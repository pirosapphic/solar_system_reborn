#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include"solarsystem.h"
#include"twobodies.h"
#include "planets.h"

int main (int argc, char *argv[]) {

    Planets setOfPlanets;
/*
    std::vector<double> sun_pos = {0,0,0};
    std::vector<double> sun_vel = {0.,0.,0.};
    
    std::vector<double> jupiter_pos = {7.78e11,0,0};
    std::vector<double> jupiter_vel = {0,0.,0.};
    
    double sun_mass = 1.99e30;
    double jupiter_mass = 1.89e27;

    struct SolarSystemPlanets {
        CelestialBody sun("sun",1.99e30,sun_pos,sun_vel);
        CelestialBody mercury("mercury",0.33e24,sun_pos,sun_vel);
        CelestialBody venus("venus",4.86e24,sun_pos,sun_vel);
        CelestialBody earth("earth",5.97e24,sun_pos,sun_vel);
        CelestialBody mars("mars",0.64e24,sun_pos,sun_vel);
        CelestialBody jupiter("jupiter",1.898e27,jupiter_pos,jupiter_vel);
        CelestialBody saturn("saturn",568e24,sun_pos,sun_vel);
        CelestialBody uranus("uranus",86e24,sun_pos,sun_vel);
        CelestialBody neptune("neptune",102e24,sun_pos,sun_vel);
    };

    struct SolarSystemDwarfPlanets {
        CelestialBody ceres("ceres",938e18,sun_pos,sun_vel);
        CelestialBody pluto("pluto",13024e18,sun_pos,sun_vel);
        CelestialBody eris("eris",16600e18,sun_pos,sun_vel);
        CelestialBody makemake("makemake",3100e18,sun_pos,sun_vel);
        CelestialBody haumea("haumea",4006e18,sun_pos,sun_vel);
    };

    CelestialBody* sun = new CelestialBody("sol",sun_mass,sun_pos,sun_vel);
    CelestialBody* jupiter = new CelestialBody("iuppiter",jupiter_mass,jupiter_pos,jupiter_vel);
    CelestialBody* equivalent = new CelestialBody("dummy_name",666,sun_pos,sun_pos);
    
    changeToCOM(*sun,*jupiter);
    sun->printInfo();
    jupiter->printInfo();
    
    *equivalent = toEquivalentBody(*sun,*jupiter);
    equivalent->printInfo();
    CelestialBody* newsun = new CelestialBody("novum_sol",sun_mass,sun_pos,sun_pos);
    CelestialBody* newjupiter = new CelestialBody("novus_iuppiter",jupiter_mass,sun_pos,sun_pos);

    fromEquivalentBody(*equivalent, *newsun, *newjupiter);
    newsun->printInfo();
    newjupiter->printInfo();
   
*/
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
