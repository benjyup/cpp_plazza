//
// ClientException.hpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 22:17:05 2017 vincent.mesquita@epitech.eu
// Last update Sun Apr 16 22:17:30 2017 vincent.mesquita@epitech.eu
//

#ifndef CLIENTEXCEPTION_H_
# define CLIENTEXCEPTION_H_

# include <exception>
# include <string>

namespace tcp
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


#endif /* !CLIENTEXCEPTION_H_ */
