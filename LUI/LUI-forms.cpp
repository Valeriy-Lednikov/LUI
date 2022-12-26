#pragma once
#include "LUI-forms.h"

void lui::Form::draw()
{
	sf::RectangleShape mainR(size);
	sf::RectangleShape titleR(sf::Vector2f(size.x, 20));
	mainR.setFillColor(sf::Color(30, 30, 30, transparency));
	titleR.setFillColor(sf::Color(61, 61, 61, transparency));
	mainR.setPosition(sf::Vector2f(position));
	titleR.setPosition(sf::Vector2f(position));


	sf::Text textTitle;
	sf::Font font = Resources::getInstance()->getFontByID(0);
	textTitle.setFont(font);
	textTitle.setString(titleText);
	textTitle.setCharacterSize(15);
	textTitle.setPosition(sf::Vector2f(position.x + 10, position.y));
	textTitle.setFillColor(sf::Color(255,255,255, transparency));



	if (renderWindow != NULL) {
		renderWindow->draw(mainR);
		renderWindow->draw(titleR);
		if (f_Title) {
			renderWindow->draw(textTitle);
		}
	}
	else {
		std::cout << "Error - renderWindow not found\n";
	}
}

int lui::Form::getId()
{
	return this->id;
}

void lui::Form::setRenderWindow(sf::RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
}

void lui::Form::setTitleText(std::string text)
{
	titleText = text;
}

void lui::Form::setSize(sf::Vector2f size)
{
	this->size = size;
}



void lui::Form::setPosition(sf::Vector2f position)
{
	this->position = position;
}

sf::Vector2f lui::Form::getPosition()
{
	return this->position;
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

bool lui::Form::getFlagState(std::string name)
{
	if (name == "TITLE") {
		return f_Title;
	}
	return false;
}

void lui::Form::setTransparency(short transparency)
{
	if (transparency > 255) {
		this->transparency = 255;
		return;
	}
	if (transparency < 0) {
		this->transparency = 0;
		return;
	}
	this->transparency = transparency;
}

int lui::Form::getTransparency()
{
	return this->transparency;
}
