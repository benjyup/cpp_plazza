//
// Client.cpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 22:15:10 2017 vincent.mesquita@epitech.eu
// Last update Mon Apr 17 03:41:53 2017 vincent.mesquita@epitech.eu
//

#include "Client.hpp"

tcp::Client::Client(const std::string &hostname, uint16_t port) :
  _socket(-1),
  _servAddr()
{
  struct hostent		*server;
  //check hostname && port
  if (port <= 0)
    throw tcp::ClientException("Not able to have a negative port.");

  if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    throw tcp::ClientException("Opening socket failed: " + std::string(strerror(errno)));

  if (!(server = gethostbyname(hostname.c_str())))
    throw tcp::ClientException("No such host");

  bzero(reinterpret_cast<char *>(&(this->_servAddr)),
	sizeof(this->_servAddr));
  this->_servAddr.sin_family = AF_INET;
  bcopy(reinterpret_cast<char *>(server->h_addr),
	reinterpret_cast<char *>(&(this->_servAddr.sin_addr.s_addr)),
	server->h_length);
  this->_servAddr.sin_port = htons(port);

  if (connect(this->_socket,
	      reinterpret_cast<struct sockaddr *>(&(this->_servAddr)),
	      sizeof(this->_servAddr)) < 0)
    throw tcp::ClientException("Connection failed: " + std::string(strerror(errno)));

}

tcp::Client::~Client(void)
{
  close(this->_socket);
}

void				tcp::Client::send(const std::string &msg) const
{
  if (write(this->_socket, msg.c_str(), msg.size()) != static_cast<ssize_t>(msg.size()))
    throw tcp::ClientException("message sending failded");
}

std::string			tcp::Client::getNotification(const size_t buffLength) const
{
  char				buff[buffLength + 1];

  bzero(buff, buffLength + 1);
  if (read(this->_socket, buff, buffLength) != static_cast<ssize_t>(buffLength))
    throw tcp::ClientException("error while reading the server notification.");
  return (std::string(buff));
}
