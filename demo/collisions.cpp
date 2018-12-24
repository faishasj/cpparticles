// Demonstrates particle physics in a 'regular' environment with gravity.
#include <SFML/Graphics.hpp>
#include "../include/cpparticles.hpp"

int main() {
	
	// Set up the environment.
	Environment *env = new Environment(800, 600);
	Particle *selectedParticle = nullptr;
	
	// Create the main window.
	sf::RenderWindow window(sf::VideoMode(env->getWidth(), env->getHeight()), "Collision Simulation");
	window.setFramerateLimit(60);
	
	// Add random particles to the environment.
	for (int i = 0; i < 10; i++) {
		env->addParticle();
	}
	
	while (window.isOpen()) {
		
		// Process events.
		sf::Event event;
		while (window.pollEvent(event)) {
			
			// Close window: Exit.
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			// Escape: Exit.
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
			
			// Hold left mouse button: Select and drag a particle.
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					float mouseX = event.mouseButton.x;
					float mouseY = event.mouseButton.y;
					selectedParticle = env->getParticle(mouseX, mouseY);
				}
			}
			
			// Release left mouse button: Release a particle.
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
		
		// Draw particles.
		for (int i = 0; i < env->getParticles().size(); i++) {
			Particle *particle = env->getParticles()[i];
			sf::CircleShape circle(particle->getSize());
			circle.setOrigin(particle->getSize(), particle->getSize());
			circle.setPosition(particle->getX(), particle->getY());
			window.draw(circle);
		}
		
		// Update the window.
		window.display();
	}
	
	return EXIT_SUCCESS;
}
