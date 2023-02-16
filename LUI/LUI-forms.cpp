#pragma once
#include "LUI-forms.h"
class Form;
class Component;
class Button;


bool lui::PointInRect(sf::Vector2i point, sf::Vector2i rectA, sf::Vector2i rectB)
{
	if (point.x > rectA.x && point.x<rectB.x && point.y>rectA.y && point.y < rectB.y) {
		return true;
	}
	else
	{
		return false;
	}
}

std::string lui::EventsToSting(Events getEvent)
{
	std::string t = "";
	if (getEvent == Events::PRESS) {
		return std::string("PRESS");
	}
	if (getEvent == Events::RELEASE) {
		return std::string("RELEASE");
	}
	if (getEvent == Events::CLICK) {
		return std::string("CLICK");
	}
	if (getEvent == Events::MOUSE_IN) {
		return std::string("MOUSE_IN");
	}
	return std::string("Error - Unknown Event");
}

std::string lui::ClassToString(Component* component)
{
	if (dynamic_cast<Button*>(component)) {
		return std::string("Button");
	}
	if (dynamic_cast<TextField*>(component)) {
		return std::string("TextField");
	}
	return std::string();
}



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

	sf::CircleShape triangle(10, 3);
	triangle.setPosition(renderWindow->getSize().x - 30, renderWindow->getSize().y- 30); // устанавливаем начальную позицию справа от круга
	triangle.setFillColor(sf::Color::Blue); // устанавливаем цвет треугольника - синий
	renderWindow->draw(triangle);




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
		components[i]->draw();
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


	//UpdateComponents
	//###########################################################################################################

	for (int i = components.size() - 1; i >= 0; i--) {
		sf::Vector2i currentComponentPosition = sf::Vector2i(components[i]->position);
		sf::Vector2i currentComponentSize = sf::Vector2i(components[i]->size);


		//standat
		if (PointInRect(sf::Mouse::getPosition(*renderWindow), currentComponentPosition, currentComponentPosition + currentComponentSize)) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				executeEventComponent(lui::Events::PRESS, components[i]);

				if (dynamic_cast<Button*>(components[i]))
				{
					if (!dynamic_cast<Button*>(components[i])->isToggle) {
						focus = components[i];
						dynamic_cast<Button*>(components[i])->state = true;
					}
				}

				if (dynamic_cast<TextField*>(components[i]))
				{
					focus = components[i];
				}
				return;
				
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && focus == components[i]) {
				if (dynamic_cast<Button*>(components[i]))
				{
					if (!dynamic_cast<Button*>(components[i])->isToggle) {
						executeEventComponent(lui::Events::RELEASE, components[i]);
						dynamic_cast<Button*>(components[i])->state = false;
						focus = NULL;
					}
				}

				if (dynamic_cast<TextField*>(components[i]))
				{
					focus = components[i];
				}
				executeEventComponent(lui::Events::CLICK, components[i]);
				return;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && focus == components[i]) {
			executeEventComponent(lui::Events::RELEASE, components[i]);
			if (dynamic_cast<Button*>(components[i]))
			{
				dynamic_cast<Button*>(components[i])->state = false;
				focus = NULL;
			}
			if (dynamic_cast<TextField*>(components[i]))
			{
				focus = NULL;
			}
			return;
		}
		//#######








		//######################################################################################
		if (dynamic_cast<TextField*>(components[i])) {
			TextField* tf = dynamic_cast<TextField*>(components[i]);

			if (event.type == sf::Event::TextEntered && focus == components[i])
			{
				std::string TSting = tf->text.getString();
				if (event.text.unicode != 8)
					tf->text.setString(tf->text.getString() + event.text.unicode);
				else {
					if (!TSting.empty()) {
						TSting.pop_back();
						tf->text.setString(TSting);
					}
				}
				//return;
			}
		}
	}

	//if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
	//	focus = NULL;
	//}


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

