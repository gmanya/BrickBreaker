#include <SFML/Graphics.hpp>
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>

// SFML used to create the ball

int main()
{
	const int windowWidth = 800;
	const int windowHeight = 600;
	const float ballRadius = 16.f;	

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bouncing ball");
	window.setVerticalSyncEnabled(true);


	std::random_device seed_device; 
	std::default_random_engine engine(seed_device());
	std::uniform_int_distribution<int> distribution(0, 16);				// To allow it to fall from center of the screen downwards toward the paddle
	auto random = std::bind(distribution, std::ref(engine));

	sf::Vector2f direction(random(), random());
	const float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::CircleShape ball(ballRadius - 4);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::Cyan);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(windowWidth / 2, windowHeight / 2);

	sf::Clock clock; 
	sf::Time clockElapsed = clock.restart();
	const sf::Time update_ms = sf::seconds(1.f / 30.f);
	while (window.isOpen()) {											//Game loop 
		sf::Event event;
		while (window.pollEvent(event)) {
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				window.close();
				break;
			}
		}

		clockElapsed += clock.restart();
		while (clockElapsed > update_ms) {
			const auto pos = ball.getPosition();
			const auto delta = update_ms.asSeconds() * velocity;
			sf::Vector2f new_pos(pos.x + direction.x * delta, pos.y + direction.y * delta);

			window.clear(sf::Color(0, 0, 0, 255));

			if (new_pos.x - ballRadius < 0) { // left window edge
				direction.x *= -1;
				new_pos.x = 0 + ballRadius;
			}
			else if (new_pos.x + ballRadius >= windowWidth) { // right window edge
				direction.x *= -1;
				new_pos.x = windowWidth - ballRadius;
			}
			else if (new_pos.y - ballRadius < 0) { // top of window
				direction.y *= -1;
				new_pos.y = 0 + ballRadius;
			}
			else if (new_pos.y + ballRadius >= windowHeight) { // bottom of window
				direction.y *= -1;
				new_pos.y = windowHeight - ballRadius;
			}
			ball.setPosition(new_pos);

			clockElapsed -= update_ms;
			
			window.draw(ball);
			window.display();

		}

	}

	return EXIT_SUCCESS;
}

// if position is the same as the radius , then bounce back 

/* float xVelocity = 0.1f;
	float yVelocity = 0.1f;

	bool xBounce = false;
	bool yBounce = false;

	if (xBounce) {
		xPosition -= xVelocity;
		}
	else {
		xPosition += xVelocity;
	}

	if (yBounce) {
		yPosition -= yVelocity;
	}
	else {
		yPosition += yvelocity;
	}

	if (xPosition > 640 || xPosition < 0) {
		xBounce = !xBounce;
		xVelocity *= 0.9f;
	}

	if (yPosition > 640 || yPosition < 0) {
		yBounce = !yBounce;
		yVelocity *= 0.9f;
	}


*/