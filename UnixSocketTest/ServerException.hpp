//
// ServerException.hpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:28:24 2017 vincent.mesquita@epitech.eu
// Last update Sun Apr 16 15:32:59 2017 vincent.mesquita@epitech.eu
//

#ifndef SERVEREXCEPTION_H_
# define SERVEREXCEPTION_H_

# include <exception>
# include <string>

namespace tcp
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

#endif /* !SERVEREXCEPTION_H_ */
