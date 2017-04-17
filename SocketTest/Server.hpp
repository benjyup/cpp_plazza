//
// Server.hpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:14:59 2017 vincent.mesquita@epitech.eu
// Last update Sun Apr 16 17:04:39 2017 vincent.mesquita@epitech.eu
//

#ifndef SERVER_H_
# define SERVER_H_

# include <netdb.h>
# include <netinet/in.h>
# include <strings.h>
# include <unistd.h>
# include <cstring>

# include "ServerException.hpp"

namespace tcp
{
  class Server
  {
  public:
    Server(int _port, int simulateConnectionAllowed);
    ~Server(void);

    
    std::string			recept(const size_t buffLength);
    void			notify(const std::string &notification) const;

  private:
    int				_port;
    int				_simulateConnectionAllowed;
    int				_servSocket;
    int				_clientSocket;
    struct ::sockaddr_in	_servAddr;
    struct ::sockaddr_in	_clientAddr;
  };
}

#endif /* !SERVER_H_ */
