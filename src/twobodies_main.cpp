#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "../include/solarsystem.h"
#include "../include/twobodies.h"

int main () {
    //declaring useful variables
    CelestialBody* p1 = new CelestialBody("default",0,0,0,0,0,0,0);
    CelestialBody* p2 = new CelestialBody("default",0,0,0,0,0,0,0);
    double total_time = 666;
    double dt = 666;
    double m1 = 666;
    double m2 = 666;
    //note that the vector is in the stack, but the contents
    //are dynamically allocated in the heap.
    
    //vectors that store the state of the two bodies
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> vel1;
    std::vector<std::vector<double>> pos2;
    std::vector<std::vector<double>> vel2;
    //pos1[i] is the vector containing the position of p1 at time t = i*dt.
    //Examples:
    //  If pos1_0 is the vector of the initial position, pos1_0 == pos1[0] is true.
    //  If y0 is the initial value of y, y0 == pos1[0][1] is true.
    
//FIRSTLY we implement a way to choose the initial conditions of the problem
    char choice;
    while(true){
        std::cout << "Welcome to the two bodies simulation!\n";
        std::cout << "Would you like to choose a preset? [y/n]: ";
        std::cin >> choice;
        if(choice == 'y' || choice=='n') break;
    }
    if(choice == 'n') setInitialConditions(*p1,*p2);
    else{
        while(true){
            int preset;
            std::cout << "List of presets:\n";
            std::cout << "  0: Earth Moon \n";
            std::cout << "  1: Sun Mercury \n";
            std::cout << "  2: Sun Venus \n";
            std::cout << "  3: Sun Earth \n";
            std::cout << "  4: Sun Mars \n";
            std::cout << "  5: Sun Jupyter \n";
            std::cout << "  6: Sun Saturn \n";
            std::cout << "  7: Sun Uranus \n";
            std::cout << "  8: Sun Neptune \n";
            //these are too many, will probably reduce them
            std::cout << "Which preset would you like to choose? ";
            std::cin >> preset;
            if(preset<=8 && preset >=0) break;
        }
    }
    return 0;
}
