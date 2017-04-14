//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_PLAZZAEXCEPTION_HPP
#define CPP_PLAZZA_PLAZZAEXCEPTION_HPP

#include <exception>
#include <string>

namespace Pza
{
  class PlazzaException : public std::exception
  {
   public:
    PlazzaException(const std::string &str) throw();
    virtual ~PlazzaException() throw();
    virtual const char *what() const throw();

   private:
    std::string		_str;

  };
}


#endif //CPP_PLAZZA_PLAZZAEXCEPTION_HPP
