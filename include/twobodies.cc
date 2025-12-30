#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "solarsystem.h"
#include "twobodies.h"

void changeToCOM(CelestialBody& P1, CelestialBody& P2){
    //this functions changes the frame of reference of the problem to that
    //of its center of mass
    std::vector<double> pos_COM;
    double m1 = P1.getMass();
    double m2 = P2.getMass();
    std::vector<double> pos1 = P1.getPos();
    std::vector<double> pos2 = P2.getPos();
    std::vector<double> new_pos1;
    std::vector<double> new_pos2;

    for(int i=0;i<pos1.size();i++){
        pos_COM.push_back((m1 * pos1[i] + m2 * pos2[i])/(m1 + m2));
        new_pos1.push_back(pos1[i] - pos_COM[i]);
        new_pos2.push_back(pos2[i] - pos_COM[i]);
    }
    P1.setPos(new_pos1);
    P2.setPos(new_pos2);
}


CelestialBody equivalentBody(CelestialBody P1, CelestialBody P2){
    //we create the virtual object with reduced mass \mu and position r = r1-r2
    //that is affected by the potential V = -G*m1*m2/r
    std::vector<double> dummy_pos = {0,0,0};
    std::vector<double> dummy_vel = {0,0,0};
    double reduced_mass;
    double m1 = P1.getMass();
    double m2 = P2.getMass();
    std::vector<double> pos1 = P1.getPos();
    std::vector<double> pos2 = P2.getPos();
    std::vector<double> vel1 = P1.getVel();
    std::vector<double> vel2 = P2.getVel();
    for(int i=0;i<P1.getPos().size();i++){
        dummy_pos[i] = pos1[i] - pos2[i];
        dummy_vel[i] = vel1[i] - vel2[i];
    }
    reduced_mass = (m1*m2)/(m1+m2);
    CelestialBody dummy("equivalentbody", reduced_mass, dummy_pos, dummy_vel);
    return dummy;
}

std::vector<double> gravityAcceleration(CelestialBody P,double m1, double m2){
    //used to compute the acceleration on the equivalent body
    //m1 and m2 are the masses of the two separate bodies
    const double G = 6.67259e-11; //SI UNITS!!!
    std::vector<double> acceleration;
    double distance = 0;
    
    for(int i=0;i<P.getPos().size();i++){
        distance += std::pow(P.getPos()[i],2);
    }

    distance = std::sqrt(distance);

    for(int i=0;i<P.getPos().size();i++){
      acceleration[i] = G * (m1 + m2) * P.getPos()[i] / std::pow(distance,3);
    }
    
    return acceleration;
}
