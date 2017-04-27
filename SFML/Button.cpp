//
// Button.cpp for Button in /home/peixot_b/Epitech/TEST/SFML
// 
// Made by Benjamin
// Login   <benjamin.peixoto@epitech.eu>
// 
// Started on  Mon Apr 24 17:31:07 2017 Benjamin
// Last update Mon Apr 24 18:50:29 2017 Benjamin
//

#include <SFML/Graphics.hpp>

#include "Button.hpp"

Button::Button()
{

}

Button::Button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style)
{
  m_position = position;
  m_btnstate = state::normal;
  m_style = style;
  switch (m_style)
    {
      case style::orange:
	{
	  m_textNormal = sf::Color(255, 255, 255);
	  m_textHover = sf::Color(255, 255, 0);
	  m_textClicked = sf::Color(255, 255, 255);
	  m_bgNormal = sf::Color(237, 127, 16, 100);
	  m_bgHover = sf::Color(180, 127, 16, 100);
	  m_bgClicked = sf::Color(237, 127, 16);
	  m_border = sf::Color(255, 255, 255, 100);
	  break;
	}
      case style::red:
	{
	  m_textNormal = sf::Color(255, 255, 255);
	  m_textHover = sf::Color(255, 255, 0);
	  m_textClicked = sf::Color(255, 255, 255);
	  m_bgNormal = sf::Color(217, 1, 21, 100);
	  m_bgHover = sf::Color(170, 1, 21, 100);
	  m_bgClicked = sf::Color(225, 1, 21);
	  m_border = sf::Color(255, 255, 255, 100);
	  break;
	}
      case style::green:
	{
	  m_textNormal = sf::Color(255, 255, 255);
	  m_textHover = sf::Color(255, 255, 0);
	  m_textClicked = sf::Color(255, 255, 255);
	  m_bgNormal = sf::Color(58, 180, 35, 100);
	  m_bgHover = sf::Color(58, 140, 35, 100);
	  m_bgClicked = sf::Color(58, 185, 35);
	  m_border = sf::Color(255, 255, 255, 100);
	  break;
	}
      default:
	break;
    }
  m_text.setString(s);
  m_text.setFont(font);
  m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
  m_text.setColor(m_textNormal);
  m_borderRadius = 5.f;
  m_borderThickness = 0.f;
  m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);
  m_Button.setPointCount(4);
  m_Button.setPoint(1, sf::Vector2f(150, 80));
  m_Button.setPoint(0, sf::Vector2f(180, 0));
  m_Button.setPoint(2, sf::Vector2f(30, 90));
  m_Button.setPoint(3, sf::Vector2f(0, 10));
  m_Button.setOrigin(m_Button.getGlobalBounds().width/2, m_Button.getGlobalBounds().height/2);
  m_Button.setPosition(m_position);
  sf::Vector2f textPosition = sf::Vector2f(m_Button.getPosition().x, m_Button.getPosition().y - m_Button.getGlobalBounds().height/4);
  m_text.setPosition(textPosition);
  m_shadow.setFont(font);
  m_shadow = m_text;
  m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
  m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
}

Button::~Button()
{

}

void Button::setColorTextNormal(sf::Color text){m_textNormal = text;};
void Button::setColorTextHover(sf::Color text){m_textHover = text;};
void Button::setColorTextClicked(sf::Color text){m_textClicked = text;};
void Button::setColorNormal(sf::Color bgNormal){m_bgNormal = bgNormal;};
void Button::setColorHover(sf::Color bgHover){m_bgHover = bgHover;};
void Button::setColorClicked(sf::Color bgClicked){m_bgClicked = bgClicked;};
void Button::setBorderColor(sf::Color border){m_border = border;};
void Button::setBorderThickness(float t){m_borderThickness = t;};
void Button::setBorderRadius(float r){m_borderRadius = r;};
void Button::setPosition(sf::Vector2f position){m_position = position;};

void Button::setText(std::string s)
{
  m_text.setString(s);
  m_shadow = m_text;
};

sf::Vector2f Button::getPosition(){return m_position;};
sf::Vector2f Button::getDimensions(){return sf::Vector2f(m_Button.getGlobalBounds().width, m_Button.getGlobalBounds().height);};
sf::Uint32 Button::getState(){return m_btnstate;};


