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

void third_kepler(){
    Planets planets;
    //------------------------------------------------------
    //EARTH MOON SYSTEM
    CelestialBody* earth = new CelestialBody(*planets.earth);
    CelestialBody* moon = new CelestialBody(*planets.moon);
    double totalt = 2.71e6; 	//29 days > 27 days which is the period
    double dt = 10.;		//2e5 iterations
    std::cout<<"Simulating earth and moon\n";
    std::vector<std::vector<double>> vector_r = equivalentBodySimulation(*earth, *moon, totalt, dt);
    std::cout<<"Successfully simulated earth and moon\n";
    delete earth;	//to initialize it later
    delete moon;	//to free memory
    std::vector<double> results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"Earth moon results\n";
    std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k = "<< std::pow(results[1],2)/std::pow(results[0],3)<<std::endl;
    results.clear();
    results.shrink_to_fit();
    //------------------------------------------------------
    //SUN EARTH SYSTEM
    earth = new CelestialBody(*planets.earth);
    CelestialBody* sun = new CelestialBody(*planets.sun);
    totalt = 3.3e7; 	//> 365 days which is the period
    dt = 100.;		//2e5 iterations
    std::cout<<"Simulating sun and earth\n";
    vector_r = equivalentBodySimulation(*sun, *earth, totalt, dt);
    std::cout<<"Successfully simulated sun and earth\n";
    delete earth;	
    delete sun;
    results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"Sun Earth results\n";
    std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k = "<< std::pow(results[1],2)/std::pow(results[0],3)<<std::endl;
    results.clear();
    results.shrink_to_fit();

    //------------------------------------------------------
    //SUN VENUS SYSTEM
    CelestialBody* venus = new CelestialBody(*planets.venus);
    sun = new CelestialBody(*planets.sun);
    totalt = 2.07e7; 	//> period
    dt = 100.;		//2e5 iterations
    std::cout<<"Simulating sun and venus\n";
    vector_r = equivalentBodySimulation(*sun, *venus, totalt, dt);
    std::cout<<"Successfully simulated sun and venus\n";
    delete venus;	
    delete sun;
    results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"Sun Venus results\n";
    std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k = "<< std::pow(results[1],2)/std::pow(results[0],3)<<std::endl;
    results.clear();
    results.shrink_to_fit();

    //------------------------------------------------------
    //SUN VENUS SYSTEM
    CelestialBody* jupiter = new CelestialBody(*planets.jupiter);
    sun = new CelestialBody(*planets.sun);
    totalt = 3.8e8; 	//> period
    dt = 1000.;		//2e5 iterations
    std::cout<<"Simulating sun and jupiter\n";
    vector_r = equivalentBodySimulation(*sun, *jupiter, totalt, dt);
    std::cout<<"Successfully simulated sun and jupiter\n";
    delete jupiter;	
    delete sun;
    results = orbitResults(vector_r, dt);
    vector_r.clear();
    vector_r.shrink_to_fit();
    std::cout<<"Sun Jupiter results\n";
    std::cout<<"a = "<<results[0]<<"m\nT = "<<results[1]<<"s\n";
    std::cout<<"k = "<< std::pow(results[1],2)/std::pow(results[0],3)<<std::endl;
    results.clear();
    results.shrink_to_fit();
//------------------------------------------------------
    //now we graph!
    /*
    TCanvas* cSE = new TCanvas("cSE","sun earth",1200,800);
    TGraph* gSE = new TGraph(areal_SE.size(),times_SE.data(),areal_SE.data());
    cSE->cd();
    gSE->SetMarkerStyle(1);
    gSE->SetTitle("Areal velocity vs time, Sun Earth system;t[s];#frac{dA}{dt}[m^{2}/s]");
    gSE->GetHistogram()->SetMinimum(2226.68917e12); //sets y axis limits
    gSE->GetHistogram()->SetMaximum(2226.689173650e12);
    gSE->Draw("AP");
    TCanvas* cEM = new TCanvas("cEM","earth moon",1200,800);
    TGraph* gEM = new TGraph(areal_EM.size(),times_EM.data(),areal_EM.data());
    cEM->cd(); 
    gEM->SetMarkerStyle(1);
    gEM->SetTitle("Areal velocity vs time, Earth Moon system;t[s];#frac{dA}{dt}[m^{2}/s]");
    gEM->GetHistogram()->SetMinimum(196.775346876e9);
    gEM->GetHistogram()->SetMaximum(196.77534719e9);
    gEM->Draw("AP");*/
}

std::vector<double> orbitResults(std::vector<std::vector<double>> vector_r,double dt){
    unsigned int n = vector_r.size();
    std::vector<double> r_sq(n); // |vector_r|^2, to avoid calculating 2e5 sqrts 
    for (int i = 0; i < n; i++){
	r_sq[i] = std::pow(vector_r[i][0],2)+std::pow(vector_r[i][1],2)+std::pow(vector_r[i][2],2);
    }
    auto max = std::max_element(r_sq.begin(), r_sq.end()); //this is a std::vector::iterator (whatever that means...)!!!!!!!!!!!!!!!!!!!!!!!!
    auto min = std::min_element(r_sq.begin(), r_sq.end());
    //we calculate the major semiaxis as (r_min + r_max)/2
    double r_max = std::sqrt(*max);
    double r_min = std::sqrt(*min);
    double a = 0.5*(r_max + r_min); //major semiaxis
    // we then calculate the period as 2 times the time distance between r_max and r_min
    double t_max = dt*std::distance(r_sq.begin(),max); //this std::distance returns the index of the maximum element
    double t_min = dt*std::distance(r_sq.begin(),min);
    double T = 2.*std::abs(t_max-t_min);
    return {a,T};
}


