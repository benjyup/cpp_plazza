//
// Created by vincent on 22/04/17.
//

#include "ClientException.hpp"

Pza::UnixSocket::ClientException::ClientException(const std::string &str) throw() :
  _str(str)
{ }

Pza::UnixSocket::ClientException::~ClientException(void) throw()
{ }

const char		*Pza::UnixSocket::ClientException::what(void) const throw()
{
  return (this->_str.c_str());
}

