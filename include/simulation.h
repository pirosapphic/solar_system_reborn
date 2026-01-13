#ifndef simulation_h
#define simulation_h

#include <iostream>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "twobodies.h"

void setInitialConditions(Planets planets, std::vector<CelestialBody*>& bodies);

void customSettings(Planets planets, std::vector<CelestialBody*>& bodies);

void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt);

void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt);

#endif
