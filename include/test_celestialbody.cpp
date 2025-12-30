#include<iostream>
#include<string>
#include<vector>
#include"solarsystem.h"

int main (int argc, char *argv[]) {

    const float G = 6.67259e-11f;

    std::vector<double> pos0 = {0,0,0};
    std::vector<double> vel0 = {0,0,0};
    std::vector<double> pos1 = {1.5e11,0,0};
    std::vector<double> vel1 = {30e3,0,0};
    double dt=100;
    CelestialBody* Sole = new CelestialBody("Sole",2e30,pos0,vel0);
    CelestialBody* Terra = new CelestialBody("terra",6.5e21,pos1,vel1);
    
    Bodies[0].GravitationalForce(G);
    
    for(int i = 0; i < Bodies.size(); i++){
    	CelestialBody& Current_Body = Bodies[i];
    	
    	Current_Body.updatePos(dt);
    }
    return 0;
    
}
