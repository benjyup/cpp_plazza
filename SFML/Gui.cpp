//
// Created by peixot_b on 27/04/17.
//

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Gui.hpp"
#include "Button.hpp"

Gui::Gui() : _window(sf::VideoMode(1600, 848,32), "Plazza", sf::Style::Default), _strMail("  Email\nAddress"), _strPhone(" Phone\nNumber"), _strIP("     IP\nAddress")
{
  sf::Font myfont;
  if(!myfont.loadFromFile("fonts/contb.ttf"))
    std::cerr<<"Could not find contb.ttf font."<<std::endl;
  _font = myfont;
  if (!_texture.loadFromFile("./gfx/background.png"))
    std::cerr<<"Could not find background.png."<<std::endl;
  sf::Sprite	background(_texture);
  _background = background;
  initObjects();
}

Gui::~Gui()
{
}

void	Gui::initObjects()
{
  Button  	myMail(_strMail, _font, sf::Vector2f(1435.f, 615.f), style::orange);
  Button	myNumberPhone(_strPhone, _font, sf::Vector2f(1435.f, 715.f), style::red);
  Button	myIP(_strIP, _font, sf::Vector2f(1435.f, 815.f), style::green);
  _myMail = myMail;
  _myNumberPhone = myNumberPhone;
  _myIP = myIP;
}

void Gui::refresh()
{
  sf::Event e;

  bool running = true;
  while(running)
    {
      while(_window.pollEvent(e))
	{
	  if(e.type == sf::Event::Closed)
	    {
	      _window.close();
	      return ;
	    }
	}
      _myMail.update(e,_window);
      _myNumberPhone.update(e,_window);
      _myIP.update(e,_window);
      _window.clear();
      _window.draw(_background);
      _window.draw(_myMail);
      _window.draw(_myNumberPhone);
      _window.draw(_myIP);
      _window.display();
    }
}