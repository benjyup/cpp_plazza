//
// Server.cpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:11:26 2017 vincent.mesquita@epitech.eu
// Last update Fri Apr 21 20:45:58 2017 vincent.mesquita@epitech.eu
//

#include "Server.hpp"

tcp::Server::Server(const std::string &socketName, int simulateConnectionAllowed) :
  _socketName(socketName),
  _simulateConnectionAllowed(simulateConnectionAllowed),
  _servSocket(-1),
  _clientSocket(-1),
  _servAddr(),
  _clientAddr()
{

  //check simulateConnectionAlloweed and Port
  if ((this->_servSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    throw tcp::ServerException("Error opening socket." + std::string(strerror(errno)));

  bzero(reinterpret_cast<char *>(&this->_servAddr), sizeof(this->_servAddr));
  this->_servAddr.sun_family = AF_UNIX;
  strncpy(_servAddr.sun_path, this->_socketName.c_str(), sizeof(_servAddr.sun_path)-1);
  if (access(_servAddr.sun_path, F_OK) == 0)
    unlink(_servAddr.sun_path);
  if (bind(this->_servSocket, reinterpret_cast<struct sockaddr *>(&this->_servAddr),
	   sizeof(this->_servAddr)) < 0)
    {
      throw tcp::ServerException("Error on bindig: " + std::string(strerror(errno)));
    }
  if (listen(this->_servSocket, 2) != 0)
    throw tcp::ServerException("Error on listenning: " + std::string(strerror(errno)));
}

tcp::Server::~Server(void)
{
  close(this->_servSocket);
  close(this->_clientSocket);
}

std::string				tcp::Server::recept(const size_t buffLength)
{
  socklen_t				clientLen = sizeof(this->_clientAddr);
  char					buff[buffLength];

  bzero(buff, buffLength);
  if ((this->_clientSocket = accept(this->_servSocket,
				    reinterpret_cast<struct sockaddr *>(&this->_clientAddr),
				    &clientLen)) < 0)
    throw tcp::ServerException("Error on accepting: " + std::string(strerror(errno)));
  if (::read(this->_clientSocket, buff, buffLength) < 0)
    throw tcp::ServerException("Error on reading socket: " + std::string(strerror(errno)));
  return (std::string(buff));
}

void					tcp::Server::notify(const std::string &notification) const
{
  const ssize_t				buffLength = notification.size();

  if (write(this->_clientSocket, notification.c_str(), buffLength) != buffLength)
    throw tcp::ServerException("Error on writing in the socket: " + std::string(strerror(errno)));
}
