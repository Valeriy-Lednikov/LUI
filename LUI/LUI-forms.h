#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include "LUI-Resources.h";
namespace lui {
	static int CountForms = 0;
	

	class Form{
	public:
		Form() { std::cout << "form create " << id << "\n"; }
		Form(sf::RenderWindow* renderWindow) { this->renderWindow = renderWindow; 
		if (renderWindow == NULL) {
			std::cout << "Error init - null" << std::endl;
		}
		std::cout << "form create " << id << "\n";}
		
		
		void draw();
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

		sf::RenderWindow *renderWindow = NULL;
	private:
		int id = ++CountForms;
		std::string titleText = "";
		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Vector2f size = sf::Vector2f(600, 300);
		short transparency = 255;


		//flags
		bool isVisiable = true;
		//flag-style
		bool f_Title = true;
		bool f_TitleContols = false;
		bool f_TitlePick = true;
		bool f_FormPick = false;
	};



}