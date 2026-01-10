#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<fstream>
#include"../include/solarsystem.h"
#include"../include/twobodies.h"

int main (int argc, char *argv[]) {
    //my goal is to simulate a circular orbit of the moon around the earth,
    //I'll put the moon at its average distance from earth and give it a velocity
    //so that it will orbit with a uniform circular motion
    std::vector<double> sun_pos = {0,0,0};
    std::vector<double> sun_vel = {0,0,0};

    // X = 1.474823999920235E+08 Y =-3.050349262752835E+07 Z = 2.658475158233196E+02 km
    //VX= 5.560897329115527E+00 VY= 2.905881218625929E+01 VZ=-1.246893224786660E-03 km/s
    //
    std::vector<double> earth_pos = {1.474823999920235e+11, -3.050349262752835e+10, 2.658475158233196e+05};//m
    std::vector<double> earth_vel = {5.560897329115527e+3, 2.905881218625929e+04, -1.246893224786660e0}; //m/s
    //FROM HORIZONS, JPL @11th September 2001, h 00:00

    double M = 1.989e30; //sun mass
    double m = 5.97e24; //earth mass

    //now we can simulate, output the positions to a CSV file and graph it with ROOT
    //the index 1 should refer to the bigger of the two bodies, for clarity
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> vel1;
    std::vector<std::vector<double>> pos2;
    std::vector<std::vector<double>> vel2;

    CelestialBody* p1 = new CelestialBody("sol",M,sun_pos,sun_vel);
    CelestialBody* p2 = new CelestialBody("terra",m,earth_pos,earth_vel);

    changeToCOM(*p1,*p2);
    CelestialBody* equivalent = new CelestialBody("default",0,{0.,0.,0.},{0.,0.,0.});
    *equivalent = toEquivalentBody(*p1,*p2);
    double totalt = 3.1557e7; //seconds = 365 days 5h etc
    double dt = 100; //3e5 iterations
    int steps = totalt/dt;
    std::cout << steps<<std::endl;
    std::vector<double> acceleration;

    std::ofstream out_file("./csv/sun_earth.csv");
    out_file<<"x1,y1,z1,x2,y2,z2"<<std::endl;
    for (int i = 0; i < steps; i++) {
        //earth->printInfo();
        //moon->printInfo();
        pos1.push_back(p1->getPos());
        pos2.push_back(p2->getPos());
        acceleration = gravityAcceleration(*equivalent,M,m);
        equivalent->updateVel(acceleration,dt);
        equivalent->updatePos(dt);
        fromEquivalentBody(*equivalent,*p1,*p2);
        out_file<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();

    return 0;
}
