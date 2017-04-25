//
// Created by peixot_b on 24/04/17.
//

#ifndef CPP_PLAZZA_PARSERFILE_HPP
#define CPP_PLAZZA_PARSERFILE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "Information.hpp"

class ParserFile
{
 public:
  ParserFile();
  ~ParserFile();

  bool			infoValid(std::string str, int info);
  void			stockMyInfo(std::string &line, std::pair<std::string, int> task);
  void			parseFile(std::pair<std::string, int> task, int posDep, int posFin);

 protected:
  std::vector<std::string>	_info;
};


#endif //CPP_PLAZZA_PARSERFILE_HPP
