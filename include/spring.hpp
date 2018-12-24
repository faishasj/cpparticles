// Header for the Spring class.
#ifndef spring_hpp
#define spring_hpp
#define _USE_MATH_DEFINES

#include <math.h>
#include "particle.hpp"


// Handles the movement and forces acting upon the spring.
class Spring {
public:
	Spring(Particle *p1, Particle *p2, float length=50, float strength=0.5);
	Particle *getP1() { return p1; }
	Particle *getP2() { return p2; }
	void update();
	
protected:
	float length;
	float strength;
	Particle *p1;
	Particle *p2;
};

#endif // spring_hpp
