//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

unsigned int			Pza::Process::ID = 0;
std::string			Pza::Process::SOCKET_NAME = "./.processSocket";

void		sigHandler(int)
{

}

Pza::Process::Process(int nbrOfThread) :
	_nbrOfThread(nbrOfThread),
//	_threadPool(_nbrOfThread),
	_pid(fork()),
	_id(Pza::Process::ID),
	_socketName(Pza::Process::SOCKET_NAME + std::to_string(Pza::Process::ID++))
{
  signal(SIGUSR1, sigHandler);
  if (_pid < 0)
    throw Pza::PlazzaException("Error on forking: " + std::string(strerror(errno)));
  if (_pid == 0)
    {
      Pza::ThreadPool			threadPool(this->_nbrOfThread);
      UnixSocket::Client		client(Pza::Plazza::SOCKET_NAME);
      UnixSocket::Server		_server(this->_socketName, nbrOfThread);
      int 				clientSocket;
      unsigned long			size;
      kill(getppid(), SIGUSR1);

      client.send("Bonjour je suis le thread[" + std::to_string(this->_id) + "]");
      std::cout << "Process créé" << std::endl;
      while (true)
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
	      //std::cout << "Process[" << this->_id << "] J'ai reçu cette commande: " << order<< std::endl;

	      threadPool.addTask(order.substr(0, size), TO_INFORMATION.at( this->toNumber<int>(std::string(1, order[size]))));
	    } catch (const std::exception &e) {
	      std::cerr << "Process[" << _id << "] error: " << e.what() << std::endl;
	    }
	  //close(clientSocket);
	}
    }
  pause();
}

/*
int 	Pza::Process::getDispo() const {
  return (_threadPool.getDispo());
}
*/

void	Pza::Process::AddTask(std::string const &filename, const Information &info)
{
  try {
      //std::cout << "adding task | " << _socketName << std::endl;
      UnixSocket::Client		client(this->_socketName);
      client.send(std::to_string(filename.size()));
      client.getNotification(2);
      //std::cout << "Notification = " << client.getNotification(2) << std::endl;
      client.send(filename + std::to_string(info));
    } catch (const std::exception &e) {
      std::cerr << "WArning: Not able to send task: " << e.what() << std::endl;
    }
}

Pza::Process::Process(const Pza::Process &other) :
	_nbrOfThread(other._nbrOfThread),
	//_threadPool(_nbrOfThread),
	_pid(other._pid)
{

}

Pza::Process::~Process(void)
{
  std::cout << "Pid = " << getpid() << " | [" << _id << "]" << "~Process" << std::endl;
  std::cout << getpid() << " " << _pid << std::endl;
  kill(this->_pid, SIGINT);
}

template<typename T>
T Pza::Process::toNumber(const std::string &str)
{
  std::stringstream ss(str);
  T     nbr;
  ss >> nbr;
  return (nbr);
}
