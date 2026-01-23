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
	std::cout<<"NOTE: you should insert the bodies in reverse order of orbit radius for the visualizer to work correctly\n";
	std::cout<<"Please choose one of the bodies listed above: ";
	std::cin>>planet;
	if (planet<10){
	    CelestialBody* dummy_planet = new CelestialBody(*list_of_planets[planet]);
	    bodies.push_back(dummy_planet);
	    std::cout<<"Do you want to use the default state of "<<bodies[i]->getName()<<"? [Y/n]: ";
	    char choice = 'y';
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
	std::cout<<"Suggested simulation times are:\n";
	std::cout<<"Total time: 3.16e7s (i.e. 1 earth-year)\n Time step: 100s\n\n";
    }
    else if (input == 4){
	bodies = list_of_planets; //in order of distance from the sun,
    }				  //but with the moon between earth and mars: see planets.h
    else if (input == 5){
	customSettings(bodies);
    }
    bodies.shrink_to_fit();
}

std::vector<std::vector<double>> equivalentBodySimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt){
    //this function simulates the motion of the equivalent body with the reduced mass \mu
    //and returns a vector of vectors so that pos[i] is the position vector of the body at t=i*dt
    //unlike twoBodiesSimulation, this function does not modify the members of
    //p1 and p2, besides putting them in their COM reference frame.
    //used to verify kepler's laws
    unsigned int steps = totalt / dt;
    std::vector<std::vector<double>> pos(steps, std::vector<double>(3));
    changeToCOM(p1,p2); //probably do not need this, as I do not need to convert
			  //back to p1 and p2
    CelestialBody* equivalent = new CelestialBody;
    *equivalent = toEquivalentBody(p1,p2);
    std::vector<double> acceleration;
    for (int i = 0; i < steps; i++){
	//Progress bar
	double percentage = (double) (i+1)/steps; //dynamic casting!
	int perc_int = 100*percentage;
	int barlen = 50;
	int bar = std::ceil(percentage*barlen);
	std::cout<<"\rLoading... [";
	for(int m = 1; m <= bar; m++){
	    std::cout<<"■";
	}
	for(int m = 1; m <= barlen-bar; m++){
	    std::cout<<" ";
	}
	std::cout<<"] "<<std::setprecision(3)<<perc_int<<"%";
	//Progress bar ends
	pos[i] = equivalent->getPos();
	acceleration = gravityAcceleration(*equivalent, p1.getMass(),p2.getMass());
	equivalent->updateVel(acceleration,dt);
	equivalent->updatePos(dt);
    }
    pos.shrink_to_fit();
    return pos;
}


void twoBodiesSimulation(CelestialBody& p1, CelestialBody& p2, double totalt, double dt, std::string output_file){
    //this is the two body simulator, implemented separately from the n-body for efficiency
    //it is called in nBodiesSimulation for n==2
    //std::string output_file should be in the form "relative/path/to/output.csv"
    unsigned int steps = totalt/dt;
    std::vector<std::vector<double>> pos1(steps, std::vector<double>(3));
    std::vector<std::vector<double>> pos2(steps, std::vector<double>(3));
    //the first index is the time step, so that pos1[i] is the position vector of p1 @ t=i*dt
    
    changeToCOM(p1,p2);
    CelestialBody* equivalent = new CelestialBody();
    *equivalent = toEquivalentBody(p1,p2);
    std::vector<double> acceleration;
    std::ofstream out_file(output_file); //to export data
    out_file<<"#x1,y1,z1,x2,y2,z2"<<std::endl; //header of the csv file
    for (int i = 0; i < steps; i++){
	//Progress bar
	double percentage = (double) (i+1)/steps; //dynamic casting!
	int perc_int = 100*percentage;
	int barlen = 50;
	int bar = std::ceil(percentage*barlen);
	std::cout<<"\rLoading... [";
	for(int m = 1; m <= bar; m++){
	    std::cout<<"■";
	}
	for(int m = 1; m <= barlen-bar; m++){
	    std::cout<<" ";
	}
	std::cout<<"] "<<std::setprecision(3)<<perc_int<<"%";
	//Progress bar ends
	pos1[i] = p1.getPos();
        pos2[i] = p2.getPos();
	acceleration = gravityAcceleration(*equivalent,p1.getMass(),p2.getMass());
	equivalent->updateVel(acceleration,dt);
	equivalent->updatePos(dt);
	fromEquivalentBody(*equivalent,p1,p2);
	out_file<<std::setprecision(15)<<pos1[i][0]<<","<<pos1[i][1]<<","<<pos1[i][2]<<","<<pos2[i][0]<<","<<pos2[i][1]<<","<<pos2[i][2]<<std::endl;
    }
    out_file.close();
    std::cout<<"Successfully simulated the motion of the bodies "<<p1.getName()<<" and "<<p2.getName()<<std::endl;
    std::cout<<"Number of iterations: "<<steps<<std::endl;
    std::cout<<"The simulated data is stored by columns (x,y,z) in "<<output_file<<"; to visualize it, you can run the root macro with\nroot ./root/two_bodies_graphic.cpp\n";
}

