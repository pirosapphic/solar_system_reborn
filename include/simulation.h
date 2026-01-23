#ifndef simulation_h
#define simulation_h

#include <iostream>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "twobodies.h"

//In this file we declare the functions used to simulate the motion, this is the core of the project
//See simulation.cc for more detailed explanations of the functions

void setInitialConditions(std::vector<CelestialBody*>& bodies);

void customSettings(std::vector<CelestialBody*>& bodies);

void changeToCOM(std::vector<CelestialBody*>& bodies);

void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt, std::string output_file);

void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt,std::string output_file);

std::vector<std::vector<double>> equivalentBodySimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt);

#endif
