#ifndef planets_h
#define planets_h
#include <iostream>
#include "solarsystem.h"
//Here are set the initial conditions for a stable solar system simulation;
//	- masses, positions and velocities are in SI units
//	- the frame of reference considered is that of the center of the Sun, so sun_pos={0,0,0} and sun_vel={0,0,0}
//	- all data was generated with the webapp https://ssd.jpl.nasa.gov/horizons/app.html#/ 
//	- to replicate it, use the correct frame of reference and look up the data at the date and time
//	  A.D. 2026-Jan-30 13:00:00.0000 TDB or, in Julian days, JD 2461071.041666667
//	  							 JD 2461072.041666667

//
class Planets {
    public:
        Planets() {};
        ~Planets() {};
        CelestialBody* sun = new CelestialBody("sun", 1.989e24, {0.,0.,0.}, {0.,0.,0.});
	
    	CelestialBody* mercury = new CelestialBody("mercury",3.302e17, {5.164264731482153e+4, -2.676720261491310e+4, -6.924043740469838e+03},{1.288336806141178e-02, 4.546427275870906e-02, 2.533826363886032e-03});

        CelestialBody* venus = new CelestialBody("venus",4.867e18,{8.769946027625194e+4, -6.433023931703644e4, -5.944021387171965e3},{2.049543646691920e-02, 2.809987045727895e-2, -7.965283930576739e-4});
        
	CelestialBody* earth = new CelestialBody("earth",5.972e18, {-9.528390989855021e+4, 1.124217295009152e+5,-6.556357833042741e+0}, {-2.319595537882758e-2, -1.936999554051368e-2, 1.858789905649694e-6});

	CelestialBody* moon = new CelestialBody("moon", 7.349e16, {-9.533730772118732e+4, 1.127827640146280e+5, 2.235212433002889e+01}, {-2.426010758339047e-2, -1.951481385321161e-2, -4.542356065928299e-5});
        
	CelestialBody* mars = new CelestialBody("mars",6.417e17, {1.101197665450433e+5, -1.784274624080612e+5, -6.439375611159682e+03}, {2.153695769647704e-2, 1.480518052997571e-2, -2.178554894094828e-3});

	CelestialBody* jupiter = new CelestialBody("jupiter",1.898e21,{-2.851336993230751e+5, 7.273940135250134e+5, 3.357833214684933e+03}, {-1.232740719151334e-2, -4.161987530224076e-3, 2.930648458277834e-4});

        CelestialBody* saturn = new CelestialBody("saturn",5.683e20, {1.420018706737240e+6, 6.314217021835843e+4, -5.762472482205009e+4}, {-9.700062584360488e-4, 9.628301523179667e-3, -1.288722090637462e-4});

        CelestialBody* uranus = new CelestialBody("uranus",8.681e19, {1.462905365250269e+6, 2.521202204462178e+6, -9.605259337934494e+03}, {-5.952781527789759e-3, 3.099664811063403e-3, 8.868023484104293e-5});

        CelestialBody* neptune = new CelestialBody("neptune",1.024e20, {1.462905365250269e+6, 2.521202204462178e+6, -9.605259337934494e+03},{-5.952781527789759e-03, 3.099664811063403e-03, 8.868023484104293e-5});
        
    //CelestialBody* pluto = new CelestialBody("pluto",1.30e22, {0.,0.,0.}, {0.,0.,0.});
        std::vector<CelestialBody*> list_of_planets = {sun, mercury, venus, earth, moon, mars, jupiter, saturn, uranus, neptune};
        CelestialBody* ceres = new CelestialBody("ceres",9.38e20, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* pluto = new CelestialBody("pluto",1.30e22, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* eris = new CelestialBody("eris",1.66e22, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* makemake = new CelestialBody("makemake",3.10e20, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* haumea = new CelestialBody("haumea",4.01e20, {0.,0.,0.}, {0.,0.,0.});
        std::vector<CelestialBody*> list_of_dwarf_planets = {ceres, pluto, eris, makemake, haumea};
};


#endif
