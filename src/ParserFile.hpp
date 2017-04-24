//
// Created by peixot_b on 24/04/17.
//

#ifndef CPP_PLAZZA_PARSERFILE_HPP
#define CPP_PLAZZA_PARSERFILE_HPP

#include <string>
#include <iostream>
#include <vector>

class ParserFile
{
 public:
  ParserFile();
  ~ParserFile();

  bool			mailValid(std::string str);
  bool			ipValid(std::string str);
  bool			numberValid(std::string str);

  void			myIp(std::string &line);
  void			myNumber(std::string &line);
  void			myMail(std::string &line);

  void			stockMyInfo(std::string &line, int typeInfo);
  void			parseFile(std::pair<std::string, int> task, int posDep, int posFin);

 protected:
  std::vector<std::string>	_info;
};


#endif //CPP_PLAZZA_PARSERFILE_HPP
