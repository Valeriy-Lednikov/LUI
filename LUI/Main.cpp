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




void Start() {

	form1 = ui.createForm();
	form1->setTitleText("my First Form");
	form1->setSize(sf::Vector2f(800, 600));
	form1->setFlag("FORM_IS_WINDOW", true);
	ui.renderWindow.setFramerateLimit(0);

}

void Control(sf::Event event) {

	
}

void Update() {

	//form1->setPosition(Vector2f(form1->getPosition().x + 1, form1->getPosition().y));
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ui.start(Start, Update, Control);
	return 0;
}