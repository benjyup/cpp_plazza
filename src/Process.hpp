//
// Created by vincent on 18/04/17.
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

namespace Pza
{
  class Process
  {
   public:
    Process(int _nbrOfThread, const std::vector<std::string> &filenames, Information information);
    Process(const Process &);
    ~Process(void);

   private:
    int 			_nbrOfThread;
    pid_t 			_pid;
    //ThreadPool		threadPool;

    Process			&operator=(const Process &);
  };
}

#endif //CPP_PLAZZA_PROCESS_HPP
