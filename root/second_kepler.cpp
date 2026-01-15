#include <iostream>
#include <cmath>
#include <vector>
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

//We want to verify the second law of Kepler for planetary motion,
//which states that the areal velocity dA/dt is constant (where dA is the area
//swept by the orbiting body in an interval dt).
//We verify it as this defition states: we will simulate some orbits and calculate
//the areal velocities, we then will show that these are constant.
//The motions considered are the orbit of the moon around the earth and the
//orbit of the earth around the sun.
//
//Note that it is the equivalent body with reduced mass

std::vector<double> areal_velocity(std::vector<std::vector<double>> vector_r, double dt);

void new_kepler2(){
    Planets planets;
    //------------------------------------------------------
    //EARTH SUN SYSTEM
    CelestialBody* earth = new CelestialBody(*planets.earth);
    CelestialBody* sun = new CelestialBody(*planets.sun);

    double totalt = 3.154e7; 	//365 days
    double dt = 100.;		//3e5 iterations
    std::cout<<"Simulating sun and earth\n";
    std::vector<std::vector<double>> vector_r = equivalentBodySimulation(*sun, *earth, totalt, dt);
    std::cout<<"Successfully simulated sun and earth\n";
    unsigned int n = vector_r.size();
    delete earth;	//to initialize it later
    delete sun;		//to free memory
    std::cout<<"Now calculating dA/dt\n";
    std::vector<double> areal_SE = areal_velocity(vector_r,dt);
    vector_r.clear(); //to reuse it
    std::vector<double> times_SE(n-1);
    for(int i = 0; i < n-1; i++){
	times_SE[i] = i*dt;
    }
    //------------------------------------------------------
    //EARTH MOON SYSTEM
    earth = new CelestialBody(*planets.earth);
    CelestialBody* moon = new CelestialBody(*planets.moon);

    totalt = 2.71e6; 	//29 days
    dt = 10.;		//3e5 iterations
    std::cout<<"Simulating earth and moon\n";
    vector_r = equivalentBodySimulation(*earth, *moon, totalt, dt);
    std::cout<<"Successfully simulated earth and moon\n";
    n = vector_r.size();
    delete earth;	//to initialize it later
    delete moon;		//to free memory
    std::cout<<"Now calculating dA/dt\n";
    std::vector<double> areal_EM = areal_velocity(vector_r,dt);
    vector_r.clear();
    std::vector<double> times_EM(n-1);
    for(int i = 0; i < n-1; i++){
	times_EM[i] = i*dt;
    }
    //now we graph!
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
    gEM->Draw("AP");
}


std::vector<double> areal_velocity(std::vector<std::vector<double>> vector_r, double dt){
    //this function calculates the areal velocity of the orbit as a function of time
    // areal_velocity[i] = dA/dt(t=i*dt)
    
    //the vector r is the position vector of the equivalent body 
    //with respect to the center of rotation (i.e the focus of the ellipse)
    //We compute dA as a triangle with sides |r(t)| |r(t+dt)-r(t)| and |r(t+dt)|
    //the area is 1/2 |r(t) x r(t+dt)|, where x denotes the cross product.

    //we calculate the cross product, halve it and divide it by dt
    const unsigned int n = vector_r.size();
    std::vector<std::vector<double>> vector_cross(n-1, std::vector<double>(3)); //this declares the sizes
    std::vector<double> result(n-1); // 1/2*|vector_cross|/dt
    for(int i = 0; i < n-1; i++){	//we can calculate r(t+dt) up until t = steps*(dt-1)
	// (a0, a1, a2) x (b0, b1, b2) = (a1*b2 - a2*b1, a2*b0 - a0*b2, a0*b1 - a1*b0);
	// a = vector_r[i], b = vector_r[i+1]
	vector_cross[i] = {vector_r[i][1]*vector_r[i+1][2] - vector_r[i][2]*vector_r[i+1][1],vector_r[i][2]*vector_r[i+1][0] - vector_r[i][0]*vector_r[i+1][2],vector_r[i][0]*vector_r[i+1][1] - vector_r[i][1]*vector_r[i+1][0]};
	result[i] = 0.5*std::sqrt(std::pow(vector_cross[i][0],2)+std::pow(vector_cross[i][1],2)+std::pow(vector_cross[i][2],2))/dt;
    }
    return result;
}

