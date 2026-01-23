#ifndef solarsystem_h
#define solarsystem_h
#include <iostream>
#include <vector>
#include <string>


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



//In this file we declare the class CelestialBody with its methods,
//the fundamental part of this project



class CelestialBody {

    private:
        std::string m_name;
        double m_mass;

        double m_x;
        double m_y;
        double m_z;
        double m_vx;
        double m_vy;
        double m_vz;

        std::vector<double> m_pos;
        std::vector<double> m_vel;
        std::vector<double> m_virtual_acc; //this is used to store the current acceleration in
					   //the n bodies simulator
    
    public:

        CelestialBody();

        CelestialBody(std::string name, double mass, double x, double y, double z, double vx, double vy, double vz); //default constructor
        
        CelestialBody(std::string name, double mass, std::vector<double> pos, std::vector<double> vel); //std::vector constructor

        CelestialBody(const CelestialBody& p); //copy constructor
    
	~CelestialBody () {};

        void printInfo();

        // getters
        std::string getName();
        double getMass(); 
        double getX();
        double getY();
        double getZ();

        double getVx();
        double getVy();
        double getVz();
        
        std::vector<double> getPos();
        std::vector<double> getVel();
        std::vector<double> getVirtualAcc();
     
        // setters
        void setName(std::string new_name);
        void setMass(double new_mass);
        
        void setX(double new_x);
        void setY(double new_y);
        void setZ(double new_z);

        void setVx(double new_vx);
        void setVy(double new_vy);
        void setVz(double new_vz);
        
        void setPos(std::vector<double> new_pos); 
        void setVel(std::vector<double> new_vel); 
        void setVirtualAcc(std::vector<double> virtual_acc);

        void updatePos(double dt);
        void updateVel(std::vector<double> acc, double dt);
        void updateVel(double ax, double ay, double az, double dt); //used only in the previous
								    //method
};
#endif
