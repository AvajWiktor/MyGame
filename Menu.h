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
			BtnSprite_.setTexture(BtnTextureOff_);
			BtnSprite_.setOrigin(BtnTextureOff_.getSize().x/2.0,BtnTextureOff_.getSize().y / 2.0);
			BtnSprite_.setScale(scale);
			BtnSprite_.setPosition(position);
			BtnType_ = type;
		}

		bool isButtonPressed(sf::Vector2f mousePos)
		{
			if (BtnSprite_.getGlobalBounds().contains(mousePos))
			{
				BtnSprite_.setTexture(BtnTextureOn_);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return true;
				else return false;
			}
			else
			{
				BtnSprite_.setTexture(BtnTextureOff_);
				return false;
			}
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

	
	void handleMenu(sf::RenderWindow &w) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(w);
		handleButtons(mousePos);
		draw(w);
	}
	

	

private:
	void handleButtons(sf::Vector2i mousePos)
	{

		for (auto i = MenuButtons_.begin(); i != MenuButtons_.end(); i++)
		{
			if ((*i)->isButtonPressed(sf::Vector2f(mousePos.x, mousePos.y)))
			{
				MenuState_ = (*i)->getType();
			}
		}
	}
	void draw(sf::RenderWindow& w)
	{

		switch (MenuState_)
		{
		case MenuStates_::Main:
		{
			handleDrawingMain(w);
			break;
		}
		case MenuStates_::Saves:
		{
			handleDrawingSaves(w);
			break;
		}
		case MenuStates_::Settings:
		{
			handleDrawingSettings(w);
			break;
		}
		case MenuStates_::Start:
		{
			handleDrawingStart(w);
			break;
		}
		case MenuStates_::Exit:
		{
			handleDrawingExit(w);
			break;
		}

		}

	}
	void createMenu()
	{
		std::string p1 = "graphics/btn";
		std::string p2 = "On.png";
		std::string p3 = "Off.png";

		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				std::shared_ptr<Button> ptr(new Button(p1 + std::to_string(i+1) + p2, p1 + std::to_string(i+1) + p3,
					i, sf::Vector2f(200 * GameScale_.x, 800 * GameScale_.y), GameScale_));
				MenuButtons_.push_back(ptr);
			}
			else
			{
				std::shared_ptr<Button> ptr(new Button(p1 + std::to_string(i+1) + p2, p1 + std::to_string(i+1) + p3,
					i, sf::Vector2f(800.0 * GameScale_.x, 350.0 * GameScale_.y + 100.0 * (i-1)*GameScale_.y) , GameScale_));
				MenuButtons_.push_back(ptr);
			}

		}
	}
	void handleDrawingMain(sf::RenderWindow &w)
	{
		for (auto itr = MenuButtons_.begin(); itr != MenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() != MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/ void handleDrawingSaves(sf::RenderWindow &w) 
	{
		for (auto itr = MenuButtons_.begin(); itr != MenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/void handleDrawingSettings(sf::RenderWindow &w)
	{
		for (auto itr = MenuButtons_.begin(); itr != MenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/void handleDrawingStart(sf::RenderWindow& w)
	{
		for (auto itr = MenuButtons_.begin(); itr != MenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/void handleDrawingExit(sf::RenderWindow& w)
	{
		for (auto itr = MenuButtons_.begin(); itr != MenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	std::list<std::shared_ptr<Button>> MenuButtons_;
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