void Button::setSize(unsigned int size)
{
  m_fontSize = size;
  m_text.setCharacterSize(m_fontSize);
  m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
  m_shadow.setCharacterSize(m_fontSize);
  m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
  m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
}

void Button::setStyle(sf::Uint32 style)
{
  m_style = style;

  switch (m_style)
    {
      case style::orange:
	{
	  m_textNormal = sf::Color(255, 255, 255);
	  m_textHover = sf::Color(255, 255, 0);
	  m_textClicked = sf::Color(255, 255, 255);
	  m_bgNormal = sf::Color(119, 181, 254, 100);
	  m_bgHover = sf::Color(119, 140, 220, 100);
	  m_bgClicked = sf::Color(150, 150, 150);
	  m_border = sf::Color(255, 255, 255, 100);
	  break;
	}
      case style::red:
	{
	  m_textNormal = sf::Color(255, 255, 255);
	  m_textHover = sf::Color(255, 255, 0);
	  m_textClicked = sf::Color(255, 255, 255);
	  m_bgNormal = sf::Color(217, 1, 21, 100);
	  m_bgHover = sf::Color(170, 1, 21, 100);
	  m_bgClicked = sf::Color(150, 150, 150);
	  m_border = sf::Color(255, 255, 255, 100);
	  break;
	}
      case style::green:
	{
	  m_textNormal = sf::Color(255, 255, 255);
	  m_textHover = sf::Color(255, 255, 0);
	  m_textClicked = sf::Color(255, 255, 255);
	  m_bgNormal = sf::Color(58, 180, 35, 100);
	  m_bgHover = sf::Color(58, 140, 35, 100);
	  m_bgClicked = sf::Color(58, 200, 35);
	  m_border = sf::Color(255, 255, 255, 100);
	  break;
	}
      default:
	break;
    }
}
void Button::setFont(sf::Font& font)
{
  m_text.setFont(font);
  m_shadow.setFont(font);
}

void Button::update(sf::Event& e, sf::RenderWindow& window)
{
  sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);
  bool mouseInButton =    m_mousePosition.x >= m_Button.getPosition().x - m_Button.getGlobalBounds().width/2
			  && m_mousePosition.x <= m_Button.getPosition().x + m_Button.getGlobalBounds().width/2
			  && m_mousePosition.y >= m_Button.getPosition().y - m_Button.getGlobalBounds().height/2
			  && m_mousePosition.y <= m_Button.getPosition().y + m_Button.getGlobalBounds().height/2;

  m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
  m_Button.setOrigin(m_Button.getGlobalBounds().width/2, m_Button.getGlobalBounds().height/2);
  m_Button.setPosition(m_position);
  m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/3);
  sf::Vector2f textPosition = sf::Vector2f(m_Button.getPosition().x, m_Button.getPosition().y - m_Button.getGlobalBounds().height/4);
  m_text.setPosition(textPosition);
  m_text.setColor(m_textNormal);
  m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/3 +6);
  m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
  m_shadow.setColor(sf::Color(0,0,0));

  if(e.type == sf::Event::MouseMoved)
    {
      if(mouseInButton)
	m_btnstate = state::hovered;
      else
	m_btnstate = state::normal;
    }
  if (e.type == sf::Event::MouseButtonPressed)
    {
      switch(e.mouseButton.button)
	{
	case sf::Mouse::Left:
	  {
	    if(mouseInButton)
	      m_btnstate = state::clicked;
	    else
	      m_btnstate = state::normal;
	  }
	  break;
	default:
	  break;
	}
    }

  if (e.type == sf::Event::MouseButtonReleased)
    {
      switch(e.mouseButton.button)
	{
	case sf::Mouse::Left:
	  {
	    if(mouseInButton)
	      m_btnstate = state::hovered;
	    else
	      m_btnstate = state::normal;
	  }
	default:
	  break;
	}
    }
  switch(m_btnstate)
    {
    case state::normal:
      {
	m_Button.setFillColor(m_bgNormal);
	m_text.setColor(m_textNormal);
      }
      break;
    case state::hovered:
      {
	m_Button.setFillColor(m_bgHover);
	m_text.setColor(m_textHover);
      }
      break;
    case state::clicked:
      {
	m_Button.setFillColor(m_bgClicked);
	m_text.setColor(m_textClicked);
      }
      break;
    default:
      break;
    }
}

void Button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
  target.draw(m_Button, states);
  target.draw(m_shadow, states);
  target.draw(m_text, states);
}
