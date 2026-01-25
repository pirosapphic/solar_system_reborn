#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "solarsystem.h"

//The class CelestialBody and its methods are implemented here

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

CelestialBody::CelestialBody(const CelestialBody& p):
    m_name(p.m_name),
    m_mass(p.m_mass),
    m_x(p.m_pos[0]),
    m_y(p.m_pos[1]),
    m_z(p.m_pos[2]),
    m_vx(p.m_vel[0]),
    m_vy(p.m_vel[1]),
    m_vz(p.m_vel[2]),
    m_pos(p.m_pos),
    m_vel(p.m_vel)
{}; // Copy constructor

void CelestialBody::printInfo() {
    //prints the state of the body, used for debugging
    std::cout << "The state of " << m_name << " is:\n";
    std::cout << "  mass: " << m_mass << " kg\n";
    std::cout << "  position: (" << m_pos[0] << ", " << m_pos[1] << ", " << m_pos[2] <<")m\n";
    std::cout << "  velocity: (" << m_vel[0] << ", " << m_vel[1] << ", " << m_vel[2] <<")m/s\n";
}

// getters
std::string CelestialBody::getName() {
    return m_name;
}

double CelestialBody::getMass() {
    return m_mass;
}

double CelestialBody::getX() {
    return m_pos[0];
}
double CelestialBody::getY() {
    return m_pos[1];
}    
double CelestialBody::getZ() {
    return m_pos[2];
}    

double CelestialBody::getVx() {
    return m_vel[0];
}
double CelestialBody::getVy() {
    return m_vel[1];
}    
double CelestialBody::getVz() {
    return m_vel[2];
}    

std::vector<double> CelestialBody::getPos() {
    return m_pos;
}

std::vector<double> CelestialBody::getVel() {
    return m_vel;
}

std::vector<double> CelestialBody::getVirtualAcc() {
    return m_virtual_acc;
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
void CelestialBody::setZ(double new_z) {
    m_pos[2] = new_z;
}

void CelestialBody::setVx(double new_vx) {
    m_vel[0] = new_vx;
}
void CelestialBody::setVy(double new_vy) {
    m_vel[1] = new_vy;
}
void CelestialBody::setVz(double new_vz) {
    m_vel[2] = new_vz;
}

void CelestialBody::setPos(std::vector<double> new_pos) {
    m_pos = new_pos;
}

void CelestialBody::setVel(std::vector<double> new_vel) {
    m_vel = new_vel;
}

void CelestialBody::setVirtualAcc(std::vector<double> virtual_acc) {
    m_virtual_acc = virtual_acc;
}



void CelestialBody::updatePos(double dt){
    //updates the position of the body after a time dt
    m_x += m_vx*dt;
    m_y += m_vy*dt;
    m_z += m_vz*dt;
    for(int i = 0; i < m_pos.size(); i++) {
        m_pos[i] += m_vel[i]*dt;
    }
}


void CelestialBody::updateVel(double ax, double ay, double az, double dt){
    //overloading of thew next function, this should NOT be used outside of there.
    m_vx +=ax*dt;
    m_vy +=ay*dt;
    m_vz +=az*dt;
}

void CelestialBody::updateVel(std::vector<double> acc, double dt){
    //updates the velocity of the body after a time dt
    CelestialBody::updateVel(acc[0], acc[1], acc[2], dt);
    for(int i = 0; i < m_pos.size(); i++) {
        m_vel[i] += acc[i]*dt;
    }
}