void nBodiesSimulation(std::vector<CelestialBody*>& bodies, double totalt, double dt, std::string output_file){
    //n body simulator
    //std::string output_file should be in the form "relative/path/to/output.csv"
    double G = 6.67e-23; 
    //"Lasciate ogni speranza, voi ch'entrate"
    if (bodies.size() == 2) {
        twoBodiesSimulation(*bodies[0], *bodies[1], totalt, dt, output_file);
    } else {
        const int n_bodies = bodies.size();
        unsigned int steps = totalt / dt;
        std::ofstream out_file(output_file);
        out_file << "#n*(x1,y1,z1)" << std::endl;
// ----------------------------------------------------------------------------------
	for (int n = 0; n<steps; n++) {
	
	double percentage = (double) (n+1)/steps; //dynamic casting!
	int perc_int = 100*percentage;
	int barlen = 50;
	int bar = std::ceil(percentage*barlen);
	std::cout<<"\rLoading... [";
	for(int m = 1; m <= bar; m++){
	    std::cout<<"■";
	}
	for(int m = 1; m <= barlen-bar; m++){
	    std::cout<<" ";
	}
	std::cout<<"] "<<std::setprecision(3)<<perc_int<<"%";

        for (int i=0; i<n_bodies; i++) {
            std::vector<double> acc(3, 0);
            //double ax = 0, ay = 0, az = 0;
            bodies[i]->setVirtualAcc({0.,0.,0.});
            for (int j = 0; j<n_bodies; j++) {
                // Need to skip the current body during calculation of acc
                if (bodies[j] == bodies[i]) {
                    continue;
                }
                double distance_cubed = std::pow(bodies[j]->getPos()[0] - bodies[i]->getPos()[0], 2) + std::pow(bodies[j]->getPos()[1] - bodies[i]->getPos()[1], 2) + std::pow(bodies[j]->getPos()[2] - bodies[i]->getPos()[2], 2);
                //std::cout << std::sqrt(distance_cubed) << std::endl;
                distance_cubed = std::pow(distance_cubed, 1.5);
                
                
                acc[0] +=  G * (bodies[j]->getMass() * (bodies[j]->getPos()[0] - bodies[i]->getPos()[0]) ) / distance_cubed; 
                acc[1] +=  G * (bodies[j]->getMass() * (bodies[j]->getPos()[1] - bodies[i]->getPos()[1]) ) / distance_cubed; 
                acc[2] +=  G * (bodies[j]->getMass() * (bodies[j]->getPos()[2] - bodies[i]->getPos()[2]) ) / distance_cubed; 

            }

            // At this point we need to keep record of the calculated acceleration for body i
            // Now we store the calculated virtual acceleration into the body's private variable.
            bodies[i]->setVirtualAcc(acc);          

            //std::cout << bodies[i]->getVirtualAcc()[0] << " ";
            //std::cout << bodies[i]->getVirtualAcc()[1] << " ";
            //std::cout << bodies[i]->getVirtualAcc()[2] << std::endl;
        }
        
        // Once all calculations are made for the current dt we can start updating pos and vel for each body
        for (int i = 0; i<n_bodies; i++) {
            out_file<<std::setprecision(15)<<bodies[i]->getPos()[0]<<","<<bodies[i]->getPos()[1]<<","<<bodies[i]->getPos()[2]<<",";
            bodies[i]->updateVel(bodies[i]->getVirtualAcc(), dt);
            bodies[i]->updatePos(dt);


        }
        // last comma could be a problem, in case need to delete last line character
        out_file<<std::endl;
    
    }
// -------------------------------------------------------------------------------
        out_file.close();

        std::cout<<"\nSuccessfully simulated the motion of the bodies!";
        std::cout<<"Number of iterations: "<<steps<<std::endl;
        std::cout<<"The simulated data is stored by columns (x,y,z) in "<<output_file<<"; to visualize it, you can run the root macro with\nroot ./root/n_bodies_graphic.cpp\n";

    }  
    
}
