//
// Created by peixot_b on 24/04/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>
#include "ParserFile.hpp"
#include "Information.hpp"

ParserFile::ParserFile()
{
}

ParserFile::~ParserFile()
{
  _info.clear();
}

bool			ParserFile::mailValid(std::string str){
  if (str.find("@") == std::string::npos)
    return (false);
  return (true);
}

bool			ParserFile::ipValid(std::string str){
  if (std::count_if(str.begin(), str.end(), std::bind1st(std::equal_to<char>(),'.')) != 3)
    return (false);
  return (true);
}

bool			ParserFile::numberValid(std::string str){
  if (str.size() < 10)
    return (false);
  return (true);
}

void			ParserFile::myIp(std::string &line)
{
  std::regex r("^([0-9]{1,3}.){3}.([0-9]{1,3})$");
  std::smatch smatch;

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (ipValid(x) == true)
	  _info.push_back(x);
      line = smatch.suffix().str();
    }
}

void			ParserFile::myMail(std::string &line)
{
  std::regex r("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  std::smatch smatch;

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (mailValid(x) == true)
	  _info.push_back(x);
      line = smatch.suffix().str();
    }
}

void			ParserFile::myNumber(std::string &line)
{
  std::regex r("(0|\\+33)[1-9]([-. ]?[0-9]{2}){4}");
  std::smatch smatch;

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (numberValid(x) == true)
	  _info.push_back(x);
      line = smatch.suffix().str();
    }
}

void			ParserFile::stockMyInfo(std::string &line, int typeInfo) { //typeInfo doit etre du type Information
  switch (typeInfo)
    {
      case 0:
	myNumber(line);
      break;
      case 1:
	myMail(line);
      break;
      case 2:
	myIp(line);
      break;
      default:
	break;
    }
}

void			ParserFile::parseFile(std::pair<std::string, int> task, int posDep, int posFin){ // mettre des valeur par défaut pour posDep et posFin
  std::ifstream			myfile(task.first);
  std::string			line;
  int				count = 0;

  std::cout << "Je rentre dans la fonction avec : filename = " << task.first << " info = " << task.second << std::endl;
  if(!myfile.is_open())
    {
      std::cout << "Error: \"" << task.first << "\" doesn't exist." << std::endl;
      return ;
    }
  if (posDep != -1 && posFin != -1)
    {
      while (myfile.good())
	{
	  count++;
	  getline(myfile, line);
	  if (count < posDep || count > posFin)
	    continue;
	  else
	    stockMyInfo(line, task.second);
	}
    }
  else
    {
      while (myfile.good())
	{
	  getline(myfile, line);
	  stockMyInfo(line, task.second);
	}
    }
// A RETIRER
  std::vector<std::string>::const_iterator i;
  for(i=_info.begin(); i!=_info.end(); ++i){
      std::cout<<(*i)<<std::endl;
    }
}