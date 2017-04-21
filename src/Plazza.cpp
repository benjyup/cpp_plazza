//
// Created by vincent on 14/04/17.
//

#include "Plazza.hpp"
#include "OrderParser.hpp"

Pza::Plazza::Plazza(int nbrOfThreadPerProcess) :
	_nbrOfThreadPerProcess(nbrOfThreadPerProcess),
	_processes()
{
  if (_nbrOfThreadPerProcess <= 0 || _nbrOfThreadPerProcess > 10)
    throw Pza::PlazzaException("The number of thread per process must be between 1 and 10");
}

Pza::Plazza::~Plazza()
{ }

void 						Pza::Plazza::reception()
{
  std::string 					line;
  Pza::OrderParser				parser;
  std::vector<std::pair<std::vector<std::string>,
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
	  this->dump(orders);
	  for (const auto &it : orders)
	    this->_processes.push_back(Process(_nbrOfThreadPerProcess, it.first, it.second));
//	    this->_processes.emplace_back(_nbrOfThreadPerProcess, it.first, it.second);
	  orders.clear();
	}
    }
}

void Pza::Plazza::dump(std::vector<std::pair<std::vector<std::string>,
	Information>> orders) const
{
  for (const auto &order: orders)
    {
      std::cout << "Files : " << std::endl;
      for (const auto &files : order.first)
	{
	  std::cout << files << std::endl;
	}
      std::cout << "Information to get :" << Pza::OrderParser::INFORMATION_TO_STRING.at(order.second)<< std::endl << std::endl;
    }
}
