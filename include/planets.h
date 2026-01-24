#ifndef planets_h
#define planets_h
#include <iostream>
#include "solarsystem.h"
//Here are set the initial conditions for a stable solar system simulation
//with the class Planets: the members are the planets of the solar system, with
//initial conditions that will bring a stable simulation.
//Some information on the data:
//  - Masses, positions and velocities are in SI units (kg, m, m/s).
//  - The frame of reference considered is that of the center of the Sun, so sun_pos={0,0,0} and sun_vel={0,0,0}
//  - All data was generated with the webapp https://ssd.jpl.nasa.gov/horizons/app.html#/ 
//  - To replicate it, use the coordinate center "Sun (body center)" and look up the data for each body at the date and time
//    A.D. 2026-Jan-30 13:00:00.0000 TDB or, in Julian days, JD 2461071.041666667
//    Note that the app requires a nonzero time interval, but this data is taken from the exact time written above.
//	  

//
class Planets {
    public:
	Planets() {};

 	   ~Planets() {};

    	CelestialBody* sun = new CelestialBody("sun", 1.989e30, {0.,0.,0.}, {0.,0.,0.});

    	CelestialBody* mercury = new CelestialBody("mercury",3.302e23, {5.164264731482153e+10, -2.676720261491310e+10, -6.924043740469838e+09},{1.288336806141178e+4, 4.546427275870906e4, 2.533826363886032e3});

    	CelestialBody* venus = new CelestialBody("venus",4.867e24,{8.769946027625194e+10, -6.433023931703644e10, -5.944021387171965e9},{2.049543646691920e4, 2.809987045727895e4, -7.965283930576739e2});

    	CelestialBody* earth = new CelestialBody("earth",5.972e24, {-9.528390989855021e+10, 1.124217295009152e+11,-6.556357833042741e+6}, {-2.319595537882758e4, -1.936999554051368e4, 1.858789905649694e0});

    	CelestialBody* moon = new CelestialBody("moon", 7.349e22, {-9.533730772118732e+10, 1.127827640146280e+11, 2.235212433002889e+07}, {-2.426010758339047e4, -1.951481385321161e4, -4.542356065928299e1});

    	CelestialBody* mars = new CelestialBody("mars",6.417e23, {1.101197665450433e+11, -1.784274624080612e+11, -6.439375611159682e+09}, {2.153695769647704e4, 1.480518052997571e4, -2.178554894094828e3});

    	CelestialBody* jupiter = new CelestialBody("jupiter",1.898e27,{-2.851336993230751e+11, 7.273940135250134e+11, 3.357833214684933e+09}, {-1.232740719151334e4, -4.161987530224076e3, 2.930648458277834e2});

    	CelestialBody* saturn = new CelestialBody("saturn",5.683e26, {1.420018706737240e+12, 6.314217021835843e+10, -5.762472482205009e+10}, {-9.700062584360488e2, 9.628301523179667e3, -1.288722090637462e2});

    	CelestialBody* uranus = new CelestialBody("uranus",8.681e25, {1.462905365250269e+12, 2.521202204462178e+12, -9.605259337934494e+09}, {-5.952781527789759e3, 3.099664811063403e3, 8.868023484104293e1});

	CelestialBody* neptune = new CelestialBody("neptune",1.024e26, {4.468422614948322e+12, 9.158366634669828e+10, -1.048576410953995e+11}, {-1.588613408233427e2, 5.464853789990736e+3, -1.093245007061039e2});

    	std::vector<CelestialBody*> list_of_planets = {sun, mercury, venus, earth, moon, mars, jupiter, saturn, uranus, neptune};
};


#endif
