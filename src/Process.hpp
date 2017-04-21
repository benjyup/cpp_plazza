//
// Created by vincent on 18/04/17.T
//

#ifndef CPP_PLAZZA_PROCESS_HPP
#define CPP_PLAZZA_PROCESS_HPP

# include <unistd.h>
# include <cstring>
# include <iostream>
# include <vector>
# include <sys/types.h>
# include <sys/wait.h>
# include "PlazzaException.hpp"
# include "Information.hpp"
# include "ThreadPool.hpp"

namespace Pza
{
  class Process
  {
   public:
    Process(int _nbrOfThread, const std::vector<std::string> &filenames, Information information);
    Process(int _nbrOfThread);
    Process(const Process &);
    ~Process(void);

   private:
    int 			_nbrOfThread;
    pid_t 			_pid;
    unsigned int		_id;
    ThreadPool			_threadPool;
    std::vector<std::string>	_filenames;

    Process			&operator=(const Process &);
  };
}

#endif //CPP_PLAZZA_PROCESS_HPP
