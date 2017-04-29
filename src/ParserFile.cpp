//
// Created by peixot_b on 24/04/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <regex>
#include <vector>
#include <mutex>
#include "ParserFile.hpp"
#include "Information.hpp"
#include "Client.hpp"
#include "Plazza.hpp"

ParserFile::ParserFile()
{
}

ParserFile::~ParserFile()
{
}

bool			ParserFile::infoValid(std::string str, int info)
{
  if (info == 0)
    {
      if (str.size() < 10)
	return (false);
      return (true);
    }
  else if (info == 1)
      {
	if (str.find("@") == std::string::npos)
	  return (false);
	return (true);
      }
    else
      {
	if (std::count_if(str.begin(), str.end(), std::bind1st(std::equal_to<char>(),'.')) != 3)
	  return (false);
	return (true);
      }
}

void			ParserFile::stockMyInfo(std::string &line, std::pair<std::string, int> task,
						    std::vector<std::string> &_info) {
  std::regex r;
  std::smatch smatch;

  if (task.second == 2)
    r = "^([0-9]{1,3}.){3}.([0-9]{1,3})$";
  if (task.second == 1)
    r = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
  if (task.second == 0)
    r = "(0|\\+33)[1-9]([-. ]?[0-9]{2}){4}";

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (infoValid(x, task.second) == true)
	  _info.push_back(x);
      line = smatch.suffix().str();
    }
}

void			ParserFile::parseFile(std::pair<std::string, int> task, int posDep, int posFin){
  std::ifstream			myfile(task.first);
  std::string			line;
  int				count = 0;
  std::vector<std::string>	_info;

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
	    stockMyInfo(line, task, _info);
	}
    }
  else
    {
      while (myfile.good())
	{
	  getline(myfile, line);
	  stockMyInfo(line, task, _info);
	}
    }

  line.clear();
  Pza::UnixSocket::Client	client(Pza::Plazza::SOCKET_NAME);
  std::vector<std::string>::const_iterator i;
  for(i=_info.begin(); i!=_info.end(); ++i)
    line = line + *i + "\n";
  std::unique_lock<std::mutex>	lock(this->_sendMutex);
  client.send(line);
  _info.clear();
}
