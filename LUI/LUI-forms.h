#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <SFML/Window/Mouse.hpp>
#include "LUI-Resources.h";
namespace lui {
	static int CountForms = 0;
	

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
	private:
		int countComponents = 0;
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

	class Component : public Form
	{
	public:

		Component(sf::Vector2f position, sf::Vector2f size, bool isActive, bool isVisible);
		Component(sf::Vector2f position, sf::Vector2f size);
		virtual void draw() {}
		virtual ~Component() = default;

		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f size = sf::Vector2f(0, 0);
		bool active = true;
		bool visible = true;
		int id = 0;

	};

	class Button :private Component {
	public:
	private:

	};

}