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
    std::vector<double> earth_pos = {0,0,0};
    std::vector<double> earth_vel = {0,0,0};

    //X = 6.017559256731034E+04 Y = 3.748321054084047E+05 Z =-7.093900872437880E+03
    //VX=-1.022530440793261E+00 VY= 1.015077723821778E-01 VZ= 8.978496337716650E-02
    std::vector<double> moon_pos = {6.017559256731034e07,3.748321054084047e+08,-7.093900872437880e+06};
    std::vector<double> moon_vel = {-1.022530440793261e+3,1.015077723821778e02,8.978496337716650e01}; //FROM HORIZONS, JPL @11th September 2001, h 00:00
    double M = 5.97e24; //earth mass
    double m = 7.349e22; //moon mass

    //now we can simulate, output the positions to a CSV file and graph it with ROOT
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> vel1;
    std::vector<std::vector<double>> pos2;
    std::vector<std::vector<double>> vel2;

    CelestialBody* earth = new CelestialBody("terra",M,earth_pos,earth_vel);
    CelestialBody* moon = new CelestialBody("luna",m,moon_pos,moon_vel);

    changeToCOM(*earth,*moon);
    earth->printInfo();
    moon->printInfo();
    CelestialBody* equivalent = new CelestialBody("default",0,{0.,0.,0.},{0.,0.,0.});
    *equivalent = toEquivalentBody(*earth,*moon);
    equivalent->printInfo();
    double totalt = 2.606e6; //seconds = 28 days
    double dt = 10; //2e5 iterations
    int steps = totalt/dt;
    std::vector<double> acceleration;
    std::ofstream out_file("./csv/earth_moon.csv");
    out_file<<"x1,y1,z1,x2,y2,z2"<<std::endl;
    for (int i = 0; i < steps; i++) {
        //earth->printInfo();
        //moon->printInfo();
        pos1.push_back(earth->getPos());
        pos2.push_back(moon->getPos());
        acceleration = gravityAcceleration(*equivalent,M,m);
        equivalent->updateVel(acceleration,dt);
        equivalent->updatePos(dt);
        fromEquivalentBody(*equivalent,*earth,*moon);
        out_file<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();

    return 0;
}
