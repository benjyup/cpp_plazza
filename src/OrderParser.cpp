//
// Created by vincent on 14/04/17.
//

#include "OrderParser.hpp"
#include "Plazza.hpp"

const std::map<std::string, Information>	Pza::OrderParser::STRING_TO_INFORMATION = {
	{"PHONE_NUMBER", PHONE_NUMBER},
	{"EMAIL_ADDRESS", EMAIL_ADDRESS},
	{"IP_ADDRESS", IP_ADDRESS},
};

const std::map<Information, std::string>	Pza::OrderParser::INFORMATION_TO_STRING = {
	{PHONE_NUMBER, "PHONE_NUMBER"},
	{EMAIL_ADDRESS, "EMAIL_ADDRESS"},
	{IP_ADDRESS, "IP_ADDRESS"},
};

const char					Pza::OrderParser::COMMANDS_SEPARATORS = ';';
const char					Pza::OrderParser::ARGS_SEPARATORS = ' ';

Pza::OrderParser::OrderParser() :
	_line(""),
	_orders()
{ }

Pza::OrderParser::~OrderParser()
{ }

void 				Pza::OrderParser::feed(const std::string &line)
{
  size_t			i = 0;
  size_t			max = 0;

  this->_orders.clear();
  while ((max = line.find(COMMANDS_SEPARATORS, i)) != std::string::npos)
    {
      _orders.push_back(line.substr(i, max - i));
      i = max + 1;
    }
  _orders.push_back(line.substr(i, max - i));
}

void 				Pza::OrderParser::parse(std::vector<std::pair<std::vector<std::string>,
	Information>> &orders)
{
  std::vector<std::string>	v;
  std::string			str;
  Information 			information;

  for (const auto &it : this->_orders)
    {
      v.clear();
      std::stringstream		ss(it);
      while (ss >> str)
	v.push_back(str);
      if (v.empty())
	continue ;
      try {
	  information = this->STRING_TO_INFORMATION.at(v.back());
	} catch (const std::exception &e) {
	  throw Pza::PlazzaException("Invalid information order");
	}
      v.pop_back();
      std::pair<std::vector<std::string>, Information > couple(v, information);
      orders.push_back(couple);
    }
}
