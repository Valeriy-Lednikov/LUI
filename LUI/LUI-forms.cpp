#pragma once
#include "LUI-forms.h"

lui::Form::Form(sf::RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
	if (renderWindow == NULL) {
		std::cout << "Error init - null" << std::endl;
	}
	std::cout << "form create " << id << "\n";
}

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

void lui::Form::update(sf::Event event)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition();
	sf::Vector2f worldPos = renderWindow->mapPixelToCoords(pixelPos);
	worldPos = worldPos - sf::Vector2f(renderWindow->getPosition().x, renderWindow->getPosition().y);


	if (a_Drag&& f_TitleIsTitleWindow) {
		sf::Vector2i subPoints = pixelPos - dragPoint;
		renderWindow->setPosition(subPoints);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (worldPos.x <= size.x + position.x && worldPos.x >= position.x) {
			if (worldPos.y >= position.y && worldPos.y <= position.y + 20) {
				a_Drag = true;
				dragPoint = sf::Vector2i(worldPos.x, worldPos.y);
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		a_Drag = false;
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
	if (name == "TITLE") {
		f_Title = state;
		return true;
	}
	if (name == "FORM_IS_WINDOW")
	{
		f_TitleIsTitleWindow = state;
		renderWindow->setSize(sf::Vector2u(size.x, size.y));
		return true;
	}
	if (name == "BLOCK_RENDER"&& f_TitleIsTitleWindow) {//! Not implemented
		f_BlockRender = state;
	}

	return false;
}

bool lui::Form::getFlagState(std::string name)
{
	if (name == "TITLE") {return f_Title;}
	if (name == "FORM_IS_WINDOW"){return f_TitleIsTitleWindow;}
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

int lui::Form::getCountComponents()
{
	return this->countComponents;
}

void lui::Form::setCountComponents(int count)
{
	this->countComponents = count;
}

lui::Component::Component(sf::Vector2f position, sf::Vector2f size, bool isActive, bool isVisible)
{
	this->position = position;
	this->size = size;
	this->active = isActive;
	this->visible = isVisible;
	this->id = getCountComponents() + 1;
	setCountComponents(id);
}

lui::Component::Component(sf::Vector2f position, sf::Vector2f size)
{
	this->position = position;
	this->size = size;
	this->id = getCountComponents() + 1;
	setCountComponents(id);
}
