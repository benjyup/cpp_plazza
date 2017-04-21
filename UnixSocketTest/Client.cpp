//
// Client.cpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 22:15:10 2017 vincent.mesquita@epitech.eu
// Last update Fri Apr 21 20:46:52 2017 vincent.mesquita@epitech.eu
//

#include "Client.hpp"

const std::array<std::string, 4>		tcp::Client::HOST_ERRORS = {
  "The specified host is unknown.",
  "A temporary error occurred on an authoritative name server.  Try again later.",
  "A nonrecoverable name server error occurred.",
  "The requested name is valid but does not have an IP address." \
  "Another type of request to the name server for this domain may return an answer."
};

tcp::Client::Client(const std::string &socket_name) :
  _socket(-1),
  _servAddr()
{
  if ((this->_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    throw tcp::ClientException("Opening socket failed: " + std::string(strerror(errno)));

  bzero(reinterpret_cast<char *>(&(this->_servAddr)),
	sizeof(this->_servAddr));
  this->_servAddr.sun_family = AF_UNIX;
  strncpy(this->_servAddr.sun_path, socket_name.c_str(), sizeof(this->_servAddr.sun_path) - 1);

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
