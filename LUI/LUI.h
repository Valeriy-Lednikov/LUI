#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "LUI-forms.h"
#include <cstddef>
#include <bitset>
#include <Windows.h>
#include "LUI-Resources.h";


using namespace sf;

namespace lui {

	class LUI {
	public:
		void start(void(*)(), void(*)(), void(*)(sf::Event));
		Form* createForm();
		sf::RenderWindow renderWindow;
		bool blockRender = false;
	private:
		bool leftMouseState = false;
		std::vector<Form*> luiForms;
		void render();
		void updateControll(sf::Event event);
	};
}