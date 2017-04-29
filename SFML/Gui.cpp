//
// Created by peixot_b on 27/04/17.
//

#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Thread.hpp>
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
  initText(_text, _textSh, 0, 494, "", 16);
  initText(_textFull, _textFullSh, 10, 520, "You don\'t have enough space...\n Press BackSpace to erase all.", 16);
  initText(_textPrompt, _textShPrompt, 0, 494, "|", 16);
  initText(_infoGet, _infoShGet, 0, 35, "" , 12);
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

void	Gui::initText(sf::Text &txt, sf::Text &shadow, int x, int y, std::string s, int size)
{
  sf::Color	col(255, 255, 255);
  sf::Color	col2(0, 0, 0);

  txt.setString(s);
  txt.setFont(_font);
  txt.setCharacterSize(size);
  txt.setColor(col);
  sf::Vector2f textPosition = sf::Vector2f(x, y);
  txt.setPosition(textPosition);
  shadow.setFont(_font);
  shadow = txt;
  shadow.setColor(col2);
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

void	Gui::myBackSpace()
{
  if (_fileName.size() > 0)
    _fileName.erase(_fileName.size() - 1);
  _text.setString(_fileName);
  _textSh.setString(_fileName);
  _textf = false;
  _textPrompt.setPosition(_text.getPosition().x + _text.getLocalBounds().width, _textPrompt.getPosition().y);
  _textShPrompt.setPosition(_text.getPosition().x + _text.getLocalBounds().width, _textShPrompt.getPosition().y);
}

void	Gui::userTextEntered(sf::Event e)
{
  if (e.text.unicode < 128 && e.text.unicode >= 32)
    {
      _fileName += static_cast<char>(e.text.unicode);
      _text.setString(_fileName);
      _textSh.setString(_fileName);
      _textPrompt.setPosition(_text.getPosition().x + _text.getLocalBounds().width, _textPrompt.getPosition().y);
      _textShPrompt.setPosition(_text.getPosition().x + _text.getLocalBounds().width, _textShPrompt.getPosition().y);
    }
}

void	Gui::drawObjects(bool promptDraw)
{
  _window.clear();
  _textSh.setString(_fileName);
  _window.draw(_background);
  _window.draw(_myMail);
  _window.draw(_myNumberPhone);
  _window.draw(_myIP);
  _window.draw(_textSh);
  _window.draw(_text);
  _window.draw(_infoShGet);
  _window.draw(_infoGet);
  if (promptDraw)
    {
      _window.draw(_textShPrompt);
      _window.draw(_textPrompt);
    }
  if (_textf)
    {
      _window.draw(_textFullSh);
      _window.draw(_textFull);
    }
  _window.display();
}

void	Gui::readResult()
{
  sf::Time	time = sf::seconds(0.05);
  std::string	fileInfo;
  std::string	tmp;
  std::ifstream myfile("test.txt");
  int	i;

  i = 0;
  while (myfile.good())
    {
      if (i == 27)
	{
	  _pageInfo.push_back(fileInfo);
	  fileInfo = "";
	  i = 0;
	}
      sf::sleep(time);
      getline(myfile, tmp);
      fileInfo += tmp + '\n';
      i++;
      //_infoGet.setString(fileInfo);
      //_infoShGet.setString(fileInfo);
    }
  _pageInfo.push_back(fileInfo);
}

void	Gui::refresh()
{
  sf::Event	e;
  int		cl;
  sf::Music	music;
  bool		running = true;
  bool		promptDraw = false;
  //sf::Thread	th(&Gui::readResult, this);

  //th.launch();
  if (!music.openFromFile("./music/music.ogg"))
    std::cerr<<"Could not find music.ogg font."<<std::endl;
  music.play();
  cl = 0;
  while(running)
    {
      while(_window.pollEvent(e))
	{
	  if(e.type == sf::Event::Closed)
	    running = !running;
	  if (_fileName.size() >= 36)
	    _textf = true;
	  else if (e.type == sf::Event::TextEntered)
	    userTextEntered(e);
	  if (e.type == sf::Event::KeyPressed)
	    {
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && _fileName.size() > 0)
		myBackSpace();
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		running = !running;
	      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
		  //th.terminate();

		  // Go to process

		  //th.launch();
		  //for (auto i = _pageInfo.begin(); i != _pageInfo.end(); ++i)
		   // {
		    //  _infoGet.setString(*i);
		     // _infoShGet.setString(*i);
		   // }
		}
	    }
	}
      selectedButton(e);
      drawObjects(promptDraw);
      if (cl++ == 200)
	{
	  promptDraw = !promptDraw;
	  cl = 0;
	}
    }
  //th.terminate();
  _window.close();
}
