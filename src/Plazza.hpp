//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_PLAZZA_HPP
# define CPP_PLAZZA_PLAZZA_HPP

# include <iostream>
# include <sstream>
# include <map>
# include <vector>
# include <atomic>
# include "PlazzaException.hpp"
# include "Information.hpp"
# include "Server.hpp"
# include "Process.hpp"

namespace Pza
{

  class Process;

  class Plazza
  {
   public:
    static const std::string				SOCKET_NAME;

    Plazza(int nbrOfThreadPerProcess);
    ~Plazza();

    void 						reception(void);
    void						processHandler(std::vector<std::pair<std::vector<
								       std::string>, Information>> const &orders);

   private:
    Plazza(const Plazza &ths);
    Plazza &operator=(const Plazza &rhs);

    int						_nbrOfThreadPerProcess;
    std::list<Pza::Process>			_processes;
    UnixSocket::Server				_server;
    bool 					_stopServer;
    std::thread					_threadServer;

    void						dump(std::vector<std::pair<std::vector<std::string>,
	    Information>>orders) const;
  };
}

#endif //CPP_PLAZZA_PLAZZA_HPP
