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

  bool			infoValid(std::string str, Information info);
  void			stockMyInfo(std::string &line, std::pair<std::string, Information > task,
					  std::vector<std::string> &);
  void			parseFile(std::pair<std::string, Information > task, int posDep, int posFin);

 protected:
  std::mutex			_sendMutex;
};


#endif //CPP_PLAZZA_PARSERFILE_HPP
