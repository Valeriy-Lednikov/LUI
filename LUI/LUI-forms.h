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
		void setSize(sf::Vector2i size);
		void setPosition(sf::Vector2i position);
		bool setFlag(std::string name, bool state);


		sf::RenderWindow *renderWindow = NULL;
	private:
		int id = ++CountForms;
		std::string titleText = "";
		sf::Vector2i position = sf::Vector2i(0, 0);
		sf::Vector2f size = sf::Vector2f(600, 300);

		//flags
		bool f_Title = true;
		bool f_TitleContols = false;
		bool f_TitlePick = true;
		bool f_FormPick = false;
	};

}