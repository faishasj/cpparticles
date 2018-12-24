// Demonstrates the use of different environment settings to simulate a gas cloud.
#define _USE_MATH_DEFINES

#include <math.h>
#include <random>
#include <SFML/Graphics.hpp>
#include "../include/cpparticles.hpp"

int main() {
	
	// Set up the environment.
	Environment *env = new Environment(800, 600);
	env->setAllowAccelerate(false);
	env->setAllowAttract(true);
	env->setAllowBounce(false);
	env->setAllowCollide(false);
	env->setAllowCombine(true);
	env->setAllowDrag(false);
	
	// Create the main window.
	sf::RenderWindow window(sf::VideoMode(env->getWidth(), env->getHeight()), "Gas Cloud Simulation");
	window.setFramerateLimit(60);
	
	// Set up the 'camera' values for viewing the environment.
	float dx = 0;
	float dy = 0;
	float mx = 0;
	float my = 0;
	float magnification = 1;
	bool paused = false;
	
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> massDist(1,5);
	
	// Add randomized particles to the environment.
	for (int i = 0; i < 500; i++) {
		int mass = massDist(rd);
		float size = 0.5 * pow(mass, 0.5);
		std::uniform_int_distribution<int> xDist(size, env->getWidth() - size);
		std::uniform_int_distribution<int> yDist(size, env->getHeight() - size);
		env->addParticle(xDist(rd), yDist(rd), size, mass, 0);
	}
	
	while (window.isOpen()) {
		
		// Process events.
		sf::Event event;
		while (window.pollEvent(event)) {
			
			// Close window: exit.
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			if (event.type == sf::Event::KeyPressed) {
				// Escape: exit.
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				
				// Left arrow: move view window to the left.
				if (event.key.code == sf::Keyboard::Left) {
					dx += 0.2 * env->getWidth() / (magnification * 10);
				}
				
				// Right arrow: move view window to the right.
				if (event.key.code == sf::Keyboard::Right) {
					dx += -0.2 * env->getWidth() / (magnification * 10);
				}
				
				// Up arrow: move view window up.
				if (event.key.code == sf::Keyboard::Up) {
					dy += 0.2 * env->getHeight() / (magnification * 10);
				}
				
				// Down arrow: move view window down.
				if (event.key.code == sf::Keyboard::Down) {
					dy += -0.2 * env->getHeight() / (magnification * 10);
				}
				
				// Right bracket: zoom in.
				if (event.key.code == sf::Keyboard::RBracket) {
					magnification *= 1.2;
					mx = (1 - magnification) * env->getWidth() / 2;
					my = (1 - magnification) * env->getHeight() / 2;
				}
				
				// Left bracket: zoom out.
				if (event.key.code == sf::Keyboard::LBracket) {
					magnification *= 0.8;
					mx = (1 - magnification) * env->getWidth() / 2;
					my = (1 - magnification) * env->getHeight() / 2;
				}
				
				// "R" key: reset view window.
				if (event.key.code == sf::Keyboard::R) {
					dx = 0;
					dy = 0;
					mx = 0;
					my = 0;
					magnification = 1;
				}
				
				// Space: toggle pause.
				if (event.key.code == sf::Keyboard::Space) {
					if (paused) {
						paused = false;
					} else {
						paused = true;
					}
				}
			}
		}
		
		// Clear the window.
		window.clear();
		
		// Update the environment.
		if (not paused) {
			env->update();
		}
		
		for (int i = 0; i < env->getParticles().size(); i++) {
			Particle *particle = env->getParticles()[i];
			
			// Combine colliding particles.
			if (particle->getCollideWith()) {
				env->removeParticle(particle->getCollideWith());
				particle->setSize(0.5 * pow(particle->getMass(), 0.5));
			}
			
			// Update view window by changing the position and size of the drawn particles.
			float x = mx + (dx + particle->getX()) * magnification;
			float y = my + (dy + particle->getY()) * magnification;
			float size = particle->getSize() * magnification;
			
			// Draw particles.
			sf::CircleShape circle(size);
			circle.setOrigin(size, size);
			circle.setPosition(x, y);
			window.draw(circle);
		}
		
		// Update the window.
		window.display();
	}
	
	return EXIT_SUCCESS;
}
