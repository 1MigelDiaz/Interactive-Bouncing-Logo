#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

int main() {
	bool paused = false;
	int bouncecount = 0;
	float speedx = 5.f;
	float speedy = 3.f;
	float locx = 400.f;
	float locy = 300.f;
	float extraspeedx = 1.f;
	float extraspeedy = 1.f;
	int addrotation = 0;

	sf::RenderWindow canva(sf::VideoMode({ 800, 600 }), "Background");
	sf::RectangleShape box({ 100, 60 });
	box.setFillColor(sf::Color(50, 50, 50));
	box.setOutlineColor(sf::Color(200, 200, 200));
	box.setOutlineThickness(5);
	box.setOrigin({ 50.f, 30.f });

	sf::Font font;
	font.openFromFile("C:/Users/Siglaptop/Downloads/PixelifySans-Medium.ttf");
	sf::Text bounce(font);
	bounce.setCharacterSize(30);
	bounce.setFillColor(sf::Color(200, 200, 200));
	bounce.setPosition({ 10.f, 20.f });

	sf::RectangleShape lowerbox({ 400, 60 });
	lowerbox.setFillColor(sf::Color(125, 125, 125));
	lowerbox.setOutlineColor(sf::Color(150, 150, 150));
	lowerbox.setOutlineThickness(2);
	lowerbox.setOrigin({ 200.f, 30.f });
	lowerbox.setPosition({ 400.f, 520.f });

	sf::Text pausetext(font);
	pausetext.setCharacterSize(25);
	pausetext.setFillColor(sf::Color::White);
	pausetext.setPosition({ 240.f, 505.f });
	



	while (canva.isOpen())
	{
		while (const auto event = canva.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) { canva.close(); }
			if (const auto* key = event->getIf<sf::Event::KeyPressed>()) 
			{
				if (key->scancode == sf::Keyboard::Scancode::Space)
				{
					paused = !paused;
				}

				else if (key->scancode == sf::Keyboard::Scancode::F) 
				{
					bouncecount = 0; locx = 400.f; locy = 300.f; box.setRotation(sf::degrees(0));
					extraspeedx = 1.f; extraspeedy = 1.f; speedx = 5.f; speedy = 3.f; addrotation = 0;
				}
			}
		}

		if (locx < 55 || locx > 800 - 55)
		{
			extraspeedx += 0.1; extraspeedx = -extraspeedx; speedx = -speedx * extraspeedx; addrotation += 1; bouncecount += 1;
		}

		if (locy < 35 || locy > 600 - 35)
		{ 
			extraspeedy += 0.1; extraspeedy = -extraspeedy; speedy = -speedy * extraspeedy;   addrotation += 1; bouncecount += 1; 
		}

		if (paused == false)
		{
			locx += speedx; locy += speedy; box.rotate(sf::degrees(2 + addrotation)); std::this_thread::sleep_for(std::chrono::milliseconds(35));
		}

		bounce.setString("Bounce count: " + std::to_string(bouncecount));
		box.setPosition({ locx, locy });
		canva.clear(sf::Color::Black);
		canva.draw(box);
		canva.draw(bounce);

		if (paused == true)
		{
			bool displayed = false; pausetext.setString("Press space to continue.");
			canva.draw(lowerbox); canva.draw(pausetext);
		}
		canva.display();
	}
}