#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
//#pragma comment( lib, "lib/LUI-Resource-Lib.lib" )
#include <LUI-Resource-Lib.h>

#define LUI_DEBUG




namespace lui {
	struct ColorStyle {
		std::vector<sf::Color> color;
	};
	class Resources {
		struct FontData
		{
			sf::Font font;
			double maxHeight;
			FontData(sf::Font font, double maxHeight) { this->font = font; this->maxHeight = maxHeight; }
		};


	public:
		static Resources* getInstance() {
			static Resources instance;
			return &instance;
		}
		void initialization() {

			//Arial font - id(0)
			sf::Font arialF;
			int size;
			char* cF = LuiResource::Resource::getInstance()->getResource(0, size);
			arialF.loadFromMemory(cF, size);
			fonts.push_back(FontData(arialF, 28));
			//-----


			CS_main.color.push_back(sf::Color(88, 56, 48));





			colorStyles.push_back(CS_main);

		}
		void closeApp() { exit(0); }

		sf::Font& getFontByID(int id) {
			return fonts.at(id).font;
		}
		double getMaxHeightFont(int id) {
			sf::Text text;
			text.setFont(Resources::getInstance()->getFontByID(0));
			text.setString("aAbBcCdDeEfgGhHiIjJKlLmMnNyY1{[<!&?:*¹;");
			return text.getGlobalBounds().height;
		}


		sf::Color getColor(int styleId, int ColorId) {
			return colorStyles.at(styleId).color[ColorId];
		}

	private:
		std::vector<FontData> fonts;
		Resources() {}
		ColorStyle CS_main;
		std::vector<ColorStyle> colorStyles;
	};




}