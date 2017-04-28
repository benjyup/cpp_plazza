//
// Created by florian on 4/21/17.
//

#include <iostream>
#include "ThreadPool.hpp"

void		threadloop(Pza::ThreadPool *t)
{
  std::mutex &mutex = t->getMutex();
  std::pair<std::string, Information> pair;

//  std::cout << "New Thread" << std::endl;
  while (42)
    {
      {
	std::unique_lock<std::mutex> lock(mutex);
	while (!t->getStatus() && t->empty())
	  t->wait(lock);
	if (t->getStatus())
	  break;
	pair = t->getTask();
      }
      t->parser.parseFile(pair, -1, -1);
    }
}

Pza::ThreadPool::ThreadPool(unsigned int nb)
	:   _stop(false), _dispo(_workers.size())
{
//  std::cout << "Création de la ThreadPool\n";
  for(unsigned int i = 0; i < nb; ++i)
    _workers.emplace_back(std::thread(threadloop, this)); //check
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
