#include <iostream>
#include <vector>
#include <string>

#include "solarsystem.h"

CelestialBody::CelestialBody():
    m_name("DEFAULT"),
    m_mass(0.),
    m_x(0.),
    m_y(0.),
    m_z(0.),
    m_vx(0.),
    m_vy(0.),
    m_vz(0.)
{
    m_pos.push_back(0.);
    m_pos.push_back(0.);
    m_pos.push_back(0.);
    m_vel.push_back(0.);
    m_vel.push_back(0.);
    m_vel.push_back(0.);
}; // Default Constructor

CelestialBody::CelestialBody(std::string name, double mass, double x, double y, double z, double vx, double vy, double vz):
    m_name(name),
    m_mass(mass),
    m_x(x),
    m_y(y),
    m_z(z),
    m_vx(vx),
    m_vy(vy),
    m_vz(vz)
{
    m_pos.push_back(x);
    m_pos.push_back(y);
    m_pos.push_back(z);
    m_vel.push_back(vx);
    m_vel.push_back(vy);
    m_vel.push_back(vz);
}; // Main Constructor

CelestialBody::CelestialBody(std::string name, double mass, std::vector<double> pos, std::vector<double> vel):
    m_name(name),
    m_mass(mass),
    m_x(pos[0]),
    m_y(pos[1]),
    m_z(pos[2]),
    m_vx(vel[0]),
    m_vy(vel[1]),
    m_vz(vel[2]),
    m_pos(pos),
    m_vel(vel)
{}; // Constructor with std::vector

void CelestialBody::printInfo() {
    std::cout << "The state of " << m_name << " is:\n";
    std::cout << "  mass: " << m_mass << "\n";
    std::cout << "  position: (" << m_pos[0] << ", " << m_pos[1] << ")\n";
    std::cout << "  velocity: (" << m_vel[0] << ", " << m_vel[1] << ")\n";
}

// getters

double CelestialBody::getMass() {
    return m_mass;
}

double CelestialBody::getX() {
    return m_pos[0];
}
double CelestialBody::getY() {
    return m_pos[1];
}    

std::vector<double> CelestialBody::getPos() {
    return m_pos;
}

// setters

void CelestialBody::setName(std::string new_name) {
    m_name = new_name;
}

void CelestialBody::setMass(double new_mass) {
    m_mass = new_mass;
}

void CelestialBody::setX(double new_x) {
    m_pos[0] = new_x;
}

void CelestialBody::setY(double new_y) {
    m_pos[1] = new_y;
}

void CelestialBody::setPos(std::vector<double> new_pos) {
    m_pos = new_pos;
}


//Object

//void CelestialBody::printInfo(){
//    std::cout << "Mass of "<<m_name<<": "<<m_mass<<"kg\n";
//    std::cout << "pos of "<<m_name<<": ("<<m_x<<", "<<m_y<<", "<<m_z<<")m\n";
//    std::cout << "vel of "<<m_name<<": ("<<m_vx<<", "<<m_vy<<", "<<m_vz<<")m/s\n";
//};

void CelestialBody::updatePos(double dt){
    m_x += m_vx*dt;
    m_y += m_vy*dt;
    m_z += m_vz*dt;


    for(int i = 0; i < m_pos.size(); i++) {
        m_pos[i] += m_vel[i]*dt;
    }
};

void CelestialBody::updateVel(double ax, double ay, double az, double dt){
    m_vx +=ax*dt;
    m_vy +=ay*dt;
    m_vz +=az*dt;
};

void CelestialBody::updateVel(std::vector<double> acc, double dt){
    CelestialBody::updateVel(acc[0], acc[1], acc[2], dt);
    
    for(int i = 0; i < m_pos.size(); i++) {
        m_vel[i] += acc[i]*dt;
    }
};


//-------------------------------------------------------------------------------

//Star

Star::Star():
    CelestialBody()
{}; // default constructor

Star::Star(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
    CelestialBody(name, mass, x, y, z, vx, vy, vz)
{}; // main constructor using CelestialBody main constructor


Star::Star(std::string name, double mass, std::vector<double> pos, std::vector<double> vel):
    CelestialBody(name, mass, pos, vel)
{}; // array constructor using CelestialBody array constructor

void Star::printInfo(){
    //std::cout << m_name<<" is a Star!\n";
    CelestialBody::printInfo(); //cool mechanism! 
};

void Star::updatePos(double dt){
    CelestialBody::updatePos(dt);
};

void Star::updateVel(double ax, double ay, double az, double dt){
    CelestialBody::updateVel(ax,ay,az,dt);
};

void Star::updateVel(std::vector<double> acc, double dt){
    CelestialBody::updateVel(acc,dt);
};


//-------------------------------------------------------------------------------

//Planet

Planet::Planet():
    CelestialBody()
{}; // default constructor

Planet::Planet(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
    CelestialBody(name, mass, x, y, z, vx, vy, vz)
{}; // main constructor using CelestialBody main constructor


Planet::Planet(std::string name, double mass, std::vector<double> pos, std::vector<double> vel):
    CelestialBody(name, mass, pos, vel)
{}; // array constructor using CelestialBody array constructor

void Planet::printInfo(){
    // std::cout << m_name<<" is a Planet!\n";
    CelestialBody::printInfo(); //cool mechanism! 
};

void Planet::updatePos(double dt){
    CelestialBody::updatePos(dt);
};

void Planet::updateVel(double ax, double ay, double az, double dt){
    CelestialBody::updateVel(ax,ay,az,dt);
};

void Planet::updateVel(std::vector<double> acc, double dt){
    CelestialBody::updateVel(acc,dt);
};


//-------------------------------------------------------------------------------

//Moon

Moon::Moon():
    CelestialBody()
{}; // default constructor

Moon::Moon(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
    CelestialBody(name, mass, x, y, z, vx, vy, vz)
{}; // main constructor using CelestialBody main constructor

Moon::Moon(std::string name, double mass, std::vector<double> pos, std::vector<double> vel):
    CelestialBody(name, mass, pos, vel)
{}; // array constructor using CelestialBody array constructor

void Moon::printInfo() {
    // std::cout << m_name<<" is a Moon\n";
    CelestialBody::printInfo(); //cool mechanism! 
};

void Moon::updatePos(double dt){
    CelestialBody::updatePos(dt);
};

void Moon::updateVel(double ax, double ay, double az, double dt){
    CelestialBody::updateVel(ax,ay,az,dt);
};

void Moon::updateVel(std::vector<double> acc, double dt){
    CelestialBody::updateVel(acc,dt);
};
