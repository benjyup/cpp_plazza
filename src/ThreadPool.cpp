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
      my_func((t->getTask()));
    }
}

Pza::ThreadPool::ThreadPool(unsigned int nb)
	:   _stop(false)
{
  Worker		work(*this);
  for(unsigned int i = 0; i < nb; ++i)
    _workers.emplace_back(test, this);
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

void Pza::ThreadPool::addTask(std::string const & filename, Information &to_find) {
  {
    std::unique_lock<std::mutex> lock(_mutexQ);
    _Queue.push_back(std::make_pair(filename, to_find));
  }
  _cdtVar.notify_one();
}

Pza::Worker::Worker(ThreadPool &tp) : _pool(tp)  {
}

Pza::Worker::~Worker() {}

void Pza::Worker::launch(void)
{
}

std::pair<std::string, Information> &Pza::ThreadPool::getTask(void)
{
  std::pair<std::string, Information> &couple = (this->_Queue.back());

  this->_Queue.pop_back();
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
