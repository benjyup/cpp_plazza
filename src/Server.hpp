//
// Created by vincent on 21/04/17.
//

#ifndef CPP_PLAZZA_SERVER_HPP
# define CPP_PLAZZA_SERVER_HPP

# include <netdb.h>
# include <netinet/in.h>
# include <strings.h>
# include <unistd.h>
# include <cstring>
# include <sys/socket.h>
# include <sys/un.h>
# include <string>
# include <unistd.h>

# include "ServerException.hpp"


namespace Pza
{
  namespace UnixSocket
  {
      class Server
      {
      public:
	Server(const std::string &_socketName, int simulateConnectionAllowed);
	~Server(void);

    
	std::string		recept(const size_t buffLength);
	void			notify(const std::string &notification) const;

      private:
	std::string		_socketName;
	int			_simulateConnectionAllowed;
	int			_servSocket;
	int			_clientSocket;
	struct ::sockaddr_un	_servAddr;
	struct ::sockaddr_un	_clientAddr;
      };
  }
}

#endif //CPP_PLAZZA_SERVER_HPP
