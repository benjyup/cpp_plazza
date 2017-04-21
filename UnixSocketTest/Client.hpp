//
// Client.hpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 22:00:23 2017 vincent.mesquita@epitech.eu
// Last update Fri Apr 21 20:47:19 2017 vincent.mesquita@epitech.eu
//

#ifndef CLIENT_H_
# define CLIENT_H_

# include <array>
# include <string>
# include <cstring>
# include <netdb.h>
#include <sys/socket.h>
#include <sys/un.h>
# include <string>
# include <unistd.h>
# include "ClientException.hpp"

namespace tcp
{
  class Client
  {
  public:

    static const std::array<std::string, 4>	HOST_ERRORS;

    Client(const std::string &hostname);
    ~Client(void);

    void					send(const std::string &msg) const;
    std::string					getNotification(const size_t buffLength) const;

  private:
    int						_socket;
    struct sockaddr_un				_servAddr;
  };
}

#endif /* !CLIENT_H_ */
