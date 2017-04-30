//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

unsigned int				Pza::Process::ID = 0;
std::string				Pza::Process::SOCKET_NAME = "./.processSocket";
bool 					Pza::Process::FATHER_IS_OK = false;
bool 					Pza::Process::AFK = false;

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
      struct sigaction act;
      act.sa_sigaction = &Pza::Process::cancelSIGUSER2;
      act.sa_flags = SA_SIGINFO;
      sigaction(SIGUSR2, &act, NULL);
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

std::mutex	&Pza::Process::getMutex(void) { return (_timeMutex); }
std::chrono::time_point<std::chrono::system_clock> &Pza::Process::getTime(void) { return (_start); }

Pza::Process::~Process(void)
{
  std::cout << "Pid = " << getpid() << " | [" << _id << "]" << "~Process" << std::endl;
  std::cout << getpid() << " " << _pid << std::endl;
  kill(getpid(), SIGINT);
  (void)remove(this->_socketName.c_str());
}

void	chrono(std::chrono::time_point<std::chrono::system_clock> &start, std::mutex &mutex, int _pid)
{
  int elapsed_seconds = 0;

  while (elapsed_seconds < 5)
    {
      {
      	std::unique_lock<std::mutex> lock(mutex);
      	elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
      	  (std::chrono::system_clock::now() - start).count();
      }
    }
  std::cout << "SIGUSR2" << getpid() << " pid ; " << _pid << std::endl;
  kill(getppid(), SIGUSR2);
  std::cout << "SIGUSR2\n";
}

void					Pza::Process::AddTask(std::string const &filename,
								  const Information &info)
{
  try {
      //std::cout << "adding task | " << _socketName << std::endl;
      UnixSocket::Client		client(this->_socketName);
      client.send(std::to_string(filename.size()));
      client.getNotification(2);
      //std::cout << "Notification = " << client.getNotification(2) << std::endl;
      client.send(filename + std::to_string(info));
      client.getNotification(2);
    } catch (const std::exception &e) {
      std::cerr << "WArning: Not able to send task: " << e.what() << std::endl;
    }
}

void 					Pza::Process::son(void)
{
  Pza::ThreadPool			threadPool(this->_nbrOfThread);
  UnixSocket::Server			_server(this->_socketName, this->_nbrOfThread);
  int 					clientSocket;
  unsigned long				size;

  if (signal(SIGUSR1, this->sonSigHandler) == SIG_ERR || signal(SIGUSR2, this->sonSigHandler2) == SIG_ERR)
    throw Pza::PlazzaException("signal: " + std::string(strerror(errno)));
  while (!(this->FATHER_IS_OK))
    {
      if (kill(getppid(), SIGUSR1) == -1)
	throw Pza::PlazzaException("kil: " + std::string(strerror(errno)));
    }
  //std::cout << "Process créé" << std::endl;
  _start = std::chrono::system_clock::now();
  std::thread th = std::thread(chrono, std::ref(this->_start), std::ref(this->_timeMutex), this->_pid);
  while (!this->AFK)
    {
      try
	{
	  clientSocket = _server.getClientConection();
	  //std::cout << "client connecté" << std::endl;

	  std::string order(_server.recept(clientSocket, 5));
	  //std::cout << "Process[" << this->_id << "] J'ai reçu cette commande: " << order << std::endl;
	  _server.notify("OK");

	  size = toNumber<unsigned long>(order);

	  order = (_server.recept(clientSocket, size + 1));
	  _server.notify("OK");
	  //std::cout << "Process[" << this->_id << "] J'ai reçu cette commande: " << order<< std::endl;

	  threadPool.addTask(order.substr(0, size), TO_INFORMATION.at( this->toNumber<int>(std::string(1, order[size]))));
	  {
	    std::unique_lock<std::mutex> lock(_timeMutex);
	    _start = std::chrono::system_clock::now();
	  }
	} catch (const std::exception &e) {
	std::cerr << "Process[" << _id << "] error: " << e.what() << std::endl;
      }
      //close(clientSocket);
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

void 					Pza::Process::sonSigHandler2(int)
{
  std::cout << "Sighandler 2\n";
  std::cout << getpid() << std::endl;
  Pza::Process::AFK = true;
  exit(1);
  // (void)remove(this->_socketName.c_str());
}

void					Pza::Process::cancelSIGUSER2(int, siginfo_t *info, void *context)
{
  std::cout << "Cancel\n";
  /* Cancel SIGUSER1 behavior (SIGINT) */
}

void					Pza::Process::cancelSIGUSER1(int)
{
  std::cout << "SigUSER1\n";
  /* Cancel SIGUSER1 behavior (SIGINT) */
}
