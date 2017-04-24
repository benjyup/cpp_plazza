//
// Created by florian on 4/21/17.
//

#ifndef CPP_PLAZZA_THREADPOOL_HPP
#define CPP_PLAZZA_THREADPOOL_HPP

#include <mutex>
#include <condition_variable>
#include <vector>
#include <list>
#include <deque>
#include <thread>
#include "Information.hpp"
#include "ParserFile.hpp"

namespace Pza
{

  class ThreadPool;

  class Worker
  {
   public:
    Worker(ThreadPool &tp);

    ~Worker();

   private:
    ThreadPool &_pool;
  };

  class ThreadPool
  {
   public:
    ThreadPool(unsigned int);
    ~ThreadPool();

    void addTask(std::string const &, Information const &);
    bool getStatus() const;
    int  getDispo() const;
    void inc();
    void dec();

    std::pair<std::string, Information>		&getTask(void);
    std::mutex					&getMutex(void);

    bool 					empty(void) const;
    void					wait(std::unique_lock<std::mutex> &lock);

   private:
    std::deque<std::pair<std::string, Information>> _Queue;
    std::condition_variable _cdtVar;
    std::mutex _mutexQ;
    std::deque<std::thread> _workers;
    bool _stop;
    int			     _dispo;
  };
}

#endif //CPP_PLAZZA_THREADPOOL_HPP
