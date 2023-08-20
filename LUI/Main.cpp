#include "LUI.h"
sf::RenderWindow *globalRenderWindow = new sf::RenderWindow;
float cameraSpeed = 5.f;
sf::RectangleShape box;



lui::LUI ui;
lui::Form* myForm;
lui::Button button;
lui::Button button2;
lui::TextField textField;
lui::Slider slider;
lui::Label label;


using namespace std;
using namespace sf;

void Button1C() {
	label.backColor = lui::RandomColor();
}
void Button2C() {
	button2.zIndex ++;
	myForm->updateComponents();
	button2.text.setString(textField.text.getString());
}

void Start() {
	myForm = ui.createForm();
	myForm->setTitleText("Hi! This is Form!");
	//myForm->setFlag("FORM_IS_WINDOW", true);
	myForm->setSize(sf::Vector2f(500, 700));



	button.initialization(sf::Vector2f(100, 60), sf::Vector2f(200, 80), "Button 1", myForm);
	button.zIndex++;
	button.attachEvent(Button1C, lui::Events::CLICK);

	button2.initialization(sf::Vector2f(100, 60), sf::Vector2f(260, 90), "Button 2", myForm);
	button2.attachEvent(Button2C, lui::Events::CLICK);

	textField.initialization(sf::Vector2f(100, 30), sf::Vector2f(20, 50), "print", myForm);
	label.initialization(Vector2f(30, 30), Vector2f(20, 120), "Hi", myForm);
	label.sf_text.setCharacterSize(30);

	slider.initialization(sf::Vector2f(100, 6), sf::Vector2f(30, 30), myForm);


}


void Control(sf::Event event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		 ui.cameraPos.y -= cameraSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		ui.cameraPos.y += cameraSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		ui.cameraPos.x -= cameraSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		ui.cameraPos.x += cameraSpeed;

	// Set the new camera position
	ui.camera.setCenter(ui.cameraPos);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
	}


	if (event.type == sf::Event::LostFocus)
		cout << "Out Focus\n";

	if (event.type == sf::Event::GainedFocus)
		cout << "In Focus\n";
}

void Update() {
	
}

int main()
{

	box.setFillColor(sf::Color::Blue);
	box.setPosition(Vector2f(20, 20));
	box.setSize(Vector2f(30, 30));


	ui.renderWindow = globalRenderWindow;
	ui.autoUpdate = false;
	ui.autoClear = false;
	ui.autoDisplay = false;
	ui.start(Start, Update, Control);
	

	while (ui.renderWindow->isOpen()) {

		

		ui.renderWindow->clear();

		ui.update();


		//globalRenderWindow->draw(box);
		ui.renderWindow->display();
		
	}

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