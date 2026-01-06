#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "solarsystem.h"
#include "twobodies.h"


void changeToCOM(CelestialBody& p1, CelestialBody& p2){
    //this functions changes the frame of reference of the problem to that
    //of the center of mass
    std::vector<double> pos_COM;
    std::vector<double> vel_COM;
    double m1 = p1.getMass();
    double m2 = p2.getMass();
    std::vector<double> pos1 = p1.getPos();
    std::vector<double> pos2 = p2.getPos();
    std::vector<double> vel1 = p1.getVel();
    std::vector<double> vel2 = p2.getVel();

    std::vector<double> new_pos1;
    std::vector<double> new_pos2;
    std::vector<double> new_vel1;
    std::vector<double> new_vel2;

    for(int i=0;i<pos1.size();i++){
        pos_COM.push_back((m1 * pos1[i] + m2 * pos2[i])/(m1 + m2));
        new_pos1.push_back(pos1[i] - pos_COM[i]);
        new_pos2.push_back(pos2[i] - pos_COM[i]);
        
        vel_COM.push_back((m1 * vel1[i] + m2 * vel2[i])/(m1 + m2));
        new_vel1.push_back(vel1[i] - vel_COM[i]);
        new_vel2.push_back(vel2[i] - vel_COM[i]);
    }
    p1.setPos(new_pos1);
    p2.setPos(new_pos2);
    p1.setVel(new_vel1);
    p2.setVel(new_vel2);
}


CelestialBody toEquivalentBody(CelestialBody p1, CelestialBody p2){
    //we create the virtual object with reduced mass \mu and position r = r1-r2
    //that is affected by the potential V = -G*m1*m2/r
    std::vector<double> equivalent_pos = {0,0,0};
    std::vector<double> equivalent_vel = {0,0,0};
    double reduced_mass;
    double m1 = p1.getMass();
    double m2 = p2.getMass();
    std::vector<double> pos1 = p1.getPos();
    std::vector<double> pos2 = p2.getPos();
    std::vector<double> vel1 = p1.getVel();
    std::vector<double> vel2 = p2.getVel();
    for(int i=0;i<p1.getPos().size();i++){
        equivalent_pos[i] = pos1[i] - pos2[i];
        equivalent_vel[i] = vel1[i] - vel2[i];
    }
    reduced_mass = (m1*m2)/(m1+m2);
    CelestialBody equivalent("equivalentbody", reduced_mass, equivalent_pos, equivalent_vel);
    return equivalent;
}

std::vector<double> gravityAcceleration(CelestialBody p,double m1, double m2){
    //used to compute the acceleration on the equivalent body
    //m1 and m2 are the masses of the two separate bodies
    const double G = 6.67259e-11; //SI UNITS!!!
    std::vector<double> acceleration;
    double distance = 0;
    
    for(int i=0;i<p.getPos().size();i++){
        distance += std::pow(p.getPos()[i],2);
    }

    distance = std::sqrt(distance);

    for(int i=0;i<p.getPos().size();i++){
      double acc = - G * (m1 + m2) * p.getPos()[i] / std::pow(distance,3);
      acceleration.push_back(acc);
      
    }
    
    return acceleration;
}

void fromEquivalentBody(CelestialBody equivalent, CelestialBody& p1, CelestialBody& p2){
    //NOTES: the order of p1 p2 must be the same used in toEquivalentBody!
    //       this function assumes that the postion and velocity vectors are
    //       expressed in the frame of reference of the center of mass
    const int n = equivalent.getPos().size();
    double reduced_mass = equivalent.getMass();
    double m1 = p1.getMass();
    double m2 = p2.getMass();
    
    std::vector<double> pos_equivalent = equivalent.getPos();
    std::vector<double> pos1 = {0,0,0};
    std::vector<double> pos2 = {0,0,0};
    
    std::vector<double> vel_equivalent = equivalent.getVel();
    std::vector<double> vel1 = {0,0,0};
    std::vector<double> vel2 = {0,0,0};
    
    for(int i = 0; i < n; i++){
        pos1[i] = reduced_mass/m1*pos_equivalent[i];
        pos2[i] = - reduced_mass/m2*pos_equivalent[i];
        
        vel1[i] = reduced_mass/m1*vel_equivalent[i];
        vel2[i] = - reduced_mass/m2*vel_equivalent[i];
    }
    p1.setPos(pos1);
    p2.setPos(pos2);
    
    p1.setVel(vel1);
    p2.setVel(vel2);
}

