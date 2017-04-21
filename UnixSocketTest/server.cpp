//
// main.cpp for  in /tmp
// 
// Made by vincent.mesquita@epitech.eu
// Login   <vincent@epitech.net>
// 
// Started on  Sun Apr 16 15:18:53 2017 vincent.mesquita@epitech.eu
// Last update Fri Apr 21 20:45:33 2017 vincent.mesquita@epitech.eu
//

#include <iostream>
#include "Server.hpp"
#include "ServerException.hpp"

int		main(void)
{
  std::string	str;
  try{
    tcp::Server	server("plazza_socket", 5);

    str = server.recept(256);
    std::cout << "Message reçu = " << str << std::endl;
    server.notify("Ok");
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  //  sleep(3);
  return (0);
}
