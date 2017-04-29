//
// Created by vincent on 21/04/17.
//

#include <iostream>
#include "Server.hpp"

Pza::UnixSocket::Server::Server(const std::string &socketName, int simulateConnectionAllowed) :
  _socketName(socketName),
  _simulateConnectionAllowed(simulateConnectionAllowed),
  _servSocket(-1),
  _clientSocket(-1),
  _servAddr(),
  _clientAddr()
{
  //check simulateConnectionAlloweed and Port
  if ((this->_servSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    throw Pza::UnixSocket::ServerException("Error opening socket." + std::string(strerror(errno)));

  bzero(reinterpret_cast<char *>(&this->_servAddr), sizeof(this->_servAddr));
  this->_servAddr.sun_family = AF_UNIX;
  strncpy(_servAddr.sun_path, this->_socketName.c_str(), sizeof(_servAddr.sun_path)-1);
  if (access(_servAddr.sun_path, F_OK) == 0)
    unlink(_servAddr.sun_path);
  if (bind(this->_servSocket, reinterpret_cast<struct sockaddr *>(&this->_servAddr),
	   sizeof(this->_servAddr)) < 0)
    {
      throw Pza::UnixSocket::ServerException("Error on bindig: " + std::string(strerror(errno)));
    }
  if (listen(this->_servSocket, simulateConnectionAllowed) != 0)
    throw Pza::UnixSocket::ServerException("Error on listenning: " + std::string(strerror(errno)));
}

Pza::UnixSocket::Server::~Server(void)
{
  close(this->_servSocket);
  //close(this->_clientSocket);
}

std::string				Pza::UnixSocket::Server::recept(const size_t buffLength)
{
  socklen_t				clientLen = sizeof(this->_clientAddr);
  char					buff[buffLength];

  bzero(buff, buffLength);
  if ((this->_clientSocket = accept(this->_servSocket,
				    reinterpret_cast<struct sockaddr *>(&this->_clientAddr),
				    &clientLen)) < 0)
    throw Pza::UnixSocket::ServerException("Error on accepting: " + std::string(strerror(errno)));
  if (::read(this->_clientSocket, buff, buffLength) < 0)
    throw Pza::UnixSocket::ServerException("Error on reading socket: " + std::string(strerror(errno)));
  return (std::string(buff));
}

void					Pza::UnixSocket::Server::notify(const std::string &notification) const
{
  const ssize_t				buffLength = notification.size();

  if (write(this->_clientSocket, notification .c_str(), buffLength) != buffLength)
    throw Pza::UnixSocket::ServerException("Error on writing in the socket: " + std::string(strerror(errno)));
}

int Pza::UnixSocket::Server::getClientConection(void)
{
  socklen_t				clientLen = sizeof(this->_clientAddr);

  if ((this->_clientSocket = accept(this->_servSocket,
				    reinterpret_cast<struct sockaddr *>(&this->_clientAddr),
				    &clientLen)) < 0)
    throw Pza::UnixSocket::ServerException("Error on accepting: " + std::string(strerror(errno)));
  return (this->_clientSocket);
}

std::string Pza::UnixSocket::Server::recept(const int clientSocket, const size_t buffLength)
{
  std::string				mesage;
  ssize_t 				end;

  this->_clientSocket = clientSocket;
  char					buff[buffLength];

  bzero(buff, buffLength);
  if ((end = ::read(this->_clientSocket, buff, buffLength)) < 0)
    throw Pza::UnixSocket::ServerException("Error on reading socket: " + std::string(strerror(errno)));
  return (std::string(buff, end));
}
