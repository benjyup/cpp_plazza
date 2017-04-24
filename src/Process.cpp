//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

unsigned int			Pza::Process::ID = 0;
std::string			Pza::Process::SOCKET_NAME = "./.processSocket";


/*Pza::Process::Process(int nbrOfThread, const std::vector<std::string> &filenames, Information information) :
	_nbrOfThread(nbrOfThread),
	_pid(fork()),
	_threadPool(_nbrOfThread),
	_filenames(filenames)
{
  (void)filenames;
  (void)information;
  std::cout << "Pid = " << getpid() << " | Process[" << _id << "] créé" << std::endl;
  if (_pid < 0)
    throw Pza::PlazzaException("Error on forking: " + std::string(strerror(errno)));
  if (_pid == 0)
    {
      while (true)
	{
	  for (const auto &filename : this->_filenames)
	    {
	      std::cout << filename << std::endl;
	      this->_threadPool.addTask(filename, information);
	    }
	  this->_filenames.clear();
	}
    }
}*/

void		sigHandler(int s)
{

}

Pza::Process::Process(int nbrOfThread) :
	_nbrOfThread(nbrOfThread),
	_threadPool(_nbrOfThread),
  	_pid(fork()),
	_id(Pza::Process::ID),
	_socketName(Pza::Process::SOCKET_NAME + std::to_string(Pza::Process::ID++))
{
  signal(SIGUSR1, sigHandler);
  if (_pid < 0)
    throw Pza::PlazzaException("Error on forking: " + std::string(strerror(errno)));
  if (_pid == 0)
    {
      UnixSocket::Client		client(Pza::Plazza::SOCKET_NAME);
      //UnixSocket::Server		_server(_socketName, 5);
      UnixSocket::Server		_server(_socketName, nbrOfThread);
      int 				clientSocket;
      kill(getppid(), SIGUSR1);

      client.send("Bonjour je suis le thread[" + std::to_string(this->_id) + "]");
      std::cout << "Process créé" << std::endl;
      while (true)
	{
	  try
	    {
	      clientSocket = _server.getClientConection();
	      std::cout << "client connecté" << std::endl;
	      std::string order(_server.recept(clientSocket, 260));
	      std::cout << "Process[" << this->_id << "] J'ai reçu cette commande: " << order << std::endl;
/*
	      order = (_server.recept(clientSocket, 260));
	      std::cout << "Process[" << this->_id << "] J'ai reçu cette commande: " << order << std::endl;
*/
	    } catch (const std::exception &e) {
	      std::cerr << "Process[" << _id << "] error: " << e.what() << std::endl;
	    }
	  close(clientSocket);
	}
    }
  pause();
}

int 	Pza::Process::getDispo() const {
	return (_threadPool.getDispo());
}

void	Pza::Process::AddTask(std::string const &filename, const Information &info)
{
  try {
      std::cout << "adding task | " << _socketName << std::endl;
      UnixSocket::Client		client(this->_socketName);
      client.send(filename  + " -> " +std::to_string(info));
    } catch (const std::exception &e) {
      std::cerr << "WArning: Not able to send task: " << e.what() << std::endl;
    }
/*
  try {
      std::cout << "adding task | " << _socketName << std::endl;
      UnixSocket::Client		client(this->_socketName);
      client.send(filename  + " -> " +std::to_string(info));
    } catch (const std::exception &e) {
      std::cerr << "WArning: Not able to send task: " << e.what() << std::endl;
    }
*/
/*
  try {
      std::cout << "adding task | " << _socketName << std::endl;
      UnixSocket::Client		client(this->_socketName);
      client.send("length pour read = " + std::to_string(filename.size()));
    } catch (const std::exception &e) {
      std::cerr << "WArning: Not able to send task: " << e.what() << std::endl;
    }
*/
}

Pza::Process::Process(const Pza::Process &other) :
	_nbrOfThread(other._nbrOfThread),
	_threadPool(_nbrOfThread),
	_pid(other._pid)
{

}

Pza::Process::~Process(void)
{
  std::cout << "Pid = " << getpid() << " | [" << _id << "]" << "~Process" << std::endl;
  std::cout << getpid() << " " << _pid << std::endl;
  kill(this->_pid, SIGINT);
}