sf::Vector2f lui::Form::getSize()
{
	return this->size;
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

int lui::Form::createElement(ElementType type)
{

	if (type == ElementType::BUTTON) {
		Button* t = new Button(sf::Vector2f(30, 30), sf::Vector2f(50, 20), this);

		components.push_back(t);
		return t->getId();

	}

}

void lui::Form::attachComponent(Component* element)
{
	element->id = this->getCountComponents() + 1;
	components.push_back(element);
	countComponents++;
	this->sortComponentsByZindex();
}

void lui::Form::updateComponents()
{
	this->sortComponentsByZindex();
}

lui::Component* lui::Form::getFocus()
{
	return focus;
}

void lui::Form::sortComponentsByZindex()
{
	for (int i = 0; i < components.size(); i++) {
		if (i != components.size() - 1 && components.size() != 1) {
			if (components.at(i + 1)->zIndex < components.at(i)->zIndex) {
				std::swap(components.at(i), components.at(i + 1));
			}
		}
	}
}

void lui::Form::executeEventComponent(lui::Events getEvent, Component* component)
{
#ifdef LUI_DEBUG
	std::cout << "ComponentId - " << component->id << " " << ClassToString(component) << " Event - " << EventsToSting(getEvent) << std::endl;
#endif // LUI_DEBUG

	Event_function Ef = component->findEventFunction(getEvent);
	if (Ef.function != NULL) {
		Ef.function();
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
	this->id = this->attachToForm->getCountComponents() + 1;
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

lui::Event_function lui::Component::findEventFunction(lui::Events event)
{
	Event_function funk;
	funk.function = NULL;
	for (int i = 0; i < this->events.size(); i++) {
		if (this->events[i].event == event) {
			funk.event = this->events[i].event;
			funk.function = this->events[i].function;
		}
	}
	return funk;
}

void lui::Component::attachEvent(void(*function)(), Events event)
{

	Event_function* ev = new Event_function();
	ev->event = event;
	ev->function = function;
	events.push_back(*ev);

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
	fon.setFillColor(backgroundColor);
	this->attachToForm->renderWindow->draw(fon);

	text.setCharacterSize(fontSize);
	text.setFillColor(fontColor);
	sf::Vector2i Center = sf::Vector2i((position.x + size.x / 2), (position.y + size.y / 2));
	Center = sf::Vector2i(Center.x - text.getGlobalBounds().width / 2, (Center.y - text.getGlobalBounds().height / 2) - 3);
	text.setPosition(Center.x, Center.y);
	if (state) {
		text.setPosition(Center.x - 1, Center.y - 1);
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


	/*if(activateFuntion != NULL)
		activateFuntion();*/

}

lui::Button::Button(sf::Vector2f position, sf::Vector2f size, Form* attachToForm) : Component(position, size, attachToForm)
{
	//text.setFont(Resources::getInstance()->getFontByID(0));
	//text.setString("button" + std::to_string(id));
	//activateFuntion = NULL;
}



void lui::Button::initialization(sf::Vector2f size, sf::Vector2f position, std::string text)
{
	this->text.setFont(Resources::getInstance()->getFontByID(0));
	this->size = size;
	this->position = position;
	this->text.setString(text);
}

void lui::Button::initialization(sf::Vector2f size, sf::Vector2f position, std::string text, Form* attachToForm)
{
	this->text.setFont(Resources::getInstance()->getFontByID(0));
	this->size = size;
	this->position = position;
	this->text.setString(text);
	this->attachToForm = attachToForm;
	attachToForm->attachComponent(this);
}






//######################################################################################################################
//#########################################TEXT FIELD###################################################################
//######################################################################################################################


void lui::TextField::draw()
{
	sf::RectangleShape fon(sf::Vector2f(size.x, size.y));
	fon.setPosition(position.x, position.y);
	if (this->attachToForm->getFocus() == this) {
		fon.setFillColor(sf::Color(255, 0, 0));
	}
	else {
		fon.setFillColor(sf::Color(0, 0, 0));
	}
	this->attachToForm->renderWindow->draw(fon);

	fon.setPosition(position.x + 1, position.y + 1);
	fon.setSize(sf::Vector2f(size.x - 2, size.y - 2));
	fon.setFillColor(sf::Color(64, 128, 128));
	this->attachToForm->renderWindow->draw(fon);


	sf::Vector2i Center = sf::Vector2i((position.x), (position.y + size.y / 2));
	if (text.getString() == "") {
		Center = sf::Vector2i(Center.x + 5, (Center.y - Resources::getInstance()->getMaxHeightFont(0)/4));
		backgroundText.setPosition(Center.x, Center.y);
		this->attachToForm->renderWindow->draw(backgroundText);
	}
	else {
		if (text.getGlobalBounds().width < size.x - 10) {
			Center = sf::Vector2i(Center.x + 5, (Center.y - Resources::getInstance()->getMaxHeightFont(0)/4));
			text.setPosition(Center.x, Center.y);
			this->attachToForm->renderWindow->draw(text);
		}
	}
}



lui::TextField::TextField(sf::Vector2f position, sf::Vector2f size, Form* attachToForm) : Component(position, size, attachToForm)
{
	this->text.setFont(Resources::getInstance()->getFontByID(0));
	this->size = size;
	this->position = position;

}

void lui::TextField::initialization(sf::Vector2f size, sf::Vector2f position, std::string backgroundText, Form* attachToForm)
{
	this->text.setFont(Resources::getInstance()->getFontByID(0));
	this->backgroundText.setFont(Resources::getInstance()->getFontByID(0));

	this->backgroundText.setCharacterSize(fontSize);
	this->backgroundText.setFillColor(sf::Color(255, 255, 255, 128));
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(sf::Color(255, 255, 255, 255));



	this->size = size;
	this->position = position;
	this->backgroundText.setString(backgroundText);
	this->attachToForm = attachToForm;

	attachToForm->attachComponent(this);
}

//######################################################################################################################
//#########################################SLIDER#######################################################################
//######################################################################################################################


void lui::Slider::draw()
{
	double radiusBall = size.y / 2;
	sf::RectangleShape fon(sf::Vector2f(size.x - 2 * radiusBall, size.y));
	fon.setFillColor(sf::Color(30, 60, 50, 255));
	fon.setPosition(position.x + radiusBall, position.y);
	this->attachToForm->renderWindow->draw(fon);

	sf::CircleShape ball(size.y / 2);
	ball.setFillColor(sf::Color(30, 60, 50, 255));
	ball.setPosition(position.x, position.y);
	this->attachToForm->renderWindow->draw(ball);
	ball.setPosition(position.x + size.x - size.y, position.y);
	this->attachToForm->renderWindow->draw(ball);

	sf::CircleShape controllBall(size.y);
	controllBall.setFillColor(sf::Color::Red);
	controllBall.setPosition(position.x + size.x / 2, position.y + size.y/2 - controllBall.getRadius());
	this->attachToForm->renderWindow->draw(controllBall);
}

void lui::Slider::initialization(sf::Vector2f size, sf::Vector2f position, Form* attachToForm)
{
	this->size = size;
	this->position = position;
	this->attachToForm = attachToForm;
	attachToForm->attachComponent(this);
}
