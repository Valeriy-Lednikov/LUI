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
	mainR.setFillColor(sf::Color(128, 128, 128, transparency));
	titleR.setFillColor(sf::Color(64, 64, 64, transparency));
	mainR.setPosition(sf::Vector2f(position));
	titleR.setPosition(sf::Vector2f(position));


	sf::Text textTitle;
	sf::Font font = Resources::getInstance()->getFontByID(0);
	textTitle.setFont(font);
	textTitle.setString(titleText);
	textTitle.setCharacterSize(15);
	textTitle.setPosition(sf::Vector2f(position.x + 10, position.y));
	textTitle.setFillColor(sf::Color(255, 255, 255, transparency));



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
	//render components ---------------------------------------------------------
	for (int i = 0; i < components.size(); i++) {
		if (dynamic_cast<Button*>(components[i]))
		{
			Button* button = dynamic_cast<Button*>(components[i]);
			button->draw();
		}
	}



}

void lui::Form::update(sf::Event event)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition();
	sf::Vector2f worldPos = renderWindow->mapPixelToCoords(pixelPos);
	worldPos = worldPos - sf::Vector2f(renderWindow->getPosition().x, renderWindow->getPosition().y);


	if (a_Drag && f_TitleIsTitleWindow) {//Update drag/drop
		sf::Vector2i subPoints = pixelPos - dragPoint;
		renderWindow->setPosition(subPoints);
	}

	if (a_Resize && f_TitleIsTitleWindow) {//resize
		sf::Vector2i subPoints = sf::Vector2i(worldPos.x, worldPos.y) - sf::Vector2i(position.x, position.y);
		sf::Vector2u newSize = sf::Vector2u(subPoints.x + 10, subPoints.y + 10);
		if (pixelPos.x < renderWindow->getPosition().x || pixelPos.y < renderWindow->getPosition().y) {
			size = sf::Vector2f(100, 50);
			renderWindow->setSize(sf::Vector2u(100, 50));
			return;
		}
		else if (newSize.x < 100) {
			renderWindow->setSize(sf::Vector2u(100, newSize.y));
			size = sf::Vector2f(100, newSize.y);
			return;
		}
		else if (newSize.y < 50) {
			renderWindow->setSize(sf::Vector2u(newSize.x, 50));
			size = sf::Vector2f(newSize.x, 50);
			return;
		}
		else {
			renderWindow->setSize(newSize);
			size = sf::Vector2f(subPoints.x + 10, subPoints.y + 10);
		}

		
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if (worldPos.x <= size.x + position.x && worldPos.x >= position.x) {//on Title
			if (worldPos.y >= position.y && worldPos.y <= position.y + 20) {
				a_Drag = true;
				dragPoint = sf::Vector2i(worldPos.x, worldPos.y);
			}
		}
		if (worldPos.x >= size.x + position.x - 20) {//resize
			if (worldPos.y >= position.y + size.y - 20) {
				a_Resize = true;
				dragPoint = sf::Vector2i(worldPos.x, worldPos.y);
			}
		}
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		if (worldPos.x <= size.x + position.x && worldPos.x >= position.x) {//on Title
			if (worldPos.y >= position.y && worldPos.y <= position.y + 20) {
				a_Drag = false;
			}
		}
		if (worldPos.x >= size.x + position.x - 20) {//resize
			if (worldPos.y >= position.y + size.y - 20) {
				a_Resize = false;
			}
		}
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
	if (name == "BLOCK_RENDER" && f_TitleIsTitleWindow) {//! Not implemented
		f_BlockRender = state;
	}

	return false;
}

