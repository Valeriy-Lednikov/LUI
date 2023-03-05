#pragma once
#include "LUI.h"


namespace lui {

	void LUI::start(void(*usrStart)(),void(*usrUpdate)(), void(*usrControl)(sf::Event))
	{

		if (renderWindow == NULL) {
			std::cout << "Render Window not setup\n";
			return;
		}

		Resources::getInstance()->initialization();
		sf::ContextSettings settings;
		settings.antialiasingLevel = 2;
		if (standartWindow) {
			renderWindow->create(sf::VideoMode(800, 600), "LUI", sf::Style::Default, settings);
		}
		else
		{
			renderWindow->create(sf::VideoMode(800, 600), "LUI", sf::Style::None, settings);
		}
		renderWindow->setFramerateLimit(100);

		HWND hwnd = renderWindow->getSystemHandle();
		LONG_PTR new_style = WS_SYSMENU;
			SetWindowLong(hwnd, GWL_EXSTYLE,new_style);

		usrStart();
		while (renderWindow->isOpen())
		{

			Event event;
			while (renderWindow->pollEvent(event))
			{
				if (event.type == sf::Event::Resized) {
					float w = static_cast<float>(event.size.width);
					float h = static_cast<float>(event.size.height);
					renderWindow->setView(
						sf::View(
							sf::Vector2f(w / 2.0, h / 2.0),
							sf::Vector2f(w, h)
						)
					);
				}

				updateControll(event);
				usrControl(event);
				for (int i = 0; i < luiForms.size(); i++) {
					luiForms.at(i)->update(event);
				}


				if (event.type == Event::Closed)
					renderWindow->close();
				if (event.type == Event::KeyPressed) {

					if (event.key.code == sf::Keyboard::Escape)
					{
						renderWindow->close();
					}

				}
			}
			if (!blockRender) {
				renderWindow->clear(Color(0, 0, 0));
				usrUpdate();
				render();

				renderWindow->display();
			}
		}

	}

	Form* LUI::createForm()
	{
		Form* form = new Form;
		form->setRenderWindow(renderWindow);
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
	void LUI::updateControll(sf::Event event)
	{
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		//	leftMouse = true;
		//}
		//else {
		//	if(leftMouse = true){
		//		false;
		//	}
		//}
		////if (PointInRect(sf::Mouse::getPosition(*Window), Components[i]->Position, Components[i]->Position + Components[i]->Size)) {

	}


}
