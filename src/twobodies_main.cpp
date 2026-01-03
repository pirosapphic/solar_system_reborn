#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "../include/solarsystem.h"
#include "../include/twobodies.h"
#include "../include/planets.h"

int main () {
    //declaring useful variables
    //note that the vector is in the stack, but the contents
    //are dynamically allocated in the heap.
    
    //vectors that store the state of the two bodies
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> vel1;
    std::vector<std::vector<double>> pos2;
    std::vector<std::vector<double>> vel2;
    //pos1[i] is the vector containing the position of p1 at time t = i*dt.
    //Examples:
    //  If pos1_0 is the vector of the initial position, pos1_0 == pos1[0] is true.
    //  If y0 is the initial value of y, y0 == pos1[0][1] is true.
    
//FIRSTLY we implement a way to choose the initial conditions of the problem
    double preset_mass = 1;
    std::vector<double> preset_pos = {0.,0.,0.};
    std::vector<double> preset_vel = {0.,0.,0.};

    CelestialBody* presetBody1 = new CelestialBody("preset_body1", preset_mass, preset_pos, preset_vel);
    CelestialBody* presetBody2 = new CelestialBody("preset_body2", preset_mass, preset_pos, preset_vel);
    
    Planets setOfPlanets; //variable that contains presets for the planets
                          // and dwarf planets of the solar system.
    setInitialConditions(setOfPlanets, *presetBody1, *presetBody2);
    
    changeToCOM(*presetBody1, *presetBody2);

    presetBody1->printInfo();
    presetBody2->printInfo();
    
    double m1 = presetBody1->getMass();
    double m2 = presetBody2->getMass();
    double totalt;
    double dt;
    std::cout << "Set total time of the simulation [s]: ";
    std::cin >> totalt;
    std::cout << "Set the infinitesimal step dt [s]: ";
    std::cin >> dt;
    int steps = totalt/dt;
    CelestialBody* equivalentBody = new CelestialBody("preset_body", preset_mass, preset_pos, preset_vel); //dummy declaration
    *equivalentBody = toEquivalentBody(*presetBody1, *presetBody2);
    std::vector<double> acceleration;
    for(int i = 0; i<=steps; i++){
        presetBody1->printInfo();
        presetBody2->printInfo();
        pos1.push_back(presetBody1->getPos());
        pos2.push_back(presetBody2->getPos());
        vel1.push_back(presetBody1->getVel());
        vel2.push_back(presetBody2->getVel());

        acceleration = gravityAcceleration(*equivalentBody, m1, m2);
        equivalentBody->updateVel(acceleration,dt);
        equivalentBody->updatePos(dt);
        fromEquivalentBody(*equivalentBody,*presetBody1,*presetBody2);
    }
    std::ofstream out_file("twobodies.csv");
    out_file<<"x1,y1,z1,x2,y2,z2"<<std::endl;
    for(int i = 0; i<=steps;i++){
        out_file<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();
    return 0;
}
