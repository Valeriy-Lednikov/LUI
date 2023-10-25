#pragma once
#include "LUI.h"


namespace lui {

	void LUI::start(void(*usrStart)(), void(*usrUpdate)(), void(*usrControl)(sf::Event))
	{
		sf::RenderWindow* tempRenderWindow = RenderController::getInstance()->renderWindow;


		std::cout << "2 " << tempRenderWindow << "\n";
		if (tempRenderWindow == NULL) {
			std::cout << "Render Window not setup\n";
			return;
		}

		Resources::getInstance()->initialization();
		//sf::ContextSettings settings;
		//settings.antialiasingLevel = 2;
		//if (standartWindow) {
		//	tempRenderWindow->create(sf::VideoMode(800, 600), "LUI", sf::Style::Default, settings);
		//}
		//else
		//{
		//	tempRenderWindow->create(sf::VideoMode(800, 600), "LUI", sf::Style::None, settings);
		//}
		//tempRenderWindow->setFramerateLimit(100);

		//HWND hwnd = tempRenderWindow->getSystemHandle();
		//LONG_PTR new_style = WS_SYSMENU;
		//SetWindowLong(hwnd, GWL_EXSTYLE, new_style);


		camera.setCenter(sf::Vector2f(tempRenderWindow->getSize().x, tempRenderWindow->getSize().y) / 2.f);
		camera.setSize(sf::Vector2f(tempRenderWindow->getSize().x, tempRenderWindow->getSize().y));
		cameraPos = sf::Vector2f(tempRenderWindow->getSize().x, tempRenderWindow->getSize().y) / 2.f;

		usrStart();




		this->userUpd = usrUpdate;
		this->userControll = usrControl;

		if (autoUpdate) {
			while (tempRenderWindow->isOpen()) {
				update();
			}
		}

	}



	void LUI::update()
	{
		sf::RenderWindow* tempRenderWindow = RenderController::getInstance()->renderWindow;
		if (tempRenderWindow->isOpen())
		{
			if (drawFPSinTitle) {
				frame_count++;
				elapsed_time = clock.getElapsedTime().asSeconds();
				if (elapsed_time >= 1)
				{
					avg_fps = frame_count / elapsed_time;
					std::string a = "" + std::to_string(avg_fps);

					tempRenderWindow->setTitle(sf::String(a));
					frame_count = 0;
					elapsed_time = 0;
					clock.restart();
				}
			}


			Event event;
			while (tempRenderWindow->pollEvent(event))
			{
				if (event.type == sf::Event::Resized) {
					float w = static_cast<int>(event.size.width);
					float h = static_cast<int>(event.size.height);
					double roundedW = std::ceil(w / 2) * 2;
					double roundedH = std::ceil(h / 2) * 2;
					camera.setSize(roundedW, roundedH);
					camera.setCenter(roundedW / 2, roundedH / 2);
					tempRenderWindow->setSize(Vector2u(roundedW, roundedH));
					std::cout << "W " << roundedW << " H " << roundedH << "\n";

				}
				if (event.type == sf::Event::Closed) {
					tempRenderWindow->close();
				}


				userControll(event);
				for (int i = 0; i < luiForms.size(); i++) {
					luiForms.at(i)->update(event);
				}

			}
			if (!blockRender) {
				if (autoClear) {
					tempRenderWindow->clear(Color(0, 0, 0));
				}
				userUpd();
				if (autoSetView) {
					tempRenderWindow->setView(camera);
				}
				render();
				if (autoDisplay) {
					tempRenderWindow->display();
				}
			}
		}
	}



	Form* LUI::createForm()
	{
		sf::RenderWindow* tempRenderWindow = RenderController::getInstance()->renderWindow;
		Form* form = new Form;
		form->setRenderWindow(tempRenderWindow);
		luiForms.push_back(form);
		return form;
	}


	void LUI::render()
	{
		for (int i = 0; i < luiForms.size(); i++) {
			luiForms.at(i)->draw();
		}
	}



}
