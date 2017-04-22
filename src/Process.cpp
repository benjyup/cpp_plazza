//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

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

Pza::Process::Process(int nbrOfThread) :
	_nbrOfThread(nbrOfThread),
	_threadPool(_nbrOfThread),
  	_pid(fork())
{
  if (_pid < 0)
    throw Pza::PlazzaException("Error on forking: " + std::string(strerror(errno)));
  //UnixSocket::Client		client(Plazza::SOCKET_NAME);
  if (_pid == 0)
    {
      sleep(2);
      client.send("Bonjour je suis le thread[" + std::to_string(this->_id) + "]");
      std::cout << "Process créé" << std::endl;
      while (true)
	{

	}
    }
}

int 	Pza::Process::getDispo() const {
	return (_threadPool.getDispo());
}

void	Pza::Process::AddTask(std::string const &filename, const Information &info)
{
  std::cout << "adding task" << std::endl;
  _threadPool.addTask(filename, info);
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

