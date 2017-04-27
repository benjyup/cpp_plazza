//
// main.cpp for main in /home/peixot_b/Epitech/TEST/SFML
// 
// Made by Benjamin
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Mon Apr 24 17:30:12 2017 Benjamin
// Last update Mon Apr 24 18:50:45 2017 Benjamin
//

#include <SFML/Graphics.hpp>
#include "Button.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(1600, 848,32), "Plazza", sf::Style::Default);
  std::string strMail = "  Email\nAddress";
  std::string strPhone = " Phone\nNumber";
  std::string strIP = "     IP\nAddress";

  sf::Texture texture;
  if (!texture.loadFromFile("./gfx/background.png"))
    std::cerr<<"Could not find background.png."<<std::endl;
  sf::Sprite background(texture);

  sf::Font myfont;
  if(!myfont.loadFromFile("fonts/contb.ttf"))
    std::cerr<<"Could not find contb.ttf font."<<std::endl;

  Button myMail(strMail, myfont, sf::Vector2f(1435.f, 615.f), style::orange);
  Button myNumberPhone(strPhone, myfont, sf::Vector2f(1435.f, 715.f), style::red);
  Button myIP(strIP, myfont, sf::Vector2f(1435.f, 815.f), style::green);

  sf::Event e;
  bool running = true;
  while(running)
    {
      while(window.pollEvent(e))
	{
	  if(e.type == sf::Event::Closed)
	    {
	      window.close();
	      return 0;
	    }
	}
      myMail.update(e,window);
      myNumberPhone.update(e,window);
      myIP.update(e,window);

      window.clear();
      window.draw(background);
      window.draw(myMail);
      window.draw(myNumberPhone);
      window.draw(myIP);
      window.display();
    }
  return 0;
}
