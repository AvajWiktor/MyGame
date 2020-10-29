#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
class Menu
{
public:

	class Button 
	{
	public:
		Button(std::string path1, std::string path2, uint8_t type, sf::Vector2f position, sf::Vector2f scale) 
		{
			BtnTextureOn_.loadFromFile(path1);
			BtnTextureOff_.loadFromFile(path2);
			BtnSprite_.setTexture(BtnTextureOn_);
			BtnSprite_.setOrigin(BtnTextureOn_.getSize().x/2.0,BtnTextureOn_.getSize().y / 2.0);
			BtnSprite_.setScale(scale);
			BtnSprite_.setPosition(position);
			BtnType_ = type;
		}

		bool isButtonPressed(sf::Vector2f mousePos)
		{
			if ((BtnSprite_.getGlobalBounds().contains(mousePos)) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) return true;
			else return false;
		}
		uint8_t getType() 
		{
			return BtnType_;
		}
		sf::Sprite getButton()
		{
			return BtnSprite_;
		}
	private:
		sf::Sprite BtnSprite_;
		sf::Texture BtnTextureOn_, BtnTextureOff_;
		uint8_t BtnType_ = 0 ;

	};

	Menu(sf::Vector2f scale) 
	{
		GameScale_ = scale;
		createMenu();
	}

	~Menu() 
	{

	}

	void handleButtons(sf::Vector2f mousePos)
	{

		for (auto i = MenuButtons_.begin(); i != MenuButtons_.end(); i++)
		{
			if ((*i)->isButtonPressed(mousePos))
			{
				MenuState_ = (*i)->getType();
			}
		}
	}

	void draw(sf::RenderWindow &w)
	{
		switch(MenuState_)
		{
			case MenuStates_::Main: 
			{
				handleMain(w);
				break;
			}
			case MenuStates_::Saves:
			{
				handleSaves(w);
				break;
			}
			case MenuStates_::Settings:
			{
				handleSettings(w);
				break;
			}
			case MenuStates_::Start:
			{
				handleStart(w);
				break;
			}
			case MenuStates_::Exit:
			{
				handleExit(w);
				break;
			}
		
		}
		
	}

	

private:
	void createMenu()
	{
		std::string p1 = "graphics/btn";
		std::string p2 = "On.png";
		std::string p3 = "Off.png";

		for (uint8_t i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				std::unique_ptr<Button> ptr(new Button(p1 + std::to_string(i) + p2, p1 + std::to_string(i) + p3,
					i, sf::Vector2f(200 * GameScale_.x, 800 * GameScale_.y), GameScale_));
			}
			else
			{
				std::unique_ptr<Button> ptr(new Button(p1 + std::to_string(i) + p2, p1 + std::to_string(i) + p3,
					i, sf::Vector2f(800.0 * GameScale_.x, 450.0 * GameScale_.y), GameScale_));
			}

		}
	}
	void handleMain(sf::RenderWindow &w)
	{
		for (auto itr = MenuButtons_.begin()++; itr != MenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() != MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/ void handleSaves(sf::RenderWindow &w) 
	{

	}
	/*to do*/void handleSettings(sf::RenderWindow &w)
	{

	}
	/*to do*/void handleStart(sf::RenderWindow& w)
	{

	}
	/*to do*/void handleExit(sf::RenderWindow& w)
	{

	}
	std::list<std::unique_ptr<Button>> MenuButtons_;
	enum MenuStates_
	{
		Main = 0,
		Start = 1,
		Settings = 2,
		Saves = 3,
		Exit = 4
	};
	uint8_t MenuState_;
	sf::Vector2f GameScale_ = sf::Vector2f(1.0,1.0);
};

