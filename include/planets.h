#ifndef planets_h
#define planets_h
#include <iostream>
#include "solarsystem.h"
//Here are set the initial conditions for a stable solar system simulation;
//	- masses, positions and velocities are in SI units
//	- the frame of reference considered is that of the center of the Sun, so sun_pos={0,0,0} and sun_vel={0,0,0}
//	- all data was generated with the webapp https://ssd.jpl.nasa.gov/horizons/app.html#/ 
//	- to replicate it, use the correct frame of reference and look up the data at the date and time
//	  A.D. 2026-Jan-30 13:00:00.0000 TDB or, in Julian days, 2461071.041666667
//
class Planets {
    public:
        Planets() {};
        ~Planets() {};
        CelestialBody* sun = new CelestialBody("sun", 1.989e30, {0.,0.,0.}, {0.,0.,0.});
	
    	CelestialBody* mercury = new CelestialBody("mercury",3.302e23, {5.164264731482153e+10, -2.676720261491310e+10, -6.924043740469838e+09},{1.288336806141178E+04, 4.546427275870906E+04, 2.533826363886032E+03});

        CelestialBody* venus = new CelestialBody("venus",4.867e24,{8.769946027625194e+10, -6.433023931703644e10, -5.944021387171965e09},{2.049543646691920E+04, 2.809987045727895E+04, -7.965283930576739e+02});
        
	CelestialBody* earth = new CelestialBody("earth",5.972e24, {-9.528390989855021E+10, 1.124217295009152E+11,-6.556357833042741E+06}, {-2.319595537882758E+04, -1.936999554051368E+04, 1.858789905649694E0});

	CelestialBody* moon = new CelestialBody("moon", 7.349e22, {-9.533730772118732E+10, 1.127827640146280E+11, 2.235212433002889E+07}, {-2.426010758339047E+04, -1.951481385321161E+04, -4.542356065928299E+1});
        
	CelestialBody* mars = new CelestialBody("mars",6.417e23, {1.101197665450433E+11, -1.784274624080612E+11, -6.439375611159682E+09}, {2.153695769647704E+04, 1.480518052997571E+04, -2.178554894094828E+03});

	CelestialBody* jupiter = new CelestialBody("jupiter",1.898e27,{-2.851336993230751E+11, 7.273940135250134E+11, 3.357833214684933E+09}, {-1.232740719151334E+04, -4.161987530224076E+03, 2.930648458277834E+02});

        CelestialBody* saturn = new CelestialBody("saturn",5.683e26, {1.420018706737240E+12, 6.314217021835843E+10, -5.762472482205009E+10}, {-9.700062584360488E+02, 9.628301523179667E+03, -1.288722090637462E+02});

        CelestialBody* uranus = new CelestialBody("uranus",8.681e25, {1.462905365250269E+12, 2.521202204462178E+12, -9.605259337934494E+09}, {-5.952781527789759E+03, 3.099664811063403E+03, 8.868023484104293E+01});

        CelestialBody* neptune = new CelestialBody("neptune",1.024e26, {1.462905365250269E+12, 2.521202204462178E+12, -9.605259337934494E+09},{-5.952781527789759E+03, 3.099664811063403E+03, 8.868023484104293E+01});
        
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
