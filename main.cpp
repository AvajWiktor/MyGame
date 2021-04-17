#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Menu.h"

using namespace std;



int main() {
	sf::Vector2f scale(1.0, 1.0);
	Window GameWindow;
	Menu GameMenu(scale, shared_ptr<Window>(new Window(GameWindow)));
	const int fps = 120;
	sf::Vector2f speed((2.0 * 60.0 / fps)*scale.x, (2.0 * 60.0 / fps)*scale.y);
	//sf::RenderWindow w(sf::VideoMode(1600,900), "iksde", sf::Style::Close);
	GameWindow.setFramerateLimit(fps);
	//unique_ptr<sf::RectangleShape> ptr(new sf::RectangleShape(sf::Vector2f(100, 100)));

		
	/*auto lambda = [&ptr, speed]() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))ptr->move(0, speed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))ptr->move(-speed, 0.0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))ptr->move(speed, 0.0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))ptr->move(0, -speed);
	};*/
	while (GameWindow.isOpen())
	{
		GameWindow.eventHandler();
		GameWindow.clear();
		//lambda();
		//GameWindow.draw(*ptr);
		// End the current frame and display its contents on screen
		GameMenu.handleMenu(*GameWindow.getGameWindowPointer());
		
		GameWindow.display();
	}
	










	return 0;
}