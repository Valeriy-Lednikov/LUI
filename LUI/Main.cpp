#include "LUI.h"

lui::LUI ui;
lui::Form* myForm;
lui::Button button;
lui::TextField tfi;

int a = 0;

void ButtonFunk1() {
	std::cout << "Button PRESS " << "\n";
}
void ButtonFunk2() {
	std::cout << "Button RELEASE " << "\n";
}
void ButtonFunk3() {
	std::cout << "Button CLICK " << "\n";
}

void Start() {
	myForm = ui.createForm();
	myForm->setTitleText("Hi! This is Form!");
	myForm->setFlag("FORM_IS_WINDOW", true);

	//button.initialization(sf::Vector2f(300, 100), sf::Vector2f(100, 30), "Button 1", myForm);
	//myForm->attachComponent(&button);
	button.attachEvent(ButtonFunk1, lui::Events::PRESS);
	button.attachEvent(ButtonFunk2, lui::Events::RELEASE);
	button.attachEvent(ButtonFunk3, lui::Events::CLICK);

	tfi.initialization(sf::Vector2f(100, 30), sf::Vector2f(20, 50), "print", myForm);
	myForm->attachComponent(&tfi);
	

}


void Control(sf::Event event) {

}

void Update() {

}

int main()
{
	ui.start(Start, Update, Control);
	return 0;
}





//lui::Form* form1;

//void Start() {
//
//	
//	form1 = lui.createForm();
//	form1->setTitleText("my First Form");
//	form1->setSize(sf::Vector2f(800, 600));
//	form1->setFlag("FORM_IS_WINDOW", true);
//	lui.renderWindow.setFramerateLimit(0);
//
//}
//
//void Control(sf::Event event) {
//
//	
//}
//
//void Update() {
//
//	
//}

//int main()
//{
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//
//	lui.start(Start, Update, Control);
//	return 0;
//}