#include "LUI.h"

lui::LUI ui;
lui::Form* myForm;
lui::Button button;
lui::Button button2;
lui::TextField textField;

int a = 0;

void ButtonFunkP() {
	std::cout << "Button PRESS " << "\n";
}
void ButtonFunkR() {
	std::cout << "Button RELEASE " << "\n";
}
void ButtonFunkC() {
	std::cout << "Button CLICK " << "\n";
}

//void Button1C() {
//	button.zIndex++;
//	myForm->updateComponents();
//	std::cout << "button 1 z = " << button.zIndex << "\n";
//}
//void Button2C() {
//	button2.zIndex ++;
//	myForm->updateComponents();
//	std::cout << "button 2 z = " << button2.zIndex << "\n";
//}

void Start() {
	myForm = ui.createForm();
	myForm->setTitleText("Hi! This is Form!");
	myForm->setFlag("FORM_IS_WINDOW", true);



	button.initialization(sf::Vector2f(100, 60), sf::Vector2f(200, 80), "Button 1", myForm);
	myForm->attachComponent(&button);
	button.attachEvent(ButtonFunkP, lui::Events::PRESS);
	button.attachEvent(ButtonFunkR, lui::Events::RELEASE);
	button.attachEvent(ButtonFunkC, lui::Events::CLICK);

	//button2.initialization(sf::Vector2f(100, 60), sf::Vector2f(230, 90), "Button 2", myForm);
	//myForm->attachComponent(&button2);
	//button2.attachEvent(Button2C, lui::Events::CLICK);




	textField.initialization(sf::Vector2f(100, 30), sf::Vector2f(20, 50), "print", myForm);
	myForm->attachComponent(&textField);
	

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