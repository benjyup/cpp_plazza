//
// ServerException.cpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:30:03 2017 vincent.mesquita@epitech.eu
// Last update Sun Apr 16 15:34:16 2017 vincent.mesquita@epitech.eu
//

#include "ServerException.hpp"

tcp::ServerException::ServerException(const std::string &str) throw() :
  _str(str)
{ }

tcp::ServerException::~ServerException(void) throw()
{ }

const char		*tcp::ServerException::what(void) const throw()
{
  return (this->_str.c_str());
}

