//
// Created by vincent on 14/04/17.
//

#include <iostream>
#include "Plazza.hpp"
#include "Gui.hpp"

int			usage(char *str)
{
  std::cerr << "Usage : " << str << " NbrOfThreadPerProcess" << std::endl;
  return (EXIT_FAILURE);
}

int 			main(int ac, char **av)
{
  int 			nbrOfThreadPerProcess = 0;
  Gui			gui;

  if (ac != 2)
    return (usage(av[0]));
  try {
    nbrOfThreadPerProcess = std::stoi(av[1]);
  } catch (const std::invalid_argument e) {
    std::cerr << "Error: NaN" << std::endl;
    return (EXIT_FAILURE);
  }

  try {
    Pza::Plazza plazza(nbrOfThreadPerProcess);
    Gui		gui;
    gui.refresh(plazza);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return (EXIT_SUCCESS);
}
