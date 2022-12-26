#pragma once
#include "LUI.h"


namespace lui {

	void LUI::start(void(*usrStart)(),void(*usrUpdate)(), void(*usrControl)(sf::Event))
	{
		Resources::getInstance()->initialization();
		renderWindow.create(sf::VideoMode(800, 600), "LUI", sf::Style::None);
		renderWindow.setFramerateLimit(100);
		

		usrStart();
		while (renderWindow.isOpen())
		{

			Event event;
			while (renderWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Resized) {
					float w = static_cast<float>(event.size.width);
					float h = static_cast<float>(event.size.height);
					renderWindow.setView(
						sf::View(
							sf::Vector2f(w / 2.0, h / 2.0),
							sf::Vector2f(w, h)
						)
					);
				}


				usrControl(event);
				for (int i = 0; i < luiForms.size(); i++) {
					luiForms.at(i)->update(event);
				}


				if (event.type == Event::Closed)
					renderWindow.close();
				if (event.type == Event::KeyPressed) {

					if (event.key.code == sf::Keyboard::Escape)
					{
						renderWindow.close();
					}

					if (event.key.code == sf::Keyboard::D)
					{
						//std::cout << &renderWindow << "\t" << lui::TargetWindow << "\n";
						//form1.draw();

					}


				}
			}
			if (!blockRender) {
				renderWindow.clear(Color(0, 0, 0));
				usrUpdate();
				render();

				renderWindow.display();
			}
		}

	}

	Form* LUI::createForm()
	{
		Form* form = new Form;
		form->setRenderWindow(&renderWindow);
		luiForms.push_back(form);
		return form;
	}
	void LUI::render()
	{
		//std::cout << "size vector - " << luiForms.size() << "\n";
		for (int i = 0; i < luiForms.size(); i++) {
			luiForms.at(i)->draw();
			//std::cout << "render\n";
		}
	}
}
