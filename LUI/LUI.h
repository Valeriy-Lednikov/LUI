#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "LUI-forms.h"
#include <cstddef>
#include <bitset>
#include <Windows.h>
#include "LUI-Resources.h";
#include <random>
#include "LUI-render.h"
#include <cmath>
using namespace sf;

namespace lui {


	class RenderController {
	private:
		static RenderController* instance; // ����������� ��������� �� ������������ ���������

		// ��������� �����������, ����� ������������� �������� ����������� �����
		RenderController() {}

	public:
		// ����� ��� ��������� ���������� RenderController
		static RenderController* getInstance() {
			if (instance == nullptr) {
				instance = new RenderController();
			}
			return instance;
		}

		sf::RenderWindow* renderWindow;

	
	};




	class LUI {
	public:

		void start(void(*)(), void(*)(), void(*)(sf::Event));
		Form* createForm();

		bool blockRender = false;
		bool standartWindow = true;

		bool autoSetView = true;
		bool autoUpdate = true;
		bool autoClear = true;
		bool autoDisplay = true;
		bool drawFPSinTitle = true;

		void update();
		void (*userUpd)();
		void (*userControll)(sf::Event);

		sf::View camera;
		sf::Vector2f cameraPos = { 0.f, 0.f };
	private:
		sf::Clock clock;
		float elapsed_time = 0;
		int frame_count = 0;
		float avg_fps = 0;
		int avg = 1;



		bool leftMouseState = false;
		std::vector<Form*> luiForms;
		void render();
	};


	static sf::Color RandomColor() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 255);

		return sf::Color(dis(gen), dis(gen), dis(gen), 255);
	}
	static sf::Color RandomColorA() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 255);

		return sf::Color(dis(gen), dis(gen), dis(gen), dis(gen));
	}

	static void getCodeTimeVoid(void* aa()) {
		auto start = std::chrono::high_resolution_clock::now();
		aa;
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		std::cout << "time: " << duration.count() << " ns" << std::endl;
	}
}