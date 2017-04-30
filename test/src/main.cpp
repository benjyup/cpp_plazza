//
// Created by vincent on 14/04/17.
//

#include <iostream>
#include "Plazza.hpp"


int			usage(char *str)
{
  std::cerr << "Usage : " << str << " NbrOfThreadPerProcess" << std::endl;
  return (EXIT_FAILURE);
}

int 			main(int ac, char **av)
{
  int 			nbrOfThreadPerProcess = 0;

  if (ac != 2)
    return (usage(av[0]));

  try {
      nbrOfThreadPerProcess = std::stoi(av[1]);
      if (nbrOfThreadPerProcess <= 0)
	throw std::invalid_argument("Number of thread must be positive");
    } catch (const std::invalid_argument e) {
      std::cerr << "Error: invalid number of thread per process" << std::endl;
      return (EXIT_FAILURE);
    }

  try {
      Pza::Plazza plazza(nbrOfThreadPerProcess);
      plazza.reception();
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  return (EXIT_SUCCESS);
}