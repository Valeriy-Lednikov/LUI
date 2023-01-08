#include "LUI.h"

lui::LUI ui;
lui::Form* myForm;

void Start() {
	myForm = ui.createForm();
	myForm->setTitleText("Hi! This is Form!");
	myForm->createElement(lui::ElementType::BUTTON);
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