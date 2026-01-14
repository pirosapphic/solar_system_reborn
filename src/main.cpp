#include <iostream>
#include <cmath>
#include <vector>
#include <string>
//#include "../include/solarsystem.h"
//#include "../include/planets.h"
#include "../include/simulation.h"

int main(){
    std::vector<CelestialBody*> bodies;
    setInitialConditions(bodies);
    double totalt;
    double dt;
    std::cout<<"Total time simulated [s]: ";
    std::cin>>totalt;
    std::cout<<"Time step dt [s]: ";
    std::cin>>dt;
    nBodiesSimulation(bodies, totalt, dt,"./csv/output.csv");
}
