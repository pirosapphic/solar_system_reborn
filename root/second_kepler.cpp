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


std::vector<double> arealVelocity(std::vector<std::vector<double>> orbital_data, double dt);
//implemented below

void second_kepler(){
    Planets planets;
    //-----------------------------------------------------------------------
    //EARTH SUN ORBIT
    CelestialBody* earth = new CelestialBody(*planets.earth);
    CelestialBody* sun = new CelestialBody(*planets.sun);
    //365 days = 3.154e7 seconds
    double totalt = 3.154e7;
    double dt = 100.;
    twoBodiesSimulation(*earth,*sun,totalt,dt,"./root/csv/second_kepler_sun_earth.csv");
    std::vector<std::vector<double>> data_sun_earth = csvReaderToDouble("./root/csv/second_kepler_sun_earth.csv",1);
    std::vector<double> areal_sun_earth = arealVelocity(data_sun_earth, dt);
    unsigned int n = data_sun_earth[0].size();
    data_sun_earth.clear();
    data_sun_earth.shrink_to_fit(); //deallocating

    std::vector<double> sun_earth_time; //array for the graph time axis
    for(int i = 0; i < areal_sun_earth.size(); i++){
	sun_earth_time.push_back(i*dt);
    }
    std::cout<<"Sun earth\n";
    std::cout<<"dA/dt(t=0s) = "<<areal_sun_earth[0]<<std::endl;
    std::cout<<"dA/dt(t=365days) = "<<areal_sun_earth[n-2]<<std::endl;
    //std::cout<<"Difference = "<<areal_sun_earth[n-2]-areal_sun_earth[0]<<"m^2/s"<<std::endl;
    delete sun; //to free memory 
    delete earth; //twoBodiesSimulation takes CelestialBody&, so we need to recreate
		  //the object to have the correct initial conditions.
    CelestialBody* moon = new CelestialBody(*planets.moon);
    earth = new CelestialBody(*planets.earth);
    totalt = 2.55e6;
    dt = 10.;
    twoBodiesSimulation(*earth,*moon,totalt,dt,"./root/csv/second_kepler_earth_moon.csv");

    std::vector<std::vector<double>> data_earth_moon = csvReaderToDouble("./root/csv/second_kepler_earth_moon.csv",1);
    n = data_earth_moon[0].size();
    std::vector<double> areal_earth_moon = arealVelocity(data_earth_moon, dt);
    data_earth_moon.clear();
    data_earth_moon.shrink_to_fit(); //deallocating
    
    std::vector<double> earth_moon_time; //array for the graph time axis
    for(int i = 0; i < areal_earth_moon.size(); i++){
	earth_moon_time.push_back(i*dt);
    }
    std::cout<<"Earth moon\n";
    std::cout<<"dA/dt(t=0s) = "<<areal_earth_moon[0]<<std::endl;
    std::cout<<"dA/dt(t=29days) = "<<areal_earth_moon[n-2]<<std::endl;
    //std::cout<<"Difference = "<<areal_earth_moon[n-2]-areal_earth_moon[0]<<"m^2/s"<<std::endl;

//----------------------------------------------------------------------------------
    //now for the graphic part: we now graph dA/dt(t) to show that it is constant
    TCanvas* c1 = new TCanvas("earth sun","c1",1200,800);
    TGraph* gSE = new TGraph(areal_sun_earth.size(), sun_earth_time.data(), areal_sun_earth.data());
    gSE->Draw("AP");
    TCanvas* c2 = new TCanvas("earth moon","c2",1200,800);
    TGraph* gEM = new TGraph(areal_earth_moon.size(), earth_moon_time.data(), areal_earth_moon.data());
    gEM->Draw("AP");
}


std::vector<double> arealVelocity(std::vector<std::vector<double>> orbital_data, double dt){ 
    std::cout<<"Now calculating dA/dt\n";
    unsigned int n = orbital_data[0].size(); //number of iterations
    std::vector<std::vector<double>> pos1;
    std::vector<std::vector<double>> pos2;
    //we re-call the data in these vectors of vectors, so that
    //pos1[i] is the position of the first body at the time i*dt
    for (int i = 0; i < n; i++){
	pos1.push_back({orbital_data[0][i],orbital_data[1][i],orbital_data[2][i]});
	pos2.push_back({orbital_data[3][i],orbital_data[4][i],orbital_data[5][i]});
    }

    //now we need to calculate dA/dt for each time step
    //we calculate the vectorial distance between the two bodies r = r2-r1
    //we calculate the vector delta_r = r1(t+dt)-r1(t)
    //and their moduli
    std::vector<std::vector<double>> vector_r;
    std::vector<std::vector<double>> vector_delta_r;
    std::vector<double> r; //|r|(t)
    std::vector<double> delta_r; //|delta_r|(t)
    //here I use 4 separate for loops because the size of vector_r is not defined
    //until the loop is closed, so before that vector_r[i] has undefined behaiviour.

    //One could try to allocate the space beforehand with std::vector<double> r(size)
    //but it did not work for me.
    for (int i = 0; i < n; i++){
	vector_r.push_back({pos2[i][0] - pos1[i][0],pos2[i][1] - pos1[i][1],pos2[i][2] - pos1[i][2]});
    }
    vector_r.shrink_to_fit();
    
    for (int i = 0; i < n; i++){
	r.push_back(std::sqrt(std::pow(vector_r[i][0],2)+std::pow(vector_r[i][1],2)+std::pow(vector_r[i][2],2)));
    }
    r.shrink_to_fit();
    
    for (int i = 0; i < n-1; i++){ 
	vector_delta_r.push_back({vector_r[i+1][0]-vector_r[i][0],vector_r[i+1][1]-vector_r[i][1],vector_r[i+1][2]-vector_r[i][2]});
    }
    vector_delta_r.shrink_to_fit();

    for (int i = 0; i < n-1; i++){
	delta_r.push_back(std::sqrt(std::pow(vector_delta_r[i][0],2)+std::pow(vector_delta_r[i][1],2)+std::pow(vector_delta_r[i][2],2)));
    }
    delta_r.shrink_to_fit();

    //we use the triangles with sides |r(t)| |r(t+dt)| and |delta_r|
    //the area is 1/2*|r(t)|*|delta_r|*cos(alpha/2), where alpha is the angle between
    //r(t) and r(t+dt): dt is 100s, so the angle is REALLY small at this scale, so cos(alpha/2) = 1 and
    //dA/dt = (1/2*|r(t)|*|delta_r|)/dt

    std::vector<double> areal_velocity; 
    for (int i = 0; i < n-1; i++){
	areal_velocity.push_back(0.5*r[i]*delta_r[i]/dt);
    }
    areal_velocity.shrink_to_fit();
    return areal_velocity;
}
