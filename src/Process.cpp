//
// Created by vincent on 18/04/17.
//

#include "Process.hpp"

Pza::Process::Process(int nbrOfThread, const std::vector<std::string> &filenames, Information information) :
	_nbrOfThread(nbrOfThread),
	_pid(fork())
{
  if (_pid < 0)
    throw Pza::PlazzaException("Error on forking: " + std::string(strerror(errno)));
  std::cout << "Process créé" << std::endl;
//  if (_pid == 0)
//    {
//      std::cout << "[" << getppid() << "] Je suis un processus(" << getpid() << ")" << "filename = " << filename << " information = " << information << std::endl;
//      while (1)
//      {
//	std::cout << "Alive" << std::endl;
//      }
//      std::exit(0);
//    }
//  else
//    {
//      //wait(NULL);
//      std::cout << "Je suis le père" << std::endl;
//      sleep(5);
//    }

}

Pza::Process::Process(const Pza::Process &other) :
	_nbrOfThread(_nbrOfThread),
	_pid(other._pid)
{

}

Pza::Process::~Process(void)
{
  kill(this->_pid, SIGINT);
  std::cout << "~Process" << std::endl;
}

