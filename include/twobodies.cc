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
    //used to compute the acceleration on the equivalent body p
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
    //this function converts the coordinates of the equivalent body back to those of the
    //2 initial bodies.
    //
    //NOTES: - the order of p1 p2 must be the same used in toEquivalentBody!
    //       - this function assumes that the postion and velocity vectors are
    //         expressed in the frame of reference of the center of mass
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
