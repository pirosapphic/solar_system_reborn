#include<iostream>
#include<string>
#include<vector>
#include"solarsystem.h"

int main (int argc, char *argv[]) {
    std::vector<double> pos0 = {0,0,0};
    std::vector<double> vel0 = {1,1,1};
    std::vector<double> acc = {1,0,1};
    double dt=0.1;
    CelestialBody* t = new CelestialBody("terra",1e5,pos0,vel0);
    t->printState();
    std::cout << "UPDATING POSITION\n";
    t->updatePos(dt);
    t->printState();
    std::cout << "UPDATING VELOCITY\n";
    t->updateVel(acc,dt);
    t->printState();
    return 0;
}
