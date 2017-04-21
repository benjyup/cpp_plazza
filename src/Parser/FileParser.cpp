//
// Created by peixot_b on 18/04/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <regex>
unsigned     NbOfLine(const char *file)
{
    std::ifstream   myfile(file);

    myfile.unsetf(std::ios_base::skipws);
    unsigned line_count = std::count(
            std::istream_iterator<char>(myfile),
            std::istream_iterator<char>(), '\n');
    return (line_count);
}

bool			MailValid(std::string str)
{
  if (str.find("@") == std::string::npos)
    return (false);
  return (true);
}

bool			IpValid(std::string str)
{
  if (std::count_if(str.begin(), str.end(), std::bind1st(std::equal_to<char>(),'.')) != 3)
    return (false);
  return (true);
}

bool			NumberValid(std::string str)
{
  if (str.size() < 10)
    return (false);
  return (true);
}

void			myIp(std::string &line)
{
  std::regex r("^([0-9]{1,3}.){3}.([0-9]{1,3})$");
  std::smatch smatch;

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (IpValid(x) == true)
	  std::cout << x << std::endl;
      line = smatch.suffix().str();
    }
}

void			myMail(std::string &line)
{
  std::regex r("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  std::smatch smatch;

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (MailValid(x) == true)
	  std::cout << x << std::endl;
      line = smatch.suffix().str();
    }
}

void			myNumber(std::string &line)
{
  std::regex r("(0|\\+33)[1-9]([-. ]?[0-9]{2}){4}");
  std::smatch smatch;

  while (std::regex_search(line, smatch, r))
    {
      for (auto x:smatch)
	if (NumberValid(x) == true)
	  std::cout << x << std::endl;
      line = smatch.suffix().str();
    }
}

void			StockMyInfo(std::string &line, int typeInfo)
{
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

void			ParseFile(const char *file, int posDep, int posFin, int typeInfo) // à remplacer par l'énum)
{
  std::ifstream		myfile(file);
  std::string		line;
  int			count = 0 ;

  if(!myfile.is_open())
    return ; // throw an Exception
  if (posDep != -1 && posFin != -1)
    {
      while (myfile.good())
	{
	  count++;
	  getline(myfile, line);
	  if (count < posDep || count > posFin)
	    continue;
	  else
	    StockMyInfo(line, typeInfo);
	}
    }
  else
    {
      while (myfile.good())
	{
	  getline(myfile, line);
	  StockMyInfo(line, typeInfo);
	}
    }
}

int main(int ac, char **av)
{
  if (ac != 2)
    {
      std::cout << "Fils de pute l'usage c'est : ./parser [0 | 1 | 2] (0 pour les numéros de téléphone sisi, 1 pour les mails, 2 pour les ip" << std::endl;
      return (0);
    }
    //NbOfLine("test.txt");
    ParseFile("test.txt", -1, -1, std::stoi(av[1]));
  return (0);
}