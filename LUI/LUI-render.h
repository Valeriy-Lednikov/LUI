#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include "LUI-Resources.h";
#include <chrono>

namespace lui {
	static void RenderInWindowCords(sf::RenderWindow* renderWindow, sf::RectangleShape* rect) {

		sf::Vector2f lp(
			renderWindow->getView().getCenter().x - renderWindow->getView().getSize().x / 2,
			renderWindow->getView().getCenter().y - renderWindow->getView().getSize().y / 2);
	
		sf::RectangleShape* nRS = new sf::RectangleShape(*rect);
		nRS->setPosition(lp + nRS->getPosition());
		renderWindow->draw(*nRS);
		delete nRS;
	}
	static void RenderInWindowCords(sf::RenderWindow* renderWindow, sf::CircleShape* circle) {
		sf::Vector2f lp(
			renderWindow->getView().getCenter().x - renderWindow->getView().getSize().x / 2,
			renderWindow->getView().getCenter().y - renderWindow->getView().getSize().y / 2);

		sf::CircleShape* nRS = new sf::CircleShape(*circle);
		nRS->setPosition(lp + nRS->getPosition());
		renderWindow->draw(*nRS);
		delete nRS;
	}
	static void RenderInWindowCords(sf::RenderWindow* renderWindow, sf::Text* text) {
		sf::Vector2f lp(
			renderWindow->getView().getCenter().x - renderWindow->getView().getSize().x / 2,
			renderWindow->getView().getCenter().y - renderWindow->getView().getSize().y / 2);

		sf::Text* nRS = new sf::Text(*text);
		nRS->setPosition(lp + nRS->getPosition());
		renderWindow->draw(*nRS);
		delete nRS;
	}
	
}



