#include <iostream>
#include <cmath>
#include <vector>
#include <string>

int Simulation(Planets& planets, ) {

/*
    std::cout << "how much space does the earth go through before completing a full orbit?" << std::endl;
    std::cout << "none lmao! dumbass." << std::endl;

    std::cout << "geocentrism rocks!\n";

    return 0;
*/

    //double earth_mass = 5.97e24;
    //double moon_mass = 7.34e22;
    //double sun_mass = 1.99e30;
    // Yes this is dumb, it's been 4 hours... 
    //Planets passed_planets = planets;
    // --------------------------------------------------------------------------------------//
    //std::vector<double> origin_pos{0., 0., 0.};
    //std::vector<double> earth_pos{1.49e11, 0., 0.};
    //std::vector<double> moon_pos{3.84e8, 0., 0.};
    //std::vector<double> moon_vel{0,1.022e6,0};
    
    // Check input with switch statement
    std::cout << "Welcome, which one of the preset simulations would you like to use:\n\n";
    std::cout << "  - 1) Two-body: [Earth - Moon]\n";
    std::cout << "  - 2) Two-body: [Sun - Earth]\n";
    std::cout << "  - 3) Three body [Sun - Earth - Moon]\n";
    std::cout << "  - 4) Solar System ( full )\n";
    std::cout << "  - 5) Custom\n\n";
    std::cout << "Please provide an integer to choose the preferred preset: ";

    int input = 0;
    std::cin >> input;

    int customBody1 = 0;
    int customBody2 = 0;
    std::vector<Selected_Planets> simulated_planets = {};
    int n = 0;
    int s = 0;

        if (input == 1){
        
            p1.setName(planets.earth->getName()); 
            p2.setName(planets.moon->getName());
            p1.setMass(planets.earth->getMass());
            p2.setMass(planets.moon->getMass());
            p1.setPos(planets.earth->getPos());
            p2.setPos(planets.moon->getPos());
            p1.setVel(planets.earth->getVel());
            p2.setVel(planets.moon->getVel());
            
            }
        else if (input == 2){
            
            p1.setName(planets.earth->getName()); 
            p2.setName(planets.sun->getName());
            p1.setMass(planets.earth->getMass());
            p2.setMass(planets.sun->getMass());
            p1.setPos(planets.earth->getPos());
            p2.setPos(planets.sun->getPos());
            p1.setVel(planets.earth->getVel());
            p2.setVel(planets.sun->getVel());
            
            }
        else if (input == 3){
        
            std::cout << "need to implement";
            
            }
        else if (input == 4){
        
            std::cout << "need to implement";
            
            }
        else if (input == 5){
        
            std::cout << "How many objects would you like to simulate:" << std::endl;
            std::cin >> n;
            
            if(n <= 2){
            
            	setInitialConditions(Planets& planets, CelestialBody& p1, CelestialBody& p2)
            
            }
            
            
            for(int i = 0; i < n; i++){
        
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
		  std::cin >> s;

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

}

