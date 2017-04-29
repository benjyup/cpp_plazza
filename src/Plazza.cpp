//
// Created by vincent on 14/04/17.
//

#include <tgmath.h>
#include "Plazza.hpp"
#include "OrderParser.hpp"

const std::string				Pza::Plazza::SOCKET_NAME = "./plazza_socket";

void			clientReception(std::mutex &displayMutex,
					    Pza::UnixSocket::Server &server,
					    const int clientSocket)
{
  std::unique_lock<std::mutex> lock(displayMutex);
  std::string		msg = server.recept(clientSocket, 4096);

  if (!(msg.empty()))
    {
      std::cout << msg;;
    }
}

void				server(Pza::UnixSocket::Server *server, const bool *stop)
{
  std::string			msg;
  int 				clientSocket;
  std::mutex			displayMutex;
  std::list<std::thread>	threads;

  while (!(*stop))
    {
      clientSocket = server->getClientConection();
      threads.emplace_back(clientReception, std::ref(displayMutex), std::ref(*server), clientSocket);
    }
  for (auto &it : threads)
    it.join();
}

Pza::Plazza::Plazza(int nbrOfThreadPerProcess) :
	_nbrOfThreadPerProcess(nbrOfThreadPerProcess),
	_processes(),
	_server(Plazza::SOCKET_NAME, _nbrOfThreadPerProcess),
	_stopServer(false),
	_threadServer(server, &this->_server, &_stopServer)
{
  if (_nbrOfThreadPerProcess <= 0 || _nbrOfThreadPerProcess > 10)
    throw Pza::PlazzaException("The number of thread per process must be between 1 and 10");
}

Pza::Plazza::~Plazza()
{
  UnixSocket::Client				_client(SOCKET_NAME);
  //  std::cerr << "~Plazza " << SOCKET_NAME<< std::endl;
  this->_stopServer = true;
  _client.send("stop");
  _threadServer.join();
}

void						Pza::Plazza::processHandler(std::vector<std::pair<std::vector<
									    std::string>, Information>> const &orders)
{
  unsigned int nbTask = 0;
  unsigned int j;
  int		process = 0;

  for (const auto &i : orders)
    nbTask += i.first.size();
  while (std::ceil((double)nbTask / _nbrOfThreadPerProcess) > _processes.size() || _processes.size() == 0)
    this->_processes.emplace_back(_nbrOfThreadPerProcess);
  //std::cout << "Nb Task : " << nbTask << "Nbr of Process : " << _processes.size() << std::endl;
  for (const auto &it : orders)
    {
      j = 0;
      process = 0;
      auto list_it = _processes.begin();
      while (j < it.first.size() &&  list_it != _processes.end())
	{
	  list_it->AddTask(it.first[j], it.second);
	  process++;
	  if (process == _nbrOfThreadPerProcess)
	    {
	      list_it++;
	      process = 0;
	    }
	  j++;
	}
    }
}

void 						Pza::Plazza::reception()
{
  std::string line;
  Pza::OrderParser parser;
  std::vector<std::pair<std::vector<std::string>,
	  Information>> orders;

  while (std::getline(std::cin, line))
    {
      if (!(line.empty()))
	{
	  parser.feed(line);
	  try
	    {
	      parser.parse(orders);
	    } catch (const std::exception &e)
	    {
	      std::cerr << "Error: " << e.what() << std::endl;
	      continue ;
	    }
	  //	  this->dump(orders);
	  processHandler(orders);
	  orders.clear();
	}
    }
}

void Pza::Plazza::dump(std::vector<std::pair<std::vector<std::string>,
	Information>> orders) const
{
  for (const auto &order: orders)
    {
      std::cout << "Files : " << std::endl;
      for (const auto &files : order.first)
	{
	  std::cout << files << std::endl;
	}
      std::cout << "Information to get :" << Pza::OrderParser::INFORMATION_TO_STRING.at(order.second) << std::endl
		<< std::endl;
    }
}
