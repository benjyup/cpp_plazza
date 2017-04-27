//
// Created by peixot_b on 27/04/17.
//

#ifndef CPP_PLAZZA_GUI_HPP
#define CPP_PLAZZA_GUI_HPP

#include "Button.hpp"

class Gui
{
 public:
  Gui();
  ~Gui();

  void	refresh();
  void	initObjects();
 protected:
  sf::RenderWindow	_window;
  std::string	_strMail;
  std::string	_strPhone;
  std::string	_strIP;
  sf::Sprite	_background;
  sf::Font	_font;
  sf::Texture	_texture;
  Button  	_myMail;
  Button	_myNumberPhone;
  Button	_myIP;
};


#endif //CPP_PLAZZA_GUI_HPP
