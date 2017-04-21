//
// client.cpp for  in /home/vincent/rendu/plazza/SocketTest
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Mon Apr 17 02:53:28 2017 vincent.mesquita@epitech.eu
// Last update Fri Apr 21 20:47:31 2017 vincent.mesquita@epitech.eu
//

#include <iostream>

#include "Client.hpp"
#include "ClientException.hpp"

int			main(void)
{
  try {
    tcp::Client		client("plazza_socket");
    client.send("Bonjour à tous\n");
    std::cout << client.getNotification(2) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  
  return (0);
}
