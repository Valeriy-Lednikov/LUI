#include "LUI.h"

lui::LUI ui;
lui::Form* myForm;
lui::Button button;
lui::Button button2;
lui::TextField textField;
lui::Slider slider;




void Button1C() {
	button.zIndex++;
	myForm->updateComponents();
	button.text.setString(textField.text.getString());
}
void Button2C() {
	button2.zIndex ++;
	myForm->updateComponents();
	button2.text.setString(textField.text.getString());
}

void Start() {
	myForm = ui.createForm();
	myForm->setTitleText("Hi! This is Form!");
	myForm->setFlag("FORM_IS_WINDOW", true);
	myForm->setSize(sf::Vector2f(1000, 700));



	button.initialization(sf::Vector2f(100, 60), sf::Vector2f(200, 80), "Button 1", myForm);
	button.zIndex++;
	button.attachEvent(Button1C, lui::Events::CLICK);

	button2.initialization(sf::Vector2f(100, 60), sf::Vector2f(260, 90), "Button 2", myForm);
	button2.attachEvent(Button2C, lui::Events::CLICK);

	textField.initialization(sf::Vector2f(100, 30), sf::Vector2f(20, 50), "print", myForm);

	slider.initialization(sf::Vector2f(100, 6), sf::Vector2f(30, 30), myForm);
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