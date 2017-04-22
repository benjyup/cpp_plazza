//
// Created by vincent on 21/04/17.
//

#ifndef CPP_PLAZZA_CLIENT_HPP
#define CPP_PLAZZA_CLIENT_HPP

# include <array>
# include <string>
# include <cstring>
# include <netdb.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <string>
# include <unistd.h>
# include "ClientException.hpp"

namespace Pza
{
  namespace UnixSocket
  {
    class Client
    {
    public:

      static const std::array<std::string, 4>	HOST_ERRORS;

      Client(const std::string &hostname);
      ~Client(void);

      void					send(const std::string &msg) const;
      std::string				getNotification(const size_t buffLength) const;

    private:
      int					_socket;
      struct sockaddr_un			_servAddr;
    };
  }
}

#endif //CPP_PLAZZA_CLIENT_HPP
