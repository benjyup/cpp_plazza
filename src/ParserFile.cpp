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

bool			ParserFile::infoValid(const std::string &str,
						  const Information info) const
{
  if (info == 0)
    return str.size() >= 10;
  else if (info == 1)
      return str.find("@") != std::string::npos;
    else
      return std::count_if(str.begin(), str.end(), std::bind1st(std::equal_to<char>(), '.')) == 3;
}

void			ParserFile::stockMyInfo(std::string &line, const std::pair<std::string,Information> &task,
						    std::vector<std::string> &_info) const
{
  std::regex r;
  std::smatch smatch;

  if (task.second == 2)
    r = "^([0-9]{1,3}.){3}.([0-9]{1,3})$";
  else if (task.second == 1)
    r = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
  else if (task.second == 0)
    r = "(0|\\+33)[1-9]([ ]?[0-9]{2}){4}";

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (infoValid(x, task.second))
	  _info.push_back(x);
      line = smatch.suffix().str();
    }
}

void			ParserFile::parseFile(const std::pair<std::string, Information > &task,
						  const int posDep,
						  const int posFin)
{
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
  std::vector<std::string>::const_iterator i;
  for(i=_info.begin(); i!=_info.end(); ++i)
    line = line + *i + "\n";
  Pza::UnixSocket::Client	client(Pza::Plazza::SOCKET_NAME);
  std::unique_lock<std::mutex>	lock(this->_sendMutex);
  client.send(line);
  _info.clear();
}
