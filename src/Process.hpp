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
# include <cstring>
# include "PlazzaException.hpp"
# include "Information.hpp"
# include "ThreadPool.hpp"
# include "Client.hpp"
# include "Plazza.hpp"

namespace Pza
{
  class Process
  {
   public:
    static bool 		FATHER_IS_OK;

//    Process(int _nbrOfThread, const std::vector<std::string> &filenames, Information information);
    Process(int _nbrOfThread);
    Process(const Process &);
    ~Process(void);

    void 			AddTask(const std::string &filename, const Information &info);
    static void			sonSigHandler(int);
    static void			cancelSIGUSER1(int);
    //int getDispo() const;
   private:

    static std::string		SOCKET_NAME;
    static unsigned int		ID;

    int 			_nbrOfThread;
//    ThreadPool			_threadPool;
    pid_t 			_pid;
    unsigned int		_id;
    std::string			_socketName;

    Process			&operator=(const Process &);
    template<typename T>
    T       			toNumber(const std::string &str);
    void 			son(void);
  };
}

#endif //CPP_PLAZZA_PROCESS_HPP
