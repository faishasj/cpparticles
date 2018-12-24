// Demonstrates the use of springs to create a soft body.
#include <SFML/Graphics.hpp>
#include "../include/cpparticles.hpp"

int main() {
	
	// Set up the environment.
	Environment *env = new Environment(800, 600);
	Particle *selectedParticle = nullptr;
	
	// Create the main window.
	sf::RenderWindow window(sf::VideoMode(env->getWidth(), env->getHeight()), "Soft Body Simulation");
	window.setFramerateLimit(60);
	
	// Add particles for the soft body to the environment.
	int size = 10;
	int mass = 600;
	int speed = 0;
	int angle = 0;
	float elasticity = 0.1;
	
	Particle *p1 = env->addParticle(300, 300, size, mass, speed, angle, elasticity);
	Particle *p2 = env->addParticle(500, 300, size, mass, speed, angle, elasticity);
	Particle *p3 = env->addParticle(500, 500, size, mass, speed, angle, elasticity);
	Particle *p4 = env->addParticle(300, 500, size, mass, speed, angle, elasticity);
	
	// Connect particles using springs to create the soft body.
	int length = 200;
	int strength = 50;
	
	env->addSpring(p1, p2, length, strength);
	env->addSpring(p2, p3, length, strength);
	env->addSpring(p3, p4, length, strength);
	env->addSpring(p4, p1, length, strength);
	env->addSpring(p1, p3, length, strength);
	env->addSpring(p2, p4, length, strength);
	
	while (window.isOpen()) {
		
		// Process events.
		sf::Event event;
		while (window.pollEvent(event)) {
			
			// Close window: exit.
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			// Escape: exit.
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
			
			// Left mouse button: select particle.
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					float mouseX = event.mouseButton.x;
					float mouseY = event.mouseButton.y;
					selectedParticle = env->getParticle(mouseX, mouseY);
				}
			}
			
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					selectedParticle = nullptr;
				}
			}
		}
		
		// Clear the window.
		window.clear();
		
		// Update the environment.
		env->update();
		
		// Move the selected particle to the cursor's position.
		if (selectedParticle) {
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;
			selectedParticle->moveTo(mouseX, mouseY);
		}
		
		// Draw springs.
		for (int i=0; i<env->getSprings().size(); i++) {
			Spring *spring = env->getSprings()[i];
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(spring->getP1()->getX(), spring->getP1()->getY())),
				sf::Vertex(sf::Vector2f(spring->getP2()->getX(), spring->getP2()->getY()))
			};
			window.draw(line, 2, sf::Lines);
		}
		
		// Update the window.
		window.display();
	}
	
	return EXIT_SUCCESS;
}
