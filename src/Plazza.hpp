//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_PLAZZA_HPP
#define CPP_PLAZZA_PLAZZA_HPP

#include <iostream>
#include <sstream>
#include "PlazzaException.hpp"

namespace Pza
{
  class Plazza
  {
   public:
    Plazza(int nbrOfThreadPerProcess);
    ~Plazza();

    bool 			reception(void);

   private:
    int				_nbrOfThreadPerProcess;
  };
}

#endif //CPP_PLAZZA_PLAZZA_HPP
