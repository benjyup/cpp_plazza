//
// Created by vincent on 22/04/17.
//

#ifndef CPP_PLAZZA_SERVEREXCEPTION_HPP
# define CPP_PLAZZA_SERVEREXCEPTION_HPP

# include <exception>
# include <string>

namespace Pza
{
  namespace UnixSocket
  {
    class ServerException : public std::exception
    {
    public:
      ServerException(const std::string &str) throw();
      virtual ~ServerException() throw();
      virtual const char		*what() const throw();
    private:
      std::string			_str;
    };
  }
}

#endif //CPP_PLAZZA_SERVEREXCEPTION_HPP
