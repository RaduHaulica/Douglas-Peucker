#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
	sf::View camera;
	camera.setCenter(800, 400);
	camera.setSize(1600, -800); // -800 because the y axis is inverted
	window.setView(camera);

	sf::Font font;
	font.loadFromFile("./Roboto-Bold.ttf");
	sf::Text helpText;
	helpText.setFont(font);
	helpText.setFillColor(sf::Color::White);
	helpText.setCharacterSize(12);
	helpText.setString("Click and drag to create curve\nRight click to start Douglas-Peucker algorithm\n\nHold F1 to display bezier curves\n(red curve is based on original path\nmagenta curve is based on D-P simplified path)");
	helpText.setPosition({ 20, 780 });
	helpText.setScale({ 1,-1 });

	sf::Vector2i mousePos;
	sf::Vector2f mousePosWorld;

	sf::Clock frameClock;
	float dt;

	float inputCooldown{ 0.025f };
	float inputCooldownAccumulator{ 0 };
	bool addPoint{ false };
	bool algorithmStarted{ false };
	float epsilon{ 15.0f };

	std::vector<sf::Vector2f> points;
	std::vector<sf::Vector2f> bezierPoints;
	std::vector<sf::Vector2f> finalPoints;
	std::vector<sf::Vector2f> bezierFinalPoints;
	sf::VertexArray pointsVA;
	sf::VertexArray finalVA;

	bool itsDone{ false };
	bool showBezier{ false };
	bool started = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			showBezier = true;
		}
		else
		{
			showBezier = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !inputCooldownAccumulator && !algorithmStarted)
		{
			addPoint = true;
			started = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			algorithmStarted = true;
		}

		// meat and potatoes
		mousePos = sf::Mouse::getPosition(window);
		mousePosWorld = window.mapPixelToCoords(mousePos);
		dt = frameClock.restart().asSeconds();
		inputCooldownAccumulator = std::fmax(0, inputCooldownAccumulator - dt);

		if (!itsDone)
		{
			if (addPoint or started)
			{
				inputCooldownAccumulator = inputCooldown;
				addPoint = true;
				if (points.size() > 0)
					addPoint = distanceBetweenPoints(mousePosWorld, points.back()) > 1;
				if (addPoint)
				{
					points.push_back({ mousePosWorld.x, mousePosWorld.y });
					pointsVA.append({ points.back(), sf::Color::White });
					addPoint = false;
				}
			}

			if (algorithmStarted)
			{
				std::cout << "Algorithm started for :" << points.size() << std::endl;

				finalPoints = algorithm(points, epsilon);
				std::cout << "Algorithm finished for :" << points.size() << std::endl;
				bezierPoints = computeBezier(points, 50);
				bezierFinalPoints = computeBezier(finalPoints, 50);
				itsDone = true;
			}
		}


		// draw
		window.clear();
		window.draw(createVertexArray(points, sf::Color::Blue));
		if (algorithmStarted)
		{
			window.draw(createVertexArray(finalPoints, sf::Color::Green));
		}
		if (itsDone && showBezier)
		{
			window.draw(createVertexArray(bezierPoints, sf::Color::Red));
			window.draw(createVertexArray(bezierFinalPoints, sf::Color::Magenta));
		}
		window.draw(helpText);
		window.display();
	}


	return 0;
}