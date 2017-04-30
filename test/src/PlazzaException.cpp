//
// Created by vincent on 14/04/17.
//

#include "PlazzaException.hpp"

Pza::PlazzaException::PlazzaException(const std::string &str) throw() : _str(str)
{ }

Pza::PlazzaException::~PlazzaException() throw()
{ }

const char* Pza::PlazzaException::what() const throw()
{
  return (_str.c_str());
}
