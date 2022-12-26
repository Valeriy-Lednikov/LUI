#pragma once
#include "LUI-forms.h"

void lui::Form::draw()
{
	sf::RectangleShape mainR(size);
	sf::RectangleShape titleR(sf::Vector2f(size.x, 20));
	mainR.setFillColor(sf::Color(30, 30, 30, 255));
	titleR.setFillColor(sf::Color(61, 61, 61, 255));

	sf::Text textTitle;
	//if (f_Title) {
		sf::Font font = Resources::getInstance()->getFontByID(0);
		textTitle.setFont(font);
		textTitle.setString(titleText);
		textTitle.setCharacterSize(15);
		textTitle.setPosition(sf::Vector2f(position.x + 10, position.y));
		textTitle.setFillColor(sf::Color::White);
	//}


	if (renderWindow != NULL) {
		//std::cout << "rw - " << &renderWindow << std::endl;
		renderWindow->draw(mainR);
		renderWindow->draw(titleR);
		//if (f_Title) {
			renderWindow->draw(textTitle);
		//}
	}
	else {
		std::cout << "Error - renderWindow not found\n";
	}
}

int lui::Form::getId()
{
	return this->id;
}

void lui::Form::setRenderWindow(sf::RenderWindow *renderWindow)
{
	this->renderWindow = renderWindow;
}

void lui::Form::setTitleText(std::string text)
{
	titleText = text;
}

bool lui::Form::setFlag(std::string name, bool state)
{
	if (name == "")
		return false;

	if (name == "TITLE") {
		f_Title = state;
		return true;
	}

	return false;
}
