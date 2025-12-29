#ifndef solarsystem_h
#define solarsystem_h
#include <iostream>
#include <vector>
#include <string>

//alternatively
//#pragma once
//!without endif!


// The following convention is wise to be followed:
// naming prefix:
//      m for members
//      p for pointers (pp for pointers to pointers) 
//      i for indexes and iterators (i++) 
//      ...


// The following naming convention is wise to be followed too (if you want to stay alive...):
// naming convention:
//      variables are to be named meaningfully, write a name that explains what the "x" is (for this specific situation snake_case is preferred over camelCase): mass, width, moon_orbit... 
//      functions and methods are to be named starting with a lower case letter: exampleMethod()
//      constants are all upper case: PI=3.141...
//      types (classes or whatever) start with uppercase letters and follow CamelCase convention: CelestialBody (see later)
//
// Other rules are free to be added. Last but not least:
// 
// whoever will add "using namespace std" at the start of ANY file will be mocked, bullied, prosecuted and publicly punished by me (0universe0). Have a great time coding ;)

class CelestialBody {

    public:
        CelestialBody (std::string name, double mass, std::vector<double> position);
        ~CelestialBody () {};

        void printState();

        // getters
        std::string getName();
        double getMass(); 
        double getX();
        double getY();
        std::vector<double> getPos();
     
        // setters
        void setName(std::string new_name);
        void setMass(double new_mass);
        void setX(double new_x);
        void setY(double new_y);
        void setPos(std::vector<double> new_pos); 
         
    private:
        std::string m_name;
        double m_mass;
        std::vector<double> m_position;
}; 

#endif
