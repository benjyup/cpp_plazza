//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

Pza::Process::Process(int nbrOfThread, const std::vector<std::string> &filenames, Information information) :
	_nbrOfThread(nbrOfThread),
	_pid(fork()),
	_threadPool(_nbrOfThread)
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
	  std::cout << getpid() << std::endl;
	  std::cout << "I am working ..." << std::endl;
	  sleep(5);
	  std::cout << "Done ..." << std::endl;
	  //kill(getpid(), );
	  //std::exit(0);
	}
    }
  else
    {
      /*
	wait(NULL);
	std::cout << "Je suis le père" << std::endl;
	sleep(5);
      */
    }
}

Pza::Process::Process(int nbrOfThread) :
  _nbrOfThread(nbrOfThread),
  _pid(fork()),
  _threadPool(_nbrOfThread)
{
  if (_pid < 0)
    throw Pza::PlazzaException("Error on forking: " + std::string(strerror(errno)));
  std::cout << "Process créé" << std::endl;
}

Pza::Process::Process(const Pza::Process &other) :
	_nbrOfThread(other._nbrOfThread),
	_pid(other._pid),
	_threadPool(_nbrOfThread)
{

}

Pza::Process::~Process(void)
{
  std::cout << "Pid = " << getpid() << " | [" << _id << "]" << "~Process" << std::endl;
  std::cout << getpid() << " " << _pid << std::endl;
  kill(this->_pid, SIGINT);
}

