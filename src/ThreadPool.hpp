//
// Created by florian on 4/21/17.
//

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <deque>
#include "Information.hpp"

namespace Pza {

    class ThreadPool;
    class Worker {
    public:
        Worker(ThreadPool &tp);
        ~Worker();
        void operator()();
    private:
     ThreadPool &_pool;
    };
    class ThreadPool {
    public:
        ThreadPool(size_t);
        ~ThreadPool();
        void    addTask(std::string const &, Information &);
        bool    getStatus() const;

        std::deque<std::pair<std::string, Information>> _Queue;
        std::condition_variable                          _cdtVar;
        std::mutex                                       _mutexQ;
    private:
        std::vector<std::thread> _workers;
        bool                                             _stop;
    };
};

#endif //CPP_PLAZZA_THREADPOOL_HPP
