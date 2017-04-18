//
// Created by vincent on 18/04/17.
//

#ifndef CPP_PLAZZA_PROCESS_HPP
#define CPP_PLAZZA_PROCESS_HPP

#include <unistd.h>

namespace Pza
{
  class Process
  {
   public:
    Process(int _nbrOfThread);
    ~Process(void);

   private:
    int 			_nbrOfThread;
    //ThreadPool			threadPool;

    Process(const Process &);
    Process			&operator=(const Process &);
  };
}

#endif //CPP_PLAZZA_PROCESS_HPP
