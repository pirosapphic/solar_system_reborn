#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include"solarsystem.h"
#include"twobodies.h"

int main (int argc, char *argv[]) {
    std::vector<double> sun_pos = {0,0,0};
    std::vector<double> sun_vel = {0.,0.,0.};
    
    std::vector<double> jupyter_pos = {7.78e11,0,0};
    std::vector<double> jupyter_vel = {0,0.,0.};
    
    double sun_mass = 1.99e30;
    double jupyter_mass = 1.89e27;

    CelestialBody* sun = new CelestialBody("sol",sun_mass,sun_pos,sun_vel);
    CelestialBody* jupyter = new CelestialBody("iuppiter",jupyter_mass,jupyter_pos,jupyter_vel);
    CelestialBody* equivalent = new CelestialBody("dummy_name",666,sun_pos,sun_pos);
    
    changeToCOM(*sun,*jupyter);
    sun->printInfo();
    jupyter->printInfo();
    
    *equivalent = toEquivalentBody(*sun,*jupyter);
    equivalent->printInfo();
    CelestialBody* newsun = new CelestialBody("novum_sol",sun_mass,sun_pos,sun_pos);
    CelestialBody* newjupyter = new CelestialBody("novus_iuppiter",jupyter_mass,sun_pos,sun_pos);

    fromEquivalentBody(*equivalent, *newsun, *newjupyter);
    newsun->printInfo();
    newjupyter->printInfo();
    
    return 0;
    
}
