//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

unsigned int				Pza::Process::ID = 0;
std::string				Pza::Process::SOCKET_NAME = "./.processSocket";
bool 					Pza::Process::FATHER_IS_OK = false;

Pza::Process::Process(int nbrOfThread) :
	_nbrOfThread(nbrOfThread),
	_pid(fork()),
	_id(Pza::Process::ID),
	_socketName(Pza::Process::SOCKET_NAME + std::to_string(Pza::Process::ID++))
{
  if (signal(SIGUSR1, this->cancelSIGUSER1) == SIG_ERR)
    throw Pza::PlazzaException("signal: " + std::string(strerror(errno)));
  if (_pid < 0)
    throw Pza::PlazzaException("fork: " + std::string(strerror(errno)));
  if (_pid != 0)
    {
      pause();
      if (kill(this->_pid, SIGUSR1) == -1)
	throw Pza::PlazzaException("kill: " + std::string(strerror(errno)));
    }
  if (_pid == 0)
    this->son();
}

Pza::Process::Process(const Pza::Process &other) :
	_nbrOfThread(other._nbrOfThread),
	_pid(this->ID++),
	_socketName(other._socketName)
{

}

Pza::Process::~Process(void)
{
  kill(this->_pid, SIGINT);
  (void)remove(this->_socketName.c_str());
}

void					Pza::Process::AddTask(std::string const &filename,
								  const Information &info)
{
  try {
      UnixSocket::Client		client(this->_socketName);
      client.send(filename + std::to_string(info));
    } catch (const std::exception &e) {
      std::cerr << "WArning: Not able to send task: " << e.what() << std::endl;
    }
}

void 					Pza::Process::son(void)
{
  Pza::ThreadPool			threadPool(this->_nbrOfThread);
  UnixSocket::Server			_server(this->_socketName, this->_nbrOfThread);
  int 					clientSocket;

  if (signal(SIGUSR1, this->sonSigHandler) == SIG_ERR)
    throw Pza::PlazzaException("signal: " + std::string(strerror(errno)));
  while (!(this->FATHER_IS_OK))
    {
      if (kill(getppid(), SIGUSR1) == -1)
	throw Pza::PlazzaException("kil: " + std::string(strerror(errno)));
    }
  while (true)
    {
      try
	{
	  clientSocket = _server.getClientConection();
	  std::string order = (_server.recept(clientSocket, 4096));
	  threadPool.addTask(order.substr(0, order.size() - 1),
			     TO_INFORMATION.at( this->toNumber<int>(std::string(1, order[order.size() - 1]))));
	} catch (const std::exception &e) {
	  std::cerr << "Process[" << _id << "] error: " << e.what() << std::endl;
	}
    }
}

template<typename T>
T Pza::Process::toNumber(const std::string &str)
{
  std::stringstream ss(str);
  T     nbr;
  ss >> nbr;
  return (nbr);
}

void 					Pza::Process::sonSigHandler(int)
{
  Pza::Process::FATHER_IS_OK = true;
}

void					Pza::Process::cancelSIGUSER1(int)
{
  /* Cancel SIGUSER1 behavior (SIGINT) */
}
