//
// main.cpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:18:53 2017 vincent.mesquita@epitech.eu
// Last update Mon Apr 17 03:38:51 2017 vincent.mesquita@epitech.eu
//

#include <iostream>
#include "Server.hpp"
#include "ServerException.hpp"

int		main(void)
{
  std::string	str;
  try{
    tcp::Server	server(5001, 5);

    str = server.recept(256);
    std::cout << "Message reçu = " << str << std::endl;
    server.notify("Ok");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
