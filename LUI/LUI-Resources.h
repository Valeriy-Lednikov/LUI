#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
//#pragma comment( lib, "lib/LUI-Resource-Lib.lib" )
#include <LUI-Resource-Lib.h>


namespace lui {
	class Resources {
	public:
		static Resources* getInstance() {
			static Resources instance;
			return &instance;
		}
		void initialization() {
			
			//Arial font - id(0)
			sf::Font arialF;
			int size;
			char *cF = LuiResource::Resource::getInstance()->getResource(0, size);
			arialF.loadFromMemory(cF, size);
			fonts.push_back(arialF);
			//-----

		}
		sf::Font &getFontByID(int id) {
			return fonts.at(id);

		}
		
	private:
		std::vector<sf::Font> fonts ;
		Resources(){}
	};
}