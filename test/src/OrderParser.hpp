//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_ORDERPARSER_HPP
#define CPP_PLAZZA_ORDERPARSER_HPP

# include <string>
# include <vector>
# include <iostream>
# include <sstream>
# include <map>
# include "Information.hpp"

namespace Pza
{
  class OrderParser
  {
   public:

    static const std::map<std::string, Information>	STRING_TO_INFORMATION;
    static const std::map<Information, std::string>	INFORMATION_TO_STRING;
    static const char					COMMANDS_SEPARATORS;
    static const char					ARGS_SEPARATORS;

    OrderParser(void);
    ~OrderParser(void);

    void						feed(const std::string &);
    void						parse(std::vector<std::pair<std::vector<std::string>,
	    Information>> &);

   private:
    OrderParser(const OrderParser &);
    OrderParser						&operator=(const OrderParser &);

    std::string 					_line;
    std::vector<std::string>				_orders;
  };
}

#endif //CPP_PLAZZA_ORDERPARSER_HPP
