//
// Created by vincent on 21/04/17.
//

#include <iostream>
#include "Client.hpp"

const std::array<std::string, 4>		Pza::UnixSocket::Client::HOST_ERRORS = {
  "The specified host is unknown.",
  "A temporary error occurred on an authoritative name server.  Try again later.",
  "A nonrecoverable name server error occurred.",
  "The requested name is valid but does not have an IP address." \
  "Another type of request to the name server for this domain may return an answer."
};

Pza::UnixSocket::Client::Client(const std::string &socket_name) :
  _socket(-1),
  _servAddr()
{
  if ((this->_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    throw Pza::UnixSocket::ClientException("Opening socket failed: " + std::string(strerror(errno)));

  bzero(reinterpret_cast<char *>(&(this->_servAddr)),
	sizeof(this->_servAddr));
  this->_servAddr.sun_family = AF_UNIX;
  strncpy(this->_servAddr.sun_path, socket_name.c_str(), sizeof(this->_servAddr.sun_path) - 1);

  if (connect(this->_socket,
	      reinterpret_cast<struct sockaddr *>(&(this->_servAddr)),
	      sizeof(this->_servAddr)) < 0)
    throw Pza::UnixSocket::ClientException("Connection failed: " + std::string(strerror(errno)));
}

Pza::UnixSocket::Client::~Client(void)
{

}

void				Pza::UnixSocket::Client::send(const std::string &msg)
{
  if (write(this->_socket, msg.c_str(), msg.size()) != static_cast<ssize_t>(msg.size()))
    throw Pza::UnixSocket::ClientException("message sending failded");
  std::cerr << "send fini -> " << msg <<std::endl;
  close(this->_socket);
}

std::string			Pza::UnixSocket::Client::getNotification(const size_t buffLength) const
{
  char				buff[buffLength + 1];

  bzero(buff, buffLength + 1);
  if (read(this->_socket, buff, buffLength) != static_cast<ssize_t>(buffLength))
    throw Pza::UnixSocket::ClientException("error while reading the server notification.");
  return (std::string(buff));
}
