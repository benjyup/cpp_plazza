//
// Created by vincent on 14/04/17.
//

#include "Plazza.hpp"
#include "OrderParser.hpp"

const std::map<std::string, Information>	Pza::Plazza::P_INFORMATION_LINKS = {
	{"PHONE_NUMBER", PHONE_NUMBER},
	{"EMAIL_ADDRESS", EMAIL_ADDRESS},
	{"IP_ADDRESS", IP_ADDRESS},
};

Pza::Plazza::Plazza(int nbrOfThreadPerProcess) :
	_nbrOfThreadPerProcess(nbrOfThreadPerProcess)
{
  if (_nbrOfThreadPerProcess <= 0 || _nbrOfThreadPerProcess > 10)
    throw Pza::PlazzaException("The number of thread per process must be between 1 and 10");
}

Pza::Plazza::~Plazza()
{ }

void 						Pza::Plazza::reception() const
{
  std::string 					line;
  Pza::OrderParser				parser;
  std::vector<std::pair<std::string,
	  Information>>				orders;

  while (std::getline(std::cin, line))
    {
      if (!(line.empty()))
	{
	  parser.feed(line);
	  try {
	      parser.parse(orders);
	    } catch (const std::exception &e) {
	      std::cerr << "Error: " << e.what() << std::endl;
	    }
	  orders.clear();
	}
    }
}
