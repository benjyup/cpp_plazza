//
// Created by vincent on 14/04/17.
//

#include "OrderParser.hpp"
#include "PlazzaException.hpp"

const char			Pza::OrderParser::OP_COMMANDS_SEPARATORS = ';';
const char			Pza::OrderParser::OP_ARGS_SEPARATORS = ' ';

Pza::OrderParser::OrderParser() :
	_line(""),
	_semicolonsPos()
{ }

Pza::OrderParser::~OrderParser()
{ }

void 				Pza::OrderParser::feed(const std::string &line)
{
  this->epureLine(line);
}

void 				Pza::OrderParser::parse(void)
{
  unsigned long			i = 0;
  std::string			fileName;
  std::string			information;


  for (const auto &it : _semicolonsPos)
    {
      (void)it;
      i = getFilename(fileName, i);
      i = getInformation(information, i);
      std::cout << "filename = " << fileName << std::endl;
      std::cout << "information = " << information << std::endl;
    }
  this->_semicolonsPos.clear();
}

unsigned long		Pza::OrderParser::getFilename(std::string &str,
							   unsigned long begin) const
{
  unsigned long		i = _line.find(OP_ARGS_SEPARATORS, begin);

  if (i == std::string::npos)
    throw Pza::PlazzaException("Invalid order1: " + _line);
  str = _line.substr(begin, (i - begin));
  return (i + 1);
}

unsigned long Pza::OrderParser::getInformation(std::string &str,
					       unsigned long begin) const
{
  unsigned long		i = _line.find(OP_COMMANDS_SEPARATORS, begin);

  if (i == std::string::npos)
    i = _line.size();
  str = _line.substr(begin, (i - begin));
  return (i + 1);
}

void 				Pza::OrderParser::epureLine(const std::string &line)
{
  unsigned long			i = 0;
  unsigned long			nbrOfWhiteSpace = 0;
  std::string			line_tmp = line + ";";

  _line.clear();
  while (line_tmp[i] == OP_ARGS_SEPARATORS || line_tmp[i] == OP_COMMANDS_SEPARATORS)
    i += 1;
  while (line_tmp[i])
    {
      _line += line_tmp[i];
      if (line_tmp[i] == OP_ARGS_SEPARATORS || line_tmp[i] == OP_COMMANDS_SEPARATORS || !line_tmp[i])
	{
	  while (line_tmp[i] == OP_ARGS_SEPARATORS || line_tmp[i] == OP_COMMANDS_SEPARATORS)
	    i += 1;
	  if ((line_tmp[i - 1] == OP_COMMANDS_SEPARATORS && i < line_tmp.size()) || (i >= line_tmp.size()))
	    {
	      if (i < line_tmp.size())
		_semicolonsPos.push_back(i - 1);
	      if (nbrOfWhiteSpace != 1)
		throw Pza::PlazzaException("Invalid order (check white spaces and semicolons): " + line);
	      nbrOfWhiteSpace = 0;
	    }
	  else
	    nbrOfWhiteSpace += 1;
	}
      else
	i += 1;
    }
  _semicolonsPos.push_back(_line.size() - 1);
}