bool lui::Form::getFlagState(std::string name)
{
	if (name == "TITLE") { return f_Title; }
	if (name == "FORM_IS_WINDOW") { return f_TitleIsTitleWindow; }
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




void lui::Form::createElement(ElementType type)
{
	if (type == ElementType::BUTTON) {
		components.push_back(new Button(sf::Vector2f(30,30), sf::Vector2f(50,20), this));
		components.push_back(new Button(sf::Vector2f(30, 50), sf::Vector2f(50, 20), this));
	}
}

//######################################################################################################################
//#########################################COMPONENTS###################################################################
//######################################################################################################################

lui::Component::Component(sf::Vector2f position, sf::Vector2f size, bool isActive, bool isVisible, Form* attachToForm) 
{
	this->attachToForm = attachToForm;
	this->position = position;
	this->size = size;
	this->active = isActive;
	this->visible = isVisible;
	this->id = this->attachToForm->getCountComponents() +1;
	this->attachToForm->setCountComponents(id);
}

lui::Component::Component(sf::Vector2f position, sf::Vector2f size, Form* attachToForm)
{
	this->attachToForm = attachToForm;
	this->position = position;
	this->size = size;
	this->id = this->attachToForm->getCountComponents() + 1;
	this->attachToForm->setCountComponents(id);
}

int lui::Component::getId()
{
	return id;
}



//######################################################################################################################
//#########################################BUTTON#######################################################################
//######################################################################################################################

void lui::Button::draw()
{
	sf::RectangleShape fon(sf::Vector2f(size.x, size.y));
	fon.setPosition(position.x, position.y);
	fon.setFillColor(sf::Color(0, 0, 0));
	this->attachToForm->renderWindow->draw(fon);

	fon = sf::RectangleShape(sf::Vector2f(size.x - 4, size.y - 4));
	fon.setPosition(position.x + 3, position.y + 3);
	fon.setFillColor(sf::Color(88, 56, 48));
	this->attachToForm->renderWindow->draw(fon);

	text.setCharacterSize(fontSize);
	sf::Vector2i Center = sf::Vector2i((position.x + size.x / 2), (position.y + size.y / 2));
	Center = sf::Vector2i(Center.x - text.getGlobalBounds().width / 2, (Center.y - text.getGlobalBounds().height / 2) - 3);
	text.setPosition(Center.x, Center.y);
	if (state) {
		text.setPosition(Center.x + 1, Center.y + 1);
	}

	this->attachToForm->renderWindow->draw(text);


	sf::Color ColorA = sf::Color(255, 255, 255);
	sf::Color ColorB = sf::Color(128, 128, 128);
	if (state) {
		ColorB = sf::Color(255, 255, 255);
		ColorA = sf::Color(128, 128, 128);
	}


	sf::RectangleShape line;
	line = sf::RectangleShape(sf::Vector2f(size.x - 2, 1)); //Up Up Up
	line.setFillColor(ColorA);
	line.setPosition(position.x + 1, position.y + 1);
	this->attachToForm->renderWindow->draw(line);

	line = sf::RectangleShape(sf::Vector2f(size.y - 2, 1)); //left Up Up
	line.setFillColor(ColorA);
	line.setPosition(position.x + 2, position.y + 1);
	line.rotate(90);
	this->attachToForm->renderWindow->draw(line);

	line = sf::RectangleShape(sf::Vector2f(size.x - 4, 1)); //Up down Up
	line.setFillColor(ColorA);
	line.setPosition(position.x + 2, position.y + 2);
	this->attachToForm->renderWindow->draw(line);

	line = sf::RectangleShape(sf::Vector2f(size.y - 4, 1)); //left down Up
	line.setFillColor(ColorA);
	line.setPosition(position.x + 3, position.y + 2);
	line.rotate(90);
	this->attachToForm->renderWindow->draw(line);

	////////////////////////////////////////////////////////////////////////////////////

	line = sf::RectangleShape(sf::Vector2f(size.x - 3, 1));
	line.setFillColor(ColorB);
	line.setPosition(position.x - 1 + size.x, position.y - 1 + size.y);
	line.rotate(180);
	this->attachToForm->renderWindow->draw(line);

	line = sf::RectangleShape(sf::Vector2f(size.x - 5, 1));
	line.setFillColor(ColorB);
	line.setPosition(position.x - 2 + size.x, position.y - 2 + size.y);
	line.rotate(180);
	this->attachToForm->renderWindow->draw(line);



	line = sf::RectangleShape(sf::Vector2f(size.y - 3, 1));
	line.setFillColor(ColorB);
	line.setPosition(position.x - 2 + size.x, position.y - 1 + size.y);
	line.rotate(270);
	this->attachToForm->renderWindow->draw(line);


	line = sf::RectangleShape(sf::Vector2f(size.y - 4, 1));
	line.setFillColor(ColorB);
	line.setPosition(position.x - 3 + size.x, position.y - 1 + size.y);
	line.rotate(270);
	this->attachToForm->renderWindow->draw(line);




}

lui::Button::Button(sf::Vector2f position, sf::Vector2f size, Form* attachToForm) : Component(position, size, attachToForm)
{
	text.setFont(Resources::getInstance()->getFontByID(0));
	text.setString("button" + std::to_string(id));
}