void setInitialConditions(Planets& planets, CelestialBody& p1, CelestialBody& p2){
    double earth_mass = 5.97e24;
    double moon_mass = 7.34e22;
    double sun_mass = 1.99e30;
    // Yes this is dumb, it's been 4 hours... 
    Planets passed_planets = planets;
    // --------------------------------------------------------------------------------------//
    std::vector<double> origin_pos{0., 0., 0.};
    std::vector<double> earth_pos{1.49e11, 0., 0.};
    std::vector<double> moon_pos{3.84e8, 0., 0.};
    std::vector<double> moon_vel{0,1.022e6,0};
    // Check input with switch statement
    std::cout << "Hello there, welcome! Do you want to use one of the available presets?:\n\n";
    std::cout << "  - 1) Default: Two-body (Earth - Moon)\n";
    std::cout << "  - 2) Two-body (Sun - Earth)\n";
    // These may be implemented later
    std::cout << " ----------- WARNING ------------- ";
    std::cout << " the following options (3 and 4) must be implemented before the end of the project ";
    std::cout << "  - 3) Three body (Sun - Earth - Moon)\n";
    std::cout << "  - 4) Solar System ( full )\n";
    std::cout << "  - 5) Custom\n\n";
    std::cout << "Please provide an integer to choose the preferred preset: ";

    int input = 0;
    std::cin >> input;

    int customBody1 = 666;
    int customBody2 = 666;

        if (input == 1)
            {
            p1.setName("Earth"); 
            p2.setName("Moon");
            p1.setMass(earth_mass);
            p2.setMass(moon_mass);
            p1.setPos(origin_pos);
            p2.setPos(moon_pos);
            p2.setVel(moon_vel);
            }
        else if (input == 2)
            {
            p1.setName("Sun");
            p2.setName("Earth");
            p1.setMass(sun_mass);
            p2.setMass(earth_mass);
            p1.setPos(origin_pos);
            p2.setPos(earth_pos);
            }
        else if (input == 3)
        {
            std::cout << "need to implement";
            }
        else if (input == 4)
        {
            std::cout << "need to implement";
            }
        else {
            std::cout << "please type body 1 name from the following options: \n";
            std::cout << "0)  sun\n";
            std::cout << "1)  mercury\n";
            std::cout << "2)  venus\n";
            std::cout << "3)  earth\n";
            std::cout << "4)  mars\n";
            std::cout << "5)  jupiter\n";
            std::cout << "6)  saturn\n";
            std::cout << "7)  uranus\n";
            std::cout << "8)  neptune\n";
            //std::cout << "9)  pluto (?)\n"; 
            std::cout << ": ";
            std::cin >> customBody1;

            std::cout << "Ok! now please type body 2 name from the following options: \n";
            std::cout << "0)  sun\n";
            std::cout << "1)  mercury\n";
            std::cout << "2)  venus\n";
            std::cout << "3)  earth\n";
            std::cout << "4)  mars\n";
            std::cout << "5)  jupiter\n";
            std::cout << "6)  saturn\n";
            std::cout << "7)  uranus\n";
            std::cout << "8)  neptune\n";
            std::cout << "9)  pluto (?)\n"; 
            std::cout << ": ";
            std::cin >> customBody2;

            std::vector<CelestialBody*> chosenBodies;
            
            setInitialBodies(planets, customBody1, customBody2, chosenBodies);
        
            p1 = *chosenBodies[0];
            p2 = *chosenBodies[1];
            
            double distanceInput = 0;
            double bx1 = 0;
            double by1 = 0;
            double bz1 = 0;
            double bx2 = 0;
            double by2 = 0;
            double bz2 = 0;
            
            std::cout << "Perfect! now write the distance between the 2 Bodies: \n";
            std::cout << ": ";
            std::cin >> distanceInput;
            
            std::cout << "And lastly, add the velocities of the two body: \n";
            std::cout << "[Body 1 (x,0,0)]: ";
            std::cin >> bx1;
            std::cout << "[Body 1 (0,y,0)]: ";
            std::cin >> by1;
            std::cout << "[Body 1 (0,0,z)]: ";
            std::cin >> bz1;
            std::cout << "[Body 2 (x,0,0)]: ";
            std::cin >> bx2;
            std::cout << "[Body 2 (0,y,0)]: ";
            std::cin >> by2;
            std::cout << "[Body 2 (0,0,z)]: ";
            std::cin >> bz2;
            
            p1.setX(distanceInput);
            p1.setVx(bx1);
            p1.setVy(by1);
            p1.setVz(bz1);
            p2.setVx(bx2);
            p2.setVy(by2);
            p2.setVz(bz2);
            }            
}

void setInitialBodies(Planets& chosen_planets, int body1, int body2, std::vector<CelestialBody*>& vectorOfBodies) {
    if(body1>10 || body1<0) {
        std::cout << "Invalid argument for body 1!\n";
    }
    if(body2>10 || body2<0){
        std::cout << "Invalid argument for body 2!\n";
    }
    else{
        vectorOfBodies.push_back(chosen_planets.list_of_planets[body1]);
        vectorOfBodies.push_back(chosen_planets.list_of_planets[body2]);
    }
}






