#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <string>
#include <string.h>
#include <tuple>

const double pi = 3.14159265359;

std::string str(double a){
	return std::to_string(a);
}

double random(unsigned int seed, double M, double N) {
	if (seed != 0) srand(seed);
	return M + (rand() / (RAND_MAX / (N - M)));
}

std::string Idontknow1(std::string c, int a, int b){
	std::string ret = "";
	if (b > c.size()){
		b = c.size();
	}
	for (unsigned int x = a; x < b; x++){
		ret += c[x];
	}
	return ret;
}

int main(){
	random(69,-100,100);
	//Define the Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 500), "The Pixels Earth",sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(30);

	//Define the Variables
	int MOUSEX = 0;
	int MOUSEY = 0;
	bool RIGHTCLICK = false;
	bool LEFTCLICK = false;
	auto menu = "";
	auto changemenu = "game";
	double Transition = 0;
	int MOUSEWHEEL = 0;
	std::vector<double> var;

	sf::Texture yellow_flower;
	if (!yellow_flower.loadFromFile("./Assets/World/yellow_flower.png")) std::cout << "Error while load image from file\n";
	sf::Texture blue_flower;
	if (!blue_flower.loadFromFile("./Assets/World/blue_flower.png")) std::cout << "Error while load image from file\n";
	sf::Texture red_flower;
	if (!red_flower.loadFromFile("./Assets/World/red_flower.png")) std::cout << "Error while load image from file\n";
	sf::Texture grass1;
	if (!grass1.loadFromFile("./Assets/World/grass1.png")) std::cout << "Error while load image from file\n";
	sf::Texture grass2;
	if (!grass2.loadFromFile("./Assets/World/grass2.png")) std::cout << "Error while load image from file\n";
	sf::Texture tree;
	if (!tree.loadFromFile("./Assets/World/tree.png")) std::cout << "Error while load image from file\n";

	sf::Font font;
	if (!font.loadFromFile("F1.ttf"));
	//While window is open
	while (window.isOpen()){
		//If menu change
		if (changemenu != menu){
			Transition += (1-Transition)/10;
			if (Transition > 0.9) {
				if (changemenu == "intro") var = std::vector<double>{0};
				if (changemenu == "menu") var = std::vector<double>{0};
				if (changemenu == "game") var = std::vector<double>{10,0,0,999999,999999,0,0};
				menu = changemenu;
			}
			RIGHTCLICK = false;
			LEFTCLICK = false;
		} else Transition += (0-Transition)/10;

		//Window events
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == 0) RIGHTCLICK = true;
				else LEFTCLICK = true;
				std::cout << "Pressed " << event.mouseButton.button <<'\n';
			}
			if(event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == 0) RIGHTCLICK = false;
				else LEFTCLICK = false;
				std::cout << "Release " << event.mouseButton.button <<'\n';
			};
			if(event.type == sf::Event::Closed) window.close();
			if(event.type == sf::Event::MouseWheelMoved){
				MOUSEWHEEL = event.mouseWheel.delta;
				if (menu == "game") var[0] += (event.mouseWheel.delta);
				std::cout << event.mouseWheel.delta << '\n';
			}
			if(event.type == sf::Event::MouseMoved){
				auto a = sf::Mouse::getPosition(window);
				MOUSEX = a.x;
				MOUSEY = a.y;
			}
		}

		//The game
		if (menu == "game"){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
				window.close();
			} if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					var[5] += (0.6-var[5])/10;
				} else var[5] += (0.3-var[5])/10;
			} if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					var[5] += (-0.6-var[5])/10;
				} else var[5] += (-0.3-var[5])/10;
			} if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					var[6] += (0.6-var[6])/10;
				} else var[6] += (0.3-var[6])/10;
			} if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					var[6] += (-0.6-var[6])/10;
				} else var[6] += (-0.3-var[6])/10;
			} if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				var[2] += 0.2;
			}

			var[4] += var[6];
			var[3] += var[5];
			var[5] += (0-var[5])/10;
			var[6] += (0-var[6])/10;
			window.clear(sf::Color(40*(1-Transition),40*(1-Transition),40*(1-Transition)));
			double CamZoom = var[0]/10;
			double CamX = -var[3]*10;
			double CamY = -var[4]*10;
			float XGrass = (CamY*10-round(CamY*10/100+0.5)*100)*1/CamZoom;
			float YGrass = (CamX*10-round(CamX*10/100+0.5)*100)*1/CamZoom;
			std::cout << "Z: " << CamZoom << '\n';
			sf::RectangleShape rect;
			double seed = 108;
			
			rect.setSize(sf::Vector2f(100*(1/CamZoom),100*(1/CamZoom)));
			for (unsigned int x = 0 ; x < round(10*CamZoom) ; x++){
				for (unsigned int y = 0 ; y < round(7*CamZoom) ; y++){
					rect.setPosition((100*(1/CamZoom))*x-XGrass-200*(1/CamZoom),(100*(1/CamZoom))*y-YGrass-200*(1/CamZoom));
					rect.setFillColor(sf::Color(30,210,10));
					window.draw(rect);
				}
			}

			for (unsigned int x = 0 ; x < round(10*CamZoom) ; x++){
				for (unsigned int y = 0 ; y < round(7*CamZoom) ; y++){
					random(((x+round(CamY*10/100+0.5))*(y+round(CamX*10/100+0.5)))+seed,0,0);
					int forint;
					forint = random(0,1,1);
					for (unsigned int forx = 0; forx < forint; forx++){
						sf::Sprite sprite;
						sprite.setScale(2.5f*1/CamZoom,2.5f*1/CamZoom);
						sprite.setPosition((100*(1/CamZoom))*x-XGrass-200*(1/CamZoom)+random(0,0,50),(100*(1/CamZoom))*y-YGrass-200*(1/CamZoom)+random(0,0,50));
						sprite.setTexture(yellow_flower);
						if (random(0,0,1)<0.1) window.draw(sprite);
					}
					forint = random(0,1,1);
					for (unsigned int forx = 0; forx < forint; forx++){
						sf::Sprite sprite;
						sprite.setScale(2.5f*1/CamZoom,2.5f*1/CamZoom);
						sprite.setPosition((100*(1/CamZoom))*x-XGrass-200*(1/CamZoom)+random(0,0,50),(100*(1/CamZoom))*y-YGrass-200*(1/CamZoom)+random(0,0,50));
						sprite.setTexture(red_flower);
						if (random(0,0,1)<0.1) window.draw(sprite);
					}
					forint = random(0,1,1);
					for (unsigned int forx = 0; forx < forint; forx++){
						sf::Sprite sprite;
						sprite.setScale(2.5f*1/CamZoom,2.5f*1/CamZoom);
						sprite.setPosition((100*(1/CamZoom))*x-XGrass-200*(1/CamZoom)+random(0,0,50),(100*(1/CamZoom))*y-YGrass-200*(1/CamZoom)+random(0,0,50));
						sprite.setTexture(blue_flower);
						if (random(0,0,1)<0.1) window.draw(sprite);
					}
					forint = random(0,1,4);
					for (unsigned int forx = 0; forx < forint; forx++){
						sf::Sprite sprite;
						sprite.setScale(2.5f*1/CamZoom,2.5f*1/CamZoom);
						sprite.setPosition((100*(1/CamZoom))*x-XGrass-200*(1/CamZoom)+random(0,0,50),(100*(1/CamZoom))*y-YGrass-200*(1/CamZoom)+random(0,0,50));
						if (random(0,0,1)<0.5) sprite.setTexture(grass1);
						else sprite.setTexture(grass2);
						if (random(0,0,1)<0.5) window.draw(sprite);
					}
				}
			}
			for (unsigned int x = 0 ; x < round(10*CamZoom) ; x++){
				for (unsigned int y = 0 ; y < round(7*CamZoom) ; y++){
					random(((x+round(CamY*10/100+0.5))*(y+round(CamX*10/100+0.5)))+seed,0,0);
					int forint;
					forint = random(0,1,2);
					for (unsigned int forx = 0; forx < forint; forx++){
						sf::Sprite sprite;
						sprite.setScale(2.5f*1/CamZoom,2.5f*1/CamZoom);
						sprite.setPosition((100*(1/CamZoom))*x-XGrass-200*(1/CamZoom)+random(0,0,50),(100*(1/CamZoom))*y-YGrass-200*(1/CamZoom)+random(0,0,50));
						if ((random(0,0,1)+random(0,0,1))/2<random(0,0,0.5)) sprite.setTexture(tree);
						window.draw(sprite);
					}
				}
			}
		}
		window.display();
	}
}