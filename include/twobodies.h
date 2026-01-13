#ifndef twobodies_h
#define twobodies_h
#include <iostream>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "planets.h"

void changeToCOM(CelestialBody& p1, CelestialBody& p2); //COM = Center Of Mass!

CelestialBody toEquivalentBody(CelestialBody p1, CelestialBody p2);

std::vector<double> gravityAcceleration(CelestialBody p, double m1, double m2);

void fromEquivalentBody(CelestialBody equivalent, CelestialBody& p1, CelestialBody& p2);

#endif
