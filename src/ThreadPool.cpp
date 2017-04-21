//
// Created by florian on 4/21/17.
//

#include <iostream>
#include "ThreadPool.hpp"

void		test(Pza::ThreadPool *t)
{
  while (42)
    {
      {
	std::unique_lock<std::mutex> lock(t->_mutexQ);
	while (!t->getStatus() && t->_Queue.empty())
	    t->_cdtVar.wait(lock);
	if (t->getStatus())
	  break;
//	auto i = _pool._Queue.front();
	//pop from task queue
	t->._Queue.pop_front();
      }
      //call function with the pair argument;
      //my_func(pair);
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
