#ifndef simulation_h
#define simulation_h

#include <iostream>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "twobodies.h"

void setInitialConditions(std::vector<CelestialBody*>& bodies);

void customSettings(std::vector<CelestialBody*>& bodies);

void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt, std::string output_file);

void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt,std::string output_file);

#endif
