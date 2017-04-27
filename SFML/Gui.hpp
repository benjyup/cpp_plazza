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

  void	selectedButton(sf::Event);
  void	refresh();
  void	initButtons();
  void	initText(sf::Text &, sf::Text &, int, int, std::string);

 protected:
  sf::RenderWindow	_window;
  std::string		_strMail;
  std::string		_strPhone;
  std::string		_strIP;

  sf::Sprite		_background;
  sf::Font		_font;
  sf::Texture		_texture;
  Button  		_myMail;
  Button		_myNumberPhone;
  Button		_myIP;
  sf::Uint32 		_info;
  std::string		_fileName;
  sf::Text		_textFull;
  sf::Text		_textFullSh;
  sf::Text		_text;
  sf::Text		_textSh;
  sf::Text		_textPrompt;
  sf::Text		_textShPrompt;
  bool			_textf;
};


#endif //CPP_PLAZZA_GUI_HPP
