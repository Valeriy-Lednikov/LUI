// MPCV.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <bitset>
#include <vector>
#include <Windows.h>
#include "LUI.h"

lui::LUI ui;
using namespace sf;


void Start() {

	lui::Form* form1 = ui.createForm();
	form1->setTitleText("my First Form");
}

void Control(sf::Event event) {
	if (event.key.code == sf::Keyboard::D)
	{
		std::cout << "hi\n";
	}
}

void Update() {

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ui.start(Start, Update, Control);
	return 0;
}