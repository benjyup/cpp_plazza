//
// Created by peixot_b on 27/04/17.
//

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gui.hpp"
#include "Button.hpp"

Gui::Gui() : _window(sf::VideoMode(1600, 848,32), "Plazza", sf::Style::Default), _strMail("  Email\nAddress"), _strPhone(" Phone\nNumber"), _strIP("     IP\nAddress"),
	     _info(0), _textf(false)
{
  sf::Font myfont;
  if(!myfont.loadFromFile("fonts/contb.ttf"))
    std::cerr<<"Could not find contb.ttf font."<<std::endl;
  _font = myfont;
  if (!_texture.loadFromFile("./gfx/background.png"))
    std::cerr<<"Could not find background.png."<<std::endl;
  sf::Sprite	background(_texture);
  _background = background;
  initButtons();
  initText(_text, _textSh, 12, 494, "");
  initText(_textFull, _textFullSh, 85, 530, "You don\'t have enough space...\n Press BackSpace to erase all.");
  initText(_textPrompt, _textShPrompt, 12, 499, "|");
}

Gui::~Gui()
{
}

void	Gui::initButtons()
{
  Button  	myMail(_strMail, _font, sf::Vector2f(1435.f, 615.f), style::orange);
  Button	myNumberPhone(_strPhone, _font, sf::Vector2f(1435.f, 715.f), style::red);
  Button	myIP(_strIP, _font, sf::Vector2f(1435.f, 815.f), style::green);
  _myMail = myMail;
  _myNumberPhone = myNumberPhone;
  _myIP = myIP;
}

void	Gui::initText(sf::Text &txt, sf::Text &shadow, int x, int y, std::string s)
{
  sf::Color	col(255, 255, 255);
  sf::Color	col2(0, 0, 0);

  txt.setString(s);
  txt.setFont(_font);
  txt.setCharacterSize(16);
  txt.setOrigin(txt.getGlobalBounds().width/3, txt.getGlobalBounds().height/3);
  txt.setColor(col);
  sf::Vector2f textPosition = sf::Vector2f(x, y);
  txt.setPosition(textPosition);
  shadow.setFont(_font);
  shadow = txt;
  shadow.setColor(col2);
  shadow.setOrigin(shadow.getGlobalBounds().width/3, shadow.getGlobalBounds().height/3);
  shadow.setPosition(txt.getPosition().x + 2.f, txt.getPosition().y + 2.f);
}

void	Gui::selectedButton(sf::Event e)
{
  sf::Uint32 tmp;

  if ((tmp = _myMail.update(e,_window)) <= 2)
    {
      _info = tmp;
      _myMail.setColorNormal(237, 127, 16, 255);
      _myMail.setColorHover(237, 127, 16, 255);
      _myNumberPhone.setColorNormal(217, 1, 21, 100);
      _myNumberPhone.setColorHover(170, 1, 21, 100);
      _myIP.setColorNormal(58, 180, 35, 100);
      _myIP.setColorHover(58, 140, 35, 100);
    }
  if ((tmp = _myNumberPhone.update(e,_window)) <= 2)
    {
      _info = tmp;
      _myNumberPhone.setColorNormal(225, 1, 21, 255);
      _myNumberPhone.setColorHover(225, 1, 21, 255);
      _myIP.setColorNormal(58, 180, 35, 100);
      _myIP.setColorHover(58, 140, 35, 100);
      _myMail.setColorNormal(237, 127, 16, 100);
      _myMail.setColorHover(180, 127, 16, 100);
    }
  if ((tmp = _myIP.update(e,_window)) <= 2)
    {
      _info = tmp;
      _myIP.setColorNormal(58, 185, 35, 255);
      _myIP.setColorHover(58, 185, 35, 255);
      _myNumberPhone.setColorNormal(217, 1, 21, 100);
      _myNumberPhone.setColorHover(170, 1, 21, 100);
      _myMail.setColorNormal(237, 127, 16, 100);
      _myMail.setColorHover(180, 127, 16, 100);
    }
}

void	Gui::refresh()
{
  sf::Event	e;
  int		cl;
  sf::Music	music;

  if (!music.openFromFile("./music/music.ogg"))
    std::cerr<<"Could not find music.ogg font."<<std::endl;
  music.play();
  bool	running = true;
  bool	promptDraw = false;
  cl = 0;
  while(running)
    {
      while(_window.pollEvent(e))
	{
	  if(e.type == sf::Event::Closed)
	    {
	      _window.close();
	      return ;
	    }
	  if (_fileName.size() >= 33)
	    _textf = true;
	  else if (e.type == sf::Event::TextEntered)
	      {
		if (e.text.unicode < 128)
		  {
		    _fileName += static_cast<char>(e.text.unicode);
		    _text.setString(_fileName);
		    _textSh.setString(_fileName);
		    _textPrompt.setPosition(_textPrompt.getPosition().x + 9, _textPrompt.getPosition().y);
		    _textShPrompt.setPosition(_textShPrompt.getPosition().x + 9, _textShPrompt.getPosition().y);
		  }
	      }
	  if (e.type == sf::Event::KeyPressed)
		{
		  if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		    {
		      _fileName = "";
		      _text.setString(_fileName);
		      _textSh.setString(_fileName);
		      _textf = false;
		      _textPrompt.setPosition(12, 499);
		      _textShPrompt.setPosition(_textPrompt.getPosition().x + 2.f, _textPrompt.getPosition().y + 2.f);
		    }
		}
	}
      selectedButton(e);
      _window.clear();
      _textSh.setString(_fileName);
      _window.draw(_background);
      _window.draw(_myMail);
      _window.draw(_myNumberPhone);
      _window.draw(_myIP);
      _window.draw(_textSh);
      _window.draw(_text);
      if (promptDraw)
	{
	  _window.draw(_textShPrompt);
	  _window.draw(_textPrompt);
	}
      if (_textf == true)
	{
	  _window.draw(_textFullSh);
	  _window.draw(_textFull);
	}
      _window.display();
      if (cl++ == 200)
	{
	  promptDraw = !promptDraw;
	  cl = 0;
	}
    }
}