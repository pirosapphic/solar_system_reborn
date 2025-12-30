#ifndef twobodies_h
#define twobodies_h
#include <iostream>
#include <string>
#include <vector>
#include "solarsystem.h"

void changeToCOM(CelestialBody& P1, CelestialBody& P2); //COM = Center Of Mass!

CelestialBody equivalentBody(CelestialBody P1, CelestialBody P2);
//unsure if to implement it to return a CelestialBody* instead.

std::vector<double> gravityAcceleration(CelestialBody P, double m1, double m2);

#endif
