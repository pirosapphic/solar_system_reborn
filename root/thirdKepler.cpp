#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <TCanvas.h>
#include <TGraph.h>
#include "../include/simulation.h"
#include "../include/simulation.cc"
#include "../include/solarsystem.h"
#include "../include/solarsystem.cc"
#include "../include/twobodies.h"
#include "../include/twobodies.cc"
#include "../include/planets.h"
#include "../include/csvconverter.h"

//We want to verify Kepler's third law, which states that
//for a closed orbit, the square of the period T is proportional to the 
//cube of the major semiaxis of the orbit a.
//T^2 = K*a^3
//With k = 4*pi^2/[G*(m+M)]
//We verify this with the earth moon orbit and with the orbits of Earth, Mars and Jupiter.
//Note that we will use the motion of the equivalent body

std::vector<double> orbitResults(std::vector<std::vector<double>> vector_r, double dt); 
//orbitResults[0] = a (semiaxis)
//orbitResults[1] = T (period)
//implemented below

void thirdKepler(){
    std::cout<<"Welcome to the simulator for the third Kepler law\n\n";
    std::cout<<"This will simulate the motion of these binary systems:\n";
    std::cout<<"  - Earth Moon\n";
    std::cout<<"  - Sun Earth\n";
    std::cout<<"  - Sun Venus\n";
    std::cout<<"  - Sun Jupiter\n\n";
    std::cout<<"It will then calculate the period T, the major semiaxis a and the constant k = T^2/a^3.\n";
    std::cout<<"The simulated values of k will then be compared to the theoretical value\nk_calc=4pi^2/[G*(M+m)]\n(where m, M are the masses of the bodies and G is the gravitational constant), predicted by Newton's law of gravitation.\nThis will highlight not only that the constant depends on the bigger body in the system, but also that more massive planets have smaller values of k.\n\n";
    char choice = 'H';
    std::cout<<"Press y to start the macro: ";
    std::cin>>choice;
    if(choice != 'y') return;
    Planets planets;
    const double G = 6.67259e-11;
    const double PI = 3.141592653589793; //written by ale
    //------------------------------------------------------
    //EARTH MOON SYSTEM
    CelestialBody* earth = new CelestialBody(*planets.earth);
    CelestialBody* moon = new CelestialBody(*planets.moon);
    double totalt = 2.71e6; 	//29 days > 27 days which is the period
    double dt = 10.;		//2e5 iterations
    std::cout<<"Simulating Earth and Moon\n";
    std::vector<std::vector<double>> vector_r = equivalentBodySimulation(*earth, *moon, totalt, dt);
    std::cout<<"\nSuccessfully simulated Earth and Moon\n\n";
    delete earth;	//to initialize it later
    delete moon;	//to free memory
    std::vector<double> results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"\nEarth and Moon results:\n";
    //std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k_simul = "<< std::pow(results[1],2) / std::pow(results[0],3)<<std::endl;
    std::cout<<"k_calc = "<< 4 * PI * PI / G / (moon->getMass() + earth->getMass())<<std::endl<<std::endl;
    results.clear();
    results.shrink_to_fit();
    //------------------------------------------------------
    //SUN EARTH SYSTEM
    earth = new CelestialBody(*planets.earth);
    CelestialBody* sun = new CelestialBody(*planets.sun);
    totalt = 3.3e7; 	//> 365 days which is the period
    dt = 100.;		//2e5 iterations
    std::cout<<"Simulating Sun and Earth\n";
    vector_r = equivalentBodySimulation(*sun, *earth, totalt, dt);
    std::cout<<"\nSuccessfully simulated Sun and Earth\n";
    delete earth;	
    delete sun;
    results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"\nSun and Earth results\n";
    //std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k_simul = "<< std::pow(results[1],2) / std::pow(results[0],3)<<std::endl;
    std::cout<<"k_calc = "<< 4 * PI * PI / G / (sun->getMass()+earth->getMass())<<std::endl<<std::endl;
    results.clear();
    results.shrink_to_fit();

    //------------------------------------------------------
    //SUN VENUS SYSTEM
    CelestialBody* venus = new CelestialBody(*planets.venus);
    sun = new CelestialBody(*planets.sun);
    totalt = 2.07e7; 	//> period
    dt = 100.;		//2e5 iterations
    std::cout<<"Simulating Sun and Venus\n";
    vector_r = equivalentBodySimulation(*sun, *venus, totalt, dt);
    std::cout<<"\nSuccessfully simulated Sun and Venus\n";
    delete venus;	
    delete sun;
    results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"\nSun and Venus results\n";
    //std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k_simul = "<< std::pow(results[1],2) / std::pow(results[0],3)<<std::endl;
    std::cout<<"k_calc = "<< 4 * PI * PI / G / (sun->getMass() + venus->getMass())<<std::endl<<std::endl;
    results.clear();
    results.shrink_to_fit();

    //------------------------------------------------------
    //SUN JUPITER SYSTEM
    CelestialBody* jupiter = new CelestialBody(*planets.jupiter);
    sun = new CelestialBody(*planets.sun);
    totalt = 3.8e8; 	//> period
    dt = 1000.;		//2e5 iterations
    std::cout<<"Simulating Sun and Jupiter\n";
    vector_r = equivalentBodySimulation(*sun, *jupiter, totalt, dt);
    std::cout<<"\nSuccessfully simulated Sun and Jupiter\n";
    delete jupiter;	
    delete sun;
    results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"\nSun and Jupiter results\n";
    //std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k_simul = "<< std::pow(results[1],2) / std::pow(results[0],3)<<std::endl;
    std::cout<<"k_calc = "<< 4 * PI * PI / G / (sun->getMass() + jupiter->getMass())<<std::endl<<std::endl;
; 
    results.clear();
    results.shrink_to_fit();
    return;
}





std::vector<double> orbitResults(std::vector<std::vector<double>> vector_r,double dt){
    //calculates the period T and the major semiaxis a of the orbital data 
    //stored in vector_r and returns {a,T}.
    unsigned int n = vector_r.size();
    std::vector<double> r_sq(n); // |vector_r|^2, to avoid calculating 2e5 sqrts 
    for (int i = 0; i < n; i++){
	r_sq[i] = std::pow(vector_r[i][0],2) + std::pow(vector_r[i][1],2) + std::pow(vector_r[i][2],2);
    }
    // we find the maximum and minimum of the distances.
    // the semiaxis a is a = 1/2 (r_max + r_min)
    // See the example at https://en.cppreference.com/w/cpp/algorithm/max_element.html
    std::vector<double>::iterator max = std::max_element(r_sq.begin(), r_sq.end());
    std::vector<double>::iterator min = std::min_element(r_sq.begin(), r_sq.end());

    double r_max = std::sqrt(*max); //the iterator points to the maximum value
    double r_min = std::sqrt(*min); 
    double a = 0.5 * (r_max + r_min); //major semiaxis

    // we then calculate the period as 2 times the time distance between r_max and r_min
    double t_max = dt * std::distance(r_sq.begin(),max); //this std::distance returns the index of the maximum element (see the example linked above)
    double t_min = dt * std::distance(r_sq.begin(),min);
    double T = 2. * std::abs(t_max-t_min);
    return {a,T};
}
