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

  bool			infoValid(const std::string &str, const Information info) const;
  void			stockMyInfo(std::string &line, const std::pair<std::string, Information > &task,
					  std::vector<std::string> &) const;
  void			parseFile(const std::pair<std::string, Information > &task,
					const int posDep = -1,
					const int posFin = -1);

 protected:
  std::mutex			_sendMutex;
};


#endif //CPP_PLAZZA_PARSERFILE_HPP
