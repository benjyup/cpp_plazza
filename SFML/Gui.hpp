//
// Created by peixot_b on 27/04/17.
//

#ifndef CPP_PLAZZA_GUI_HPP
#define CPP_PLAZZA_GUI_HPP

#include "Plazza.hpp"
#include "Button.hpp"

#include <SFML/Audio.hpp>

class Gui
{
 public:
  Gui();
  ~Gui();

  void				selectedButton(sf::Event);
  void				refresh(Pza::Plazza &plazza);

  void				initButtons();
  void				initMusic();
  void				initText(sf::Text &, sf::Text &, int, int, const std::string &, const int size);

  void				myBackSpace();
  void				pageLeft();
  void				pageRight();

  void				drawObjects(bool promptDraw);
  void				affResult(Pza::Plazza &plazza);

  void				readResult();
  void				userTextEntered(sf::Event e);
  void				sendCommand(Pza::Plazza &plazza);

  void				setSizeFont();

 protected:
  sf::RenderWindow		_window;
  sf::Music			_music;

  std::string			_strMail;
  std::string			_strPhone;
  std::string			_strIP;

  sf::Sprite			_background;
  sf::Font			_font;
  sf::Texture			_texture;

  Button  			_myMail;
  Button			_myNumberPhone;
  Button			_myIP;

  sf::Uint32 			_info;

  int	 			_index;
  int				_indexLeft;
  std::string			_fileName;

  sf::Text			_textFull;
  sf::Text			_textFullSh;
  sf::Text			_text;
  sf::Text			_textSh;
  sf::Text			_textPrompt;
  sf::Text			_textShPrompt;
  sf::Text			_infoGet;
  sf::Text			_infoShGet;
  bool				_textf;

  std::vector<std::string>	_pageInfo;
};


#endif //CPP_PLAZZA_GUI_HPP
