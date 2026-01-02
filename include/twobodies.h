#ifndef twobodies_h
#define twobodies_h
#include <iostream>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "planets.h"

void changeToCOM(CelestialBody& p1, CelestialBody& p2); //COM = Center Of Mass!

CelestialBody toEquivalentBody(CelestialBody p1, CelestialBody p2);
//unsure if to implement it to return a CelestialBody* instead.

std::vector<double> gravityAcceleration(CelestialBody p, double m1, double m2);
void fromEquivalentBody(CelestialBody equivalent, CelestialBody& p1, CelestialBody& p2);

void setInitialConditions(Planets& planets, CelestialBody& p1, CelestialBody& p2);

void setInitialBodies(Planets& planets, int body1, int body2, std::vector<CelestialBody*>& vectorOfBodies);
        
#endif
