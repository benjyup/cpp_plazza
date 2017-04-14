//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_PLAZZA_HPP
#define CPP_PLAZZA_PLAZZA_HPP

#include <iostream>
#include <sstream>
#include <regex>
#include "PlazzaException.hpp"
#include "Information.hpp"

namespace Pza
{
  class Plazza
  {
   public:
    static const std::map<std::string, Information>	P_INFORMATION_LINKS;

    Plazza(int nbrOfThreadPerProcess);
    ~Plazza();

    bool 						reception(void);

   private:
    int							_nbrOfThreadPerProcess;
  };
}

#endif //CPP_PLAZZA_PLAZZA_HPP
