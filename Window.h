#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Window
{
	public:

	Window() 
	{

		GameWindow_ = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1600,900),"MyGame", sf::Style::Close));
		GameWindow_->setFramerateLimit(FPS_);
		
	}

	~Window() 
	{

	}

	//getters / are they even necessary? XD

	/*std::shared_ptr<sf::RenderWindow> getGameWindowPointer() 
	{
		return GameWindow_;
	}*/

	//setters
	void setWindowSize(sf::Vector2u size) 
	{
		GameWindow_->setSize(size);
		GameWindowSize_ = size;
	}

	void setFramerateLimit(uint16_t fps)
	{
		GameWindow_->setFramerateLimit(fps);
		FPS_ = fps;
	}

	//other functions
	void draw(sf::Drawable &toDraw) 
	{
		GameWindow_->draw(toDraw);
	}
	void clear()
	{
		GameWindow_->clear();
	}
	void display()
	{
		GameWindow_->display();
	}
	bool isOpen()
	{
		return GameWindow_->isOpen();
	}
	void eventHandler() 
	{
		sf::Event event;
		while (GameWindow_->pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				GameWindow_->close();
		}
	}

private:
	std::shared_ptr<sf::RenderWindow> GameWindow_;
	uint16_t FPS_=60;
	sf::Vector2u GameWindowSize_ = sf::Vector2u(1600, 900);

};

