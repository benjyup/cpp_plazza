//
// Created by vincent on 14/04/17.
//

#ifndef CPP_PLAZZA_ORDERPARSER_HPP
#define CPP_PLAZZA_ORDERPARSER_HPP

#include <string>
#include <vector>
#include <iostream>

namespace Pza
{
  class OrderParser
  {
   public:

    static const char		OP_COMMANDS_SEPARATORS;
    static const char		OP_ARGS_SEPARATORS;

    OrderParser(void);
    ~OrderParser(void);

    void			feed(const std::string &);
    void			parse(void);


   private:
    OrderParser(const OrderParser &);
    OrderParser			&operator=(const OrderParser &);

    std::string 		_line;
    std::vector<unsigned long>	_semicolonsPos;

    unsigned long		getFilename(std::string &str,
					     unsigned long begin) const;
    unsigned long		getInformation(std::string &str,
						unsigned long begin) const;
    void			epureLine(const std::string &line);
  };
}

#endif //CPP_PLAZZA_ORDERPARSER_HPP
