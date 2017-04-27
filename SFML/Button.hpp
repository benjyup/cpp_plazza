//
// Button.hpp for Button in /home/peixot_b/Epitech/TEST/SFML
// 
// Made by Benjamin
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Mon Apr 24 17:32:55 2017 Benjamin
// Last update Mon Apr 24 18:50:32 2017 Benjamin
//

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

namespace state
{
  enum
  {
    normal = 0,
    hovered = 1,
    clicked = 2,
    none = 3
  };
};

namespace style
{
  enum
  {
    red = 0,
    green = 1,
    orange = 2
  };
};

class Button : public sf::Drawable
{
 public:
  Button();
  Button(std::string& s, sf::Font& font, sf::Vector2f position, sf::Uint32 style);

  ~Button();

  void setColorTextNormal(sf::Color text);
  void setColorTextHover(sf::Color text);
  void setColorTextClicked(sf::Color text);
  void setColorNormal(sf::Color bgNormal);
  void setColorNormal(int r, int g, int b, int a);
  void setColorHover(int r, int g, int b, int a);
  void setColorHover(sf::Color bgHover);
  void setColorClicked(sf::Color bgClicked);
  void setBorderColor(sf::Color border);
  void setBorderThickness(float t);
  void setBorderRadius(float r);
  void setPosition(sf::Vector2f position);
  void setSize(unsigned int size);
  void setText(std::string s);
  void setStyle(sf::Uint32 style);
  void setFont(sf::Font& font);

  sf::Vector2f getPosition();
  sf::Vector2f getDimensions();
  sf::Uint32 getState();

  sf::Uint32 update(sf::Event& e, sf::RenderWindow& window);

 private:

  virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

 private:

  sf::Color m_bgNormal;
  sf::Color m_bgHover;
  sf::Color m_bgClicked;
  sf::Color m_textNormal;
  sf::Color m_textHover;
  sf::Color m_textClicked;
  sf::Color m_border;

  float m_borderThickness;
  float m_borderRadius;
  sf::Vector2f m_size;
  sf::Vector2f m_position;
  sf::Uint32 m_style;
  sf::Uint32 m_btnstate;

  sf::ConvexShape m_Button;
  sf::Font m_font;
  unsigned int m_fontSize;
  sf::Text m_text;
  sf::Text m_shadow;
};
#endif // BUTTON_HPP
