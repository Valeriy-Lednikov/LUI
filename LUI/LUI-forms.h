#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <SFML/Window/Mouse.hpp>
#include "LUI-Resources.h";


namespace lui {
	static int CountForms = 0;
	bool PointInRect(sf::Vector2i point, sf::Vector2i rectA, sf::Vector2i rectB);


	enum class Attach {
		UP,
		RIGHT_UP,
		RIGHT,
		RIGHT_DOWN,
		DOWN,
		LEFT_DOWN,
		LEFT,
		LEFT_UP,
		CENTER
	};

	enum class ElementType {
		BUTTON
	};

	enum class Events
	{
		MOUSE_IN,
		MOUSE_OUT,
		MOUSE_ON,
		PRESS,
		RELEASE,
		CLICK
	};
	std::string EventsToSting(Events event);

	struct Event_function
	{
		Events event;
		void(*function)();
	};



	class Form;
	class Component;
	class Button;


	class Form{
	public:
		Form() { std::cout << "form create " << id << "\n"; }
		Form(sf::RenderWindow* renderWindow);
		
		
		void draw();
		void update(sf::Event event);

		int getId();
		void setRenderWindow(sf::RenderWindow *renderWindow);
		void setTitleText(std::string text);
		
		void setSize(sf::Vector2f size);
		
		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition();
		
		bool setFlag(std::string name, bool state);
		bool getFlagState(std::string name);

		void setTransparency(short transparency);
		int getTransparency();

		int getCountComponents();
		void setCountComponents(int count);

		sf::RenderWindow *renderWindow = NULL;

		int createElement(ElementType type);
		void attachComponent(Component* element);
		void updateComponents();

		Component* getFocus();
	private:
		void sortComponentsByZindex();
		void executeEventComponent(lui::Events getEvent, Component* component);



		int countComponents = 0;
		std::vector<Component*> components;
		Component* focus = NULL;

		int id = ++CountForms;
		std::string titleText = "";
		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f size = sf::Vector2f(600, 300);
		short transparency = 255;



		//flags
		bool isVisiable = true;
		//action flags and data
		bool a_Drag = false;
		bool a_Resize = false;
		sf::Vector2i dragPoint;
		//flag-style
		bool f_TitleIsTitleWindow = false;//title this form = title window
		bool f_BlockRender = false;//! Not implemented

		bool f_Title = true;

		bool f_TitleContols = false;
		bool f_TitleCloseButton = true;
		bool f_TitleResizeButton = true;
		bool f_TitleMinimizeButton = false;

		bool f_TitlePick = true;
		bool f_FormPick = false;


	};







	class Component
	{
	public:

		Component(sf::Vector2f position, sf::Vector2f size, bool isActive, bool isVisible, Form *attachToForm) ;
		Component(sf::Vector2f position, sf::Vector2f size, Form* attachToForm);
		Component(){};
		virtual void draw() {}
		virtual ~Component() = default;
		
		int getId();

		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f size = sf::Vector2f(0, 0);
		bool active = true;
		bool visible = true;
		int id = 0;
		int zIndex = 1;
		Attach attach = Attach::LEFT_UP;
		Form* attachToForm;
		std::vector<Event_function> events;

		Event_function findEventFunction(lui::Events event);
		void attachEvent(void (*function)(), Events event);
	};




	class Button :public Component {
	public:
		void draw();
		Button(sf::Vector2f position, sf::Vector2f size, Form* attachToForm);
		Button() : Component() {}
		
		void initialization(sf::Vector2f size, sf::Vector2f position, std::string text);
		void initialization(sf::Vector2f size, sf::Vector2f position, std::string text, Form* attachToForm);
		sf::Text text;
		bool state = false;
		sf::Color backgroundColor = sf::Color(88, 56, 48);
		sf::Color fontColor = sf::Color(0, 0, 0);
		bool isToggle = false;
		int fontSize = 13;
	};
	

	class TextField : public Component {
	public:
		void draw();
		TextField() : Component() {}
		TextField(sf::Vector2f position, sf::Vector2f size, Form* attachToForm);
		void initialization(sf::Vector2f size, sf::Vector2f position, std::string text, Form* attachToForm);
		sf::Text text;
		sf::Text backgroundText;
		int fontSize = 11;
	private:

	};
}

