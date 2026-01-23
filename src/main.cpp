#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "../include/simulation.h" //this includes all other header files

//This is the main(), you can compile it by running 'make' in the main directory
//To see more about the called functions, see simulation.cc and simulation.h
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
