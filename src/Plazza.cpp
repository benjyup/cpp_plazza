//
// Created by vincent on 14/04/17.
//

#include "Plazza.hpp"
#include "OrderParser.hpp"


Pza::Plazza::Plazza(int nbrOfThreadPerProcess) :
	_nbrOfThreadPerProcess(nbrOfThreadPerProcess)
{
  if (_nbrOfThreadPerProcess <= 0 || _nbrOfThreadPerProcess > 10)
    throw Pza::PlazzaException("The number of thread per process must be between 1 and 10");
}

Pza::Plazza::~Plazza()
{ }

bool 				Pza::Plazza::reception()
{
  std::string 			line;
  Pza::OrderParser		parser;

  while (std::getline(std::cin, line))
    {
      parser.feed(line);
      parser.parse();
    }
  return (true);
}