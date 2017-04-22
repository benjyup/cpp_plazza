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
  std::string line;
  Pza::OrderParser parser;
  std::vector<std::pair<std::vector<std::string>,
	  Information>> orders;
  int nbTask;
  int j;

  while (std::getline(std::cin, line))
    {
      if (!(line.empty()))
	{
	  nbTask = 0;
	  parser.feed(line);
	  try
	    {
	      parser.parse(orders);
	    } catch (const std::exception &e)
	    {
	      std::cerr << "Error: " << e.what() << std::endl;
	    }
	  this->dump(orders);
	  for (const auto &i : orders)
	    nbTask += i.first.size();
	  while (nbTask / _nbrOfThreadPerProcess > _processes.size() || _processes.size() == 0)
	    this->_processes.emplace_back(_nbrOfThreadPerProcess);
	  std::cout << "Nbr of Process : " << _processes.size() << std::endl;
	  for (const auto &it : orders)
	    {
	      j = 0;
	      int process = 0;
	      auto list_it = _processes.begin();
	      while (j < it.first.size() &&  list_it != _processes.end())
		{
		  list_it->AddTask(it.first[j], it.second);
		  process++;
		  if (process == _nbrOfThreadPerProcess)
		    {
		      list_it++;
		      process = 0;
		    }
		  j++;
		}
	    }
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
      std::cout << "Information to get :" << Pza::OrderParser::INFORMATION_TO_STRING.at(order.second) << std::endl
		<< std::endl;
    }
}
