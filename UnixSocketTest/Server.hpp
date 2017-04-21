//
// Server.hpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:14:59 2017 vincent.mesquita@epitech.eu
// Last update Fri Apr 21 20:44:31 2017 vincent.mesquita@epitech.eu
//

#ifndef SERVER_H_
# define SERVER_H_

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

namespace tcp
{
  class Server
  {
  public:
    Server(const std::string &_socketName, int simulateConnectionAllowed);
    ~Server(void);

    
    std::string			recept(const size_t buffLength);
    void			notify(const std::string &notification) const;

  private:
    std::string			_socketName;
    int				_simulateConnectionAllowed;
    int				_servSocket;
    int				_clientSocket;
    struct ::sockaddr_un	_servAddr;
    struct ::sockaddr_un	_clientAddr;
  };
}

#endif /* !SERVER_H_ */
