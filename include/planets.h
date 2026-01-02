#ifndef planets_h
#define planets_h
#include <iostream>
#include "solarsystem.h"


class Planets {
    public:
        Planets() {};
        ~Planets() {};

        CelestialBody* sun = new CelestialBody("sun", 1.98e30, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* mercury = new CelestialBody("mercury",3.3e23, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* venus = new CelestialBody("venus",4.86e24, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* earth = new CelestialBody("earth",5.97e24, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* mars = new CelestialBody("mars",6.4e23, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* jupiter = new CelestialBody("jupiter",1.89e27, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* saturn = new CelestialBody("saturn",5.68e26, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* uranus = new CelestialBody("uranus",8.6e25, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* neptune = new CelestialBody("neptune",1.02e26, {0.,0.,0.}, {0.,0.,0.});
};

class DwarfPlanets { 
    public:
        CelestialBody* ceres = new CelestialBody("ceres",9.38e20, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* pluto = new CelestialBody("pluto",1.30e22, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* eris = new CelestialBody("eris",1.66e22, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* makemake = new CelestialBody("makemake",3.10e20, {0.,0.,0.}, {0.,0.,0.});
        CelestialBody* haumea = new CelestialBody("haumea",4.01e20, {0.,0.,0.}, {0.,0.,0.});
};


#endif
