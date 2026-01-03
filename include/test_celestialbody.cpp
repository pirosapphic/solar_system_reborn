#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include"solarsystem.h"
#include"twobodies.h"
#include "planets.h"

int main (int argc, char *argv[]) {

    Planets setOfPlanets;

    // Test for presets
    double preset_mass = 1;
    std::vector<double> preset_pos = {0.,0.,0.};
    std::vector<double> preset_vel = {0.,0.,0.};

    CelestialBody* presetBody1 = new CelestialBody("preset_body1", preset_mass, preset_pos, preset_vel);
    CelestialBody* presetBody2 = new CelestialBody("preset_body2", preset_mass, preset_pos, preset_vel);

    setInitialConditions(setOfPlanets, *presetBody1, *presetBody2);
    
    changeToCOM(*presetBody1, *presetBody2);

    presetBody1->printInfo();
    presetBody2->printInfo();
    
    double m1 = presetBody1->getMass();
    double m2 = presetBody2->getMass();
    
    presetBody2->setVy(1e6);
    
    int n = 10;
    int dt = 1000;
    
    for(int i = 0; i < n; i++){
    
    	presetBody1->updateVel(gravityAcceleration(*presetBody1, m1, m2), dt);
    	presetBody2->updateVel(gravityAcceleration(*presetBody2, m1, m2), dt);
    	presetBody1->updatePos(dt);
    	presetBody2->updatePos(dt);
    	
    	std::cout << "[Earth]:" << std::endl;
    	std::cout << "[A_x]: " << gravityAcceleration(*presetBody2, m1, m2)[0] << std::endl;
    	std::cout << "[A_y]: " << gravityAcceleration(*presetBody2, m1, m2)[1] << std::endl;
    	std::cout << "[A_z]: " << gravityAcceleration(*presetBody2, m1, m2)[2] << std::endl;
    	std::cout << "[V_x]: " << presetBody1->getVx() << std::endl;
    	std::cout << "[V_y]: " << presetBody1->getVy() << std::endl;
    	std::cout << "[V_z]: " << presetBody1->getVz() << std::endl;
    	std::cout << "[X]: " << presetBody1->getX() << std::endl;
    	std::cout << "[Y]: " << presetBody1->getY() << std::endl;
    	std::cout << "[Z]: " << presetBody1->getZ() << std::endl;
    	std::cout << "[Moon]:" << std::endl;
    	std::cout << "[A_x]: " << gravityAcceleration(*presetBody2, m1, m2)[0] << std::endl;
    	std::cout << "[A_y]: " << gravityAcceleration(*presetBody2, m1, m2)[1] << std::endl;
    	std::cout << "[A_z]: " << gravityAcceleration(*presetBody2, m1, m2)[2] << std::endl;
    	std::cout << "[V_x]: " << presetBody2->getVx() << std::endl;
    	std::cout << "[V_y]: " << presetBody2->getVy() << std::endl;
    	std::cout << "[V_z]: " << presetBody2->getVz() << std::endl;
    	std::cout << "[X]: " << presetBody2->getX() << std::endl;
    	std::cout << "[Y]: " << presetBody2->getY() << std::endl;
    	std::cout << "[Z]: " << presetBody2->getZ() << std::endl;
    	
    
    }
    
    
    return 0;
    
}
