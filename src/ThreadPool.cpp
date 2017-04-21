//
// Created by florian on 4/21/17.
//

#include "ThreadPool.hpp"

Pza::ThreadPool::ThreadPool(size_t nb)
        :   _stop(false)
{
    for(unsigned int i = 0; i < nb; ++i)
        _workers.push_back(std::thread(Worker(*this)));
}

Pza::ThreadPool::~ThreadPool()
{
    _stop = true;
    _cdtVar.notify_all();

    for(auto i : _workers)
        i.join();
}

bool Pza::ThreadPool::getStatus() const {
    return _stop;
}

void Pza::ThreadPool::addTask(std::string const & filename, Information &to_find) {
    {
        std::unique_lock lock(_mutexQ);
        _Queue.push_back(std::make_pair(filename, to_find));
    }
    _cdtVar.notify_one();
}

Pza::Worker::Worker(ThreadPool &tp) : _pool(tp)  {
    this->();
}

Pza::Worker::~Worker() {}

void Pza::Worker::operator()() {

    while (42) {
        {
            std::unique_lock lock(_pool._mutexQ);
            while (!_pool.getStatus() && _pool._Queue.empty()) {
                _pool._cdtVar.wait(lock);
            }
            if (_pool.getStatus())
                break ;
            std::pair i = _pool._Queue.front();
            //pop from task queue
            _pool._Queue.pop_front();
        }
        //call function with the pair argument;
        //my_func(pair);
    }
}

