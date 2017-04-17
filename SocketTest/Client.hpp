//
// Client.hpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 22:00:23 2017 vincent.mesquita@epitech.eu
// Last update Mon Apr 17 03:47:45 2017 vincent.mesquita@epitech.eu
//

#ifndef CLIENT_H_
# define CLIENT_H_

# include <string>
# include <cstring>
# include <netdb.h>
# include <netinet/in.h>
# include <unistd.h>

# include "ClientException.hpp"

namespace tcp
{
  class Client
  {
  public:

    Client(const std::string &hostname, uint16_t port);
    ~Client(void);

    void			send(const std::string &msg) const;
    std::string			getNotification(const size_t buffLength) const;

  private:
    int				_socket;
    struct sockaddr_in		_servAddr;
  };
}

#endif /* !CLIENT_H_ */
