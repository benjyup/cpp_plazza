//
// ClientException.cpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 22:17:39 2017 vincent.mesquita@epitech.eu
// Last update Sun Apr 16 22:17:59 2017 vincent.mesquita@epitech.eu
//

#include "ClientException.hpp"

tcp::ClientException::ClientException(const std::string &str) throw() :
  _str(str)
{ }

tcp::ClientException::~ClientException(void) throw()
{ }

const char		*tcp::ClientException::what(void) const throw()
{
  return (this->_str.c_str());
}

