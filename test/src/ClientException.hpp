//
// Created by vincent on 22/04/17.
//

#ifndef CPP_PLAZZA_CLIENTEXCEPTION_HPP
#define CPP_PLAZZA_CLIENTEXCEPTION_HPP

# include <exception>
# include <string>

namespace Pza
{
  namespace UnixSocket
  {
    class ClientException : public std::exception
    {
    public:
      ClientException(const std::string &str) throw();
      virtual ~ClientException() throw();
      virtual const char		*what() const throw();
    private:
      std::string			_str;
    };
  }
}

#endif //CPP_PLAZZA_CLIENTEXCEPTION_HPP
