//
// Created by vincent on 22/04/17.
//

#include "ServerException.hpp"

Pza::UnixSocket::ServerException::ServerException(const std::string &str) throw() :
  _str(str)
{ }

Pza::UnixSocket::ServerException::~ServerException(void) throw()
{ }

const char		*Pza::UnixSocket::ServerException::what(void) const throw()
{
  return (this->_str.c_str());
}

