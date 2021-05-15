#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Button.h"
#include <list>
#include <string>
class Menu
{
public:

	Menu(sf::Vector2f &scale, std::shared_ptr<Window> gameWindow)
	{
		GameWindow_ = gameWindow;
		GameScale_ = scale;
		createMenu();
	}
	~Menu() {}

	void handleMenu(sf::RenderWindow &w) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(w);
		handleButtons(mousePos);
		draw(w);
	}
	void setResolution(sf::Vector2u resolution)
	{
		MainMenuButtons_.clear();
		StartMenuButtons_.clear();
		ExitMenuButtons_.clear();
		SavesMenuButtons_.clear();
		SettingsMenuButtons_.clear();
		GameWindow_->setWindowSize(resolution);
		GameScale_ = sf::Vector2f(float(resolution.x) / 1600.0, float(resolution.y) / 900.0);
		createMenu();
		
		

	}
private:

	void handleButtons(sf::Vector2i mousePos)
	{

		for (auto i = MainMenuButtons_.begin(); i != MainMenuButtons_.end(); i++)
		{
			if ((*i)->getType() == MenuStates_::Main)
			{
				if ((*i)->isButtonPressed(sf::Vector2f(mousePos.x, mousePos.y)))
				{
					MenuState_ = (*i)->getType();
				}
			}
		}
		auto begin = MainMenuButtons_.begin();
		auto end = MainMenuButtons_.end();
		bool breakLoop = false;
		switch (MenuState_)
		{
			case MenuStates_::Main:
			{
				begin = MainMenuButtons_.begin();
				end = MainMenuButtons_.end();
				break;
			}
			case MenuStates_::Saves:
			{
				begin = SavesMenuButtons_.begin();
				end = SavesMenuButtons_.end();
				break;
			}
			case MenuStates_::Settings:
			{
				begin = SettingsMenuButtons_.begin();
				end = SettingsMenuButtons_.end();
				break;
			}
			case MenuStates_::Resolution:
			{
				begin = SettingsMenuButtons_.begin();
				end = SettingsMenuButtons_.end();
				break;
			}
			case MenuStates_::Start:
			{
				begin = StartMenuButtons_.begin();
				end = StartMenuButtons_.end();
				break;
			}
			case MenuStates_::Exit:
			{
				begin = ExitMenuButtons_.begin();
				end = ExitMenuButtons_.end();
				break;
			}
		}
		for (auto i = begin; i != end; i++)
		{
			if ((*i)->isButtonPressed(sf::Vector2f(mousePos.x, mousePos.y)))
			{
				MenuState_ = (*i)->getType();
				switch (MenuState_)
				{
					case MenuStates_::Main:
					{
						break;
					}
					case MenuStates_::Saves:
					{
						break;
					}
					case MenuStates_::Settings:
					{
						break;
					}
					case MenuStates_::Resolution:
					{
						setResolution((*i)->getResolution());
						breakLoop = true;
						break;
					}
					case MenuStates_::Start:
					{
						break;
					}
					case MenuStates_::Exit:
					{
						break;
					}
				}
			}
			if (breakLoop) 
			{
				break;
			}
		}
	}
	void draw(sf::RenderWindow& w)
	{
		//std::cout << "MenuState: " << int(MenuState_) << std::endl;
		w.draw(MenuBackgroundSprite_);
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
			case MenuStates_::Resolution:
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
		MenuBackgroundTexture_.loadFromFile("graphics/menuBackground.png");
		MenuBackgroundSprite_.setTexture(MenuBackgroundTexture_);
		MenuBackgroundSprite_.setOrigin(MenuBackgroundTexture_.getSize().x, MenuBackgroundTexture_.getSize().y);
		MenuBackgroundSprite_.setScale((1600.0/MenuBackgroundTexture_.getSize().x)*GameScale_.x, (900.0/ MenuBackgroundTexture_.getSize().y)*GameScale_.y);
		MenuBackgroundSprite_.setPosition(1600.0*GameScale_.x, 900.0*GameScale_.y);

		std::string p1 = "graphics/btn";
		std::string p2 = "On.png";
		std::string p3 = "Off.png";

		//creating MainMenu buttons which gonna be used to navigate 
		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				std::shared_ptr<Button> ptr(new Button(p1 + std::to_string(i+1) + p2, p1 + std::to_string(i+1) + p3,
					i, sf::Vector2f(200 * GameScale_.x, 800 * GameScale_.y), GameScale_));
				MainMenuButtons_.push_back(ptr);
			}
			else
			{
				std::shared_ptr<Button> ptr(new Button(p1 + std::to_string(i+1) + p2, p1 + std::to_string(i+1) + p3,
					i, sf::Vector2f(800.0 * GameScale_.x, 350.0 * GameScale_.y + 100.0 * (i-1)*GameScale_.y) , GameScale_));
				MainMenuButtons_.push_back(ptr);
			}
		}
		//creating SettingsMenu buttons
		for (int i = 0; i < Resolutions_.size(); i++)
		{
			std::shared_ptr<Button> ptr(new Button(p1 + std::to_string(i + 1) + p2, p1 + std::to_string(i + 1) + p3,
				MenuStates_::Resolution,Resolutions_[i], sf::Vector2f(800.0 * GameScale_.x, 350.0 * GameScale_.y + 100.0 * (i - 1) * GameScale_.y), GameScale_));
			SettingsMenuButtons_.push_back(ptr);
		}

	}
	void handleDrawingMain(sf::RenderWindow &w)
	{
		for (auto itr = MainMenuButtons_.begin(); itr != MainMenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() != MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/ 
	void handleDrawingSaves(sf::RenderWindow &w) 
	{
		for (auto itr = MainMenuButtons_.begin(); itr != MainMenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/
	void handleDrawingSettings(sf::RenderWindow &w)
	{
		for (auto itr = MainMenuButtons_.begin(); itr != MainMenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
		for (auto itr = SettingsMenuButtons_.begin(); itr != SettingsMenuButtons_.end(); itr++)
		{
				w.draw((*itr)->getButton());
		}
	}
	/*to do*/
	void handleDrawingStart(sf::RenderWindow& w)
	{
		for (auto itr = MainMenuButtons_.begin(); itr != MainMenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}
	/*to do*/
	void handleDrawingExit(sf::RenderWindow& w)
	{
		for (auto itr = MainMenuButtons_.begin(); itr != MainMenuButtons_.end(); itr++)
		{
			if ((*itr)->getType() == MenuStates_::Main)
			{
				w.draw((*itr)->getButton());
			}
		}
	}

	std::list<std::shared_ptr<Button>> MainMenuButtons_;
	std::list<std::shared_ptr<Button>> SettingsMenuButtons_;
	std::list<std::shared_ptr<Button>> StartMenuButtons_;
	std::list<std::shared_ptr<Button>> ExitMenuButtons_;
	std::list<std::shared_ptr<Button>> SavesMenuButtons_;
	enum MenuStates_
	{
		Main = 0,
		Start = 1,
		Settings = 2,
		Saves = 3,
		Exit = 4,
		Resolution = 5
	};
	uint8_t MenuState_;
	std::shared_ptr<Window> GameWindow_;
	sf::Vector2f GameScale_ = sf::Vector2f(1.0,1.0);
	sf::Sprite MenuBackgroundSprite_;
	sf::Texture MenuBackgroundTexture_;
	std::vector<sf::Vector2u> Resolutions_{ sf::Vector2u(1920,1080), sf::Vector2u(1600, 900),sf::Vector2u(1440, 810), sf::Vector2u(1280, 720) };
	uint8_t ResolutionNumber_ = 0; //is necessary?
};

