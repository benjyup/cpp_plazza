//
// Created by florian on 4/21/17.
//

#include <iostream>
#include <unistd.h>
#include "ThreadPool.hpp"

void		my_func(std::pair<std::string, Information>)
{
  std::cout << "Je suis un thread" << std::endl;
  std::cout << "Working ..." << std::endl;
  sleep(5);
  std::cout << "Done ..." << std::endl;
}

void		test(Pza::ThreadPool *t)
{
  std::mutex	&mutex = t->getMutex();

  std::cout << "New Thread"  << std::endl;
  while (42)
    {
      {
	std::unique_lock<std::mutex> lock(mutex);
	while (!t->getStatus() && t->empty())
	  t->wait(lock);
	if (t->getStatus())
	  break;
      }
      //auto couple = (t->getTask());
      //call function with the pair argument;
     // t->dec();
      my_func((t->getTask()));
     // t->inc();
    }
}

Pza::ThreadPool::ThreadPool(unsigned int nb)
	:   _stop(false), _dispo(_workers.size())
{
  std::cout << "Création de la ThreadPool\n";
  for(unsigned int i = 0; i < nb; ++i)
    _workers.emplace_back(std::thread(test, this)); //check
}

Pza::ThreadPool::~ThreadPool()
{
  _stop = true;
  _cdtVar.notify_all();
  for(auto &i : _workers)
    i.join();
}

bool Pza::ThreadPool::getStatus() const {
  return _stop;
}

void Pza::ThreadPool::addTask(std::string const & filename, Information const &to_find) {
  {
    std::unique_lock<std::mutex> lock(_mutexQ);
    _Queue.push_back(std::make_pair(filename, to_find));
  }
  _cdtVar.notify_one();
}

Pza::Worker::Worker(ThreadPool &tp) : _pool(tp)  {
}

Pza::Worker::~Worker() {}

std::pair<std::string, Information> &Pza::ThreadPool::getTask(void)
{
  std::unique_lock<std::mutex> lock(_mutexQ);
  std::pair<std::string, Information> &couple = (this->_Queue.front());
  this->_Queue.pop_front();
  return (couple);
}

bool Pza::ThreadPool::empty(void) const
{
  return (this->_Queue.empty());
}

void Pza::ThreadPool::wait(std::unique_lock<std::mutex> &lock)
{
  this->_cdtVar.wait(lock);
}

std::mutex &Pza::ThreadPool::getMutex(void)
{
  return (this->_mutexQ);
}

int Pza::ThreadPool::getDispo() const
{
  return _dispo;
}

void Pza::ThreadPool::inc()
{
  _dispo++;
}

void Pza::ThreadPool::dec()
{
  _dispo--;
}
