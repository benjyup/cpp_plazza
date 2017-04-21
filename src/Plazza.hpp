//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_PLAZZA_HPP
# define CPP_PLAZZA_PLAZZA_HPP

# include <iostream>
# include <sstream>
# include <map>
# include <vector>
# include "PlazzaException.hpp"
# include "Information.hpp"
# include "Process.hpp"

namespace Pza
{
  class Plazza
  {
   public:
    static const std::map<std::string, Information>	P_INFORMATION_LINKS;

    Plazza(int nbrOfThreadPerProcess);
    ~Plazza();

    void 						reception(void);

   private:
    Plazza(const Plazza &ths);
    Plazza &operator=(const Plazza &rhs);

    int							_nbrOfThreadPerProcess;
    std::vector<std::pair<Pza::Process, int>>			_processes;

    void						dump(std::vector<std::pair<std::vector<std::string>,
	    Information>>orders) const;
  };
}

#endif //CPP_PLAZZA_PLAZZA_HPP
