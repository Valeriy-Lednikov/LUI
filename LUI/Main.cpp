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
lui::Form* form1;








bool f = false;


void Start() {

	form1 = ui.createForm();
	form1->setTitleText("my First Form");
	form1->setSize(sf::Vector2f(800, 600));


}

void Control(sf::Event event) {
	if (event.key.code == sf::Keyboard::D)
	{
		form1->setTransparency(form1->getTransparency() - 1);
	}
	if (event.key.code == sf::Keyboard::A)
	{
		form1->setTransparency(form1->getTransparency() + 1);
	}

	
}

void Update() {

	if (f == false) {
		form1->setTransparency(form1->getTransparency() - 1);
	}
	else{
		form1->setTransparency(form1->getTransparency() + 1);
	}
	if (form1->getTransparency() == 0 || form1->getTransparency() == 255) {
		f = !f;
	}
	//form1->setPosition(Vector2f(form1->getPosition().x + 1, form1->getPosition().y));
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ui.start(Start, Update, Control);
	return 0;
}