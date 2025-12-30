#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include"solarsystem.h"
#include"twobodies.h"

int main (int argc, char *argv[]) {
    std::vector<double> sun_pos = {3,2,1};
    std::vector<double> sun_vel = {0.,0.,0.};
    
    std::vector<double> earth_pos = {3,4,5};
    std::vector<double> earth_vel = {0.,0.,0.};
    CelestialBody* sun = new CelestialBody("sol",1.989e3,sun_pos,sun_vel);
    CelestialBody* earth = new CelestialBody("terra",1.989e3,earth_pos,earth_vel);
    sun->printInfo();
    earth->printInfo();
    changeToCOM(*earth,*sun);
    CelestialBody* equivalent = new CelestialBody("dummy_name",666,sun_vel,sun_pos);
    sun->printInfo();
    earth->printInfo();
    *equivalent = equivalentBody(*sun,*earth);
    equivalent->printInfo();
    return 0;
    
}
