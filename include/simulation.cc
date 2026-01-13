#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "solarsystem.h" //paths relative to this file
#include "twobodies.h"
#include "planets.h"

void setInitialConditions(Planets planets, std::vector<CelestialBody*>& bodies){
    //This is the greeter and the function that sets the conditions for the simulations	
    unsigned int input = 0;
    while(true){
	std::cout << "Welcome, which one of the preset simulations would you like to use:\n\n";
	std::cout << "  - 1) Earth - Moon\n";
	std::cout << "  - 2) Sun - Earth\n";
	std::cout << "  - 3) Sun - Earth - Moon\n";
	std::cout << "  - 4) Solar System (full)\n";
	std::cout << "  - 5) Custom\n\n";
	std::cout << "Please provide an integer to choose the preferred preset: ";
	std::cin>>input;
	if(input <= 5 and input > 0) break;
	std::cout<<"Please choose one of the options listed above\n";
    }
    if (input == 1){
	bodies.push_back(planets.earth);
	bodies.push_back(planets.moon);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 2.7e6s (i.e. 28 days)\n Time step: 10s\n\n";
    }
    else if (input == 2){
	bodies.push_back(planets.sun);
	bodies.push_back(planets.earth);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 3.16e7s (i.e. 1 earth-year)\n Time step: 100s\n\n";
    }
    else if (input == 3){
	bodies.push_back(planets.sun);
	bodies.push_back(planets.earth);
	bodies.push_back(planets.moon);
    }
    else if (input == 4){
	bodies = planets.list_of_planets; //in order of distance from the sun,
    }				 	  //but with the moon between earth and mars
    else if (input == 5){
	std::cout<<"If you can read this, we still need to implement custom settings...\n";
    }

}



void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt){
    //this is the two body simulator, implemented separately from the n-body for efficiency
    //it is called in nBodiesSimulation for n==2
    
    unsigned int steps = totalt/dt;
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> pos2;
    //the first index is the time step, so that pos1[i] is the position vector of p1 @ t=i*dt

    changeToCOM(p1,p2);
    CelestialBody* equivalent = new CelestialBody("default",0,{0,0,0},{0,0,0});
    *equivalent = toEquivalentBody(p1,p2);
    std::vector<double> acceleration;
    std::ofstream out_file("./csv/output.csv"); //to export data
    out_file<<"#x1,y1,z1,x2,y2,z2"<<std::endl; //header of the csv file
    for (int i = 0; i< steps; i++){
	pos1.push_back(p1.getPos());
	pos2.push_back(p2.getPos());
	acceleration = gravityAcceleration(*equivalent,p1.getMass(),p2.getMass());
	equivalent->updateVel(acceleration,dt);
	equivalent->updatePos(dt);
	fromEquivalentBody(*equivalent,p1,p2);
	out_file<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();
    std::cout<<"Successfully simulated the motion of the bodies "<<p1.getName()<<" and "<<p2.getName()<<std::endl;
    std::cout<<"The simulated data is stored by columns (x,y,z) in csv/output.csv\nNumber of iterations: "<<steps<<std::endl;
}

void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt){
    //n body simulator
    //"Lasciate ogni speranza, voi ch'entrate"
    if(bodies.size() == 2) twoBodiesSimulation(*bodies[0], *bodies[1], totalt, dt);
}
