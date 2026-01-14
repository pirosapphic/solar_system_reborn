#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include "solarsystem.h" //paths relative to this file
#include "twobodies.h"
#include "planets.h"

void customSettings(std::vector<CelestialBody*>& bodies){
    //Function used in setInitialConditions to set the custom settings
    Planets planets;
    std::vector<CelestialBody*> list_of_planets = planets.list_of_planets;
    std::cout<<"\n\nCustom settings\n";
    std::cout<<"Number of bodies for the simulation n = ";
    unsigned int n = 999;
    std::cin>>n;
    for(int i = 0; i < n; i++){
	std::cout<<"Body "<<i+1<<std::endl;
	std::cout<<"  - 0) Sun\n  - 1) Mercury\n  - 2) Venus\n  - 3) Earth\n  - 4) Moon\n  - 5) Mars\n  - 6) Jupiter\n  - 7) Saturn\n  - 8) Uranus\n  - 9) Neptune\n  - 10) Custom body\n";
	unsigned int planet;
	std::cout<<"Please choose one of the bodies listed above: ";
	std::cin>>planet;
	if (planet<10){
	    CelestialBody* dummy_planet = new CelestialBody(*list_of_planets[planet]);
	    bodies.push_back(dummy_planet);
	    std::cout<<"Do you want to use the default state of "<<bodies[i]->getName()<<"? [y/n]: ";
	    char choice = 'f';
	    std::cin>>choice;
	    if(choice == 'n'){
		std::cout<<"Initial state of body "<<i+1<<std::endl;
		double x,y,z,vx,vy,vz;
		std::cout<<"x [m] = ";
		std::cin>>x;
		std::cout<<"y [m] = ";
		std::cin>>y;
		std::cout<<"z [m] = ";
		std::cin>>z;
		
		std::cout<<"vx [m/s] = ";
		std::cin>>vx;
		std::cout<<"vy [m/s] = ";
		std::cin>>vy;
		std::cout<<"vz [m/s] = ";
		std::cin>>vz;
		bodies[i]->setPos({x,y,z});
		bodies[i]->setVel({vx,vy,vz});
	    }
	}
	else if (planet == 10){
	    std::cout<<"Name of the body: ";
	    std::string custom_name = "default";
	    double custom_mass, x,y,z, vx,vy,vz;
	    std::cin>> custom_name;
	    std::cout<<"Mass of the body [kg] = ";
	    std::cin>>custom_mass;
	    std::cout<<"Initial state of body '"<<custom_name<<"";
	    std::cout<<"x [m] = ";
	    std::cin>>x;
	    std::cout<<"y [m] = ";
	    std::cin>>y;
	    std::cout<<"z [m] = ";
	    std::cin>>z;

	    std::cout<<"vx [m/s] = ";
	    std::cin>>vx;
	    std::cout<<"vy [m/s] = ";
	    std::cin>>vy;
	    std::cout<<"vz [m/s] = ";
	    std::cin>>vz;
	    CelestialBody* custom_body = new CelestialBody(custom_name,custom_mass,{x,y,z},{vx,vy,vz});
	    bodies.push_back(custom_body);
	}
	std::cout<<"-----------------------\n";
    }
}

void setInitialConditions(std::vector<CelestialBody*>& bodies){
    //This is the greeter and the function that sets the conditions for the simulations	
    Planets planets;
    std::vector<CelestialBody*> list_of_planets = planets.list_of_planets;
    unsigned int input = 0;
    while(true){
	std::cout << "Welcome to the n-body simulator!\nYou can choose a preset or setup a custom simulation.\n\n";
	std::cout << "  - 1) Earth - Moon\n";
	std::cout << "  - 2) Sun - Earth\n";
	std::cout << "  - 3) Sun - Earth - Moon\n";
	std::cout << "  - 4) Solar System (full)\n";
	std::cout << "  - 5) Custom\n\n";
	std::cout << "Choose one of the options above: ";
	std::cin>>input;
	if(input <= 5 and input > 0) break;
	std::cout<<"Invalid option, try again\n";
    }
    if (input == 1){
	bodies.push_back(planets.earth);
	bodies.push_back(planets.moon);
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 2.7e6s (i.e. 28 days)\nTime step: 10s\n\n";
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
	bodies = list_of_planets; //in order of distance from the sun,
    }				 	  //but with the moon between earth and mars: see planets.h
    else if (input == 5){
	customSettings(bodies);
    }

}


void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt, std::string output_file){
    //this is the two body simulator, implemented separately from the n-body for efficiency
    //it is called in nBodiesSimulation for n==2
    //output_file should be in the form "path/to/output.csv"
    unsigned int steps = totalt/dt;
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> pos2;
    //the first index is the time step, so that pos1[i] is the position vector of p1 @ t=i*dt
    
    changeToCOM(p1,p2);
    CelestialBody* equivalent = new CelestialBody();
    *equivalent = toEquivalentBody(p1,p2);
    std::vector<double> acceleration;
    std::ofstream out_file(output_file); //to export data
    out_file<<"#x1,y1,z1,x2,y2,z2"<<std::endl; //header of the csv file
    for (int i = 0; i< steps; i++){
	pos1.push_back(p1.getPos());
	pos2.push_back(p2.getPos());
	acceleration = gravityAcceleration(*equivalent,p1.getMass(),p2.getMass());
	equivalent->updateVel(acceleration,dt);
	equivalent->updatePos(dt);
	fromEquivalentBody(*equivalent,p1,p2);
	out_file<<std::setprecision(15)<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();
    std::cout<<"Successfully simulated the motion of the bodies "<<p1.getName()<<" and "<<p2.getName()<<std::endl;
    std::cout<<"The simulated data is stored by columns (x,y,z) in csv/output.csv\nNumber of iterations: "<<steps<<std::endl;
}

void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt, std::string output_file){
    //n body simulator
    //output_file should be in the form "path/to/output.csv"
    
    //"Lasciate ogni speranza, voi ch'entrate"
    if(bodies.size() == 2) twoBodiesSimulation(*bodies[0], *bodies[1], totalt, dt, output_file);
}
