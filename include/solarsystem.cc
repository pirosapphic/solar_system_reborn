#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "solarsystem.h"

CelestialBody::CelestialBody (std::string name, double mass, std::vector<double> position, std::vector<double> velocity) {
    m_name = name;
    m_mass = mass;
    m_position = position;
    m_velocity = velocity;
}

void CelestialBody::printState() {
    std::cout << "The state of " << m_name << " is:\n";
    std::cout << "  mass: " << m_mass << "\n";
    std::cout << "  position: (" << m_position[0] << ", " << m_position[1] <<", " << m_position[2] << ")m\n";
    std::cout << "  velocity: (" << m_velocity[0] << ", " << m_velocity[1] <<", " << m_velocity[2] << ")m/s\n";
}

// getters

double CelestialBody::getMass() {
    return m_mass;
}

double CelestialBody::getX() {
    return m_position[0];
}
double CelestialBody::getY() {
    return m_position[1];
}    
double CelestialBody::getZ() {
    return m_position[2];
}    

double CelestialBody::getVx() {
    return m_velocity[0];
}
double CelestialBody::getVy() {
    return m_velocity[1];
}    
double CelestialBody::getVz() {
    return m_velocity[2];
}    

std::vector<double> CelestialBody::getPos() {
    return m_position;
}

std::vector<double> CelestialBody::getVel() {
    return m_velocity;
}

// setters

void CelestialBody::setName(std::string new_name) {
    m_name = new_name;
}

void CelestialBody::setMass(double new_mass) {
    m_mass = new_mass;
}

void CelestialBody::setX(double new_x) {
    m_position[0] = new_x;
}
void CelestialBody::setY(double new_y) {
    m_position[1] = new_y;
}
void CelestialBody::setZ(double new_z) {
    m_position[2] = new_z;
}


void CelestialBody::setVx(double new_vx) {
    m_velocity[0] = new_vx;
}
void CelestialBody::setVy(double new_vy) {
    m_velocity[1] = new_vy;
}
void CelestialBody::setVz(double new_vz) {
    m_velocity[2] = new_vz;
}

void CelestialBody::setPos(std::vector<double> new_pos) {
    m_position = new_pos;
}
void CelestialBody::setVel(std::vector<double> new_vel) {
    m_position = new_vel;
}


void CelestialBody::updatePos(double dt){
    m_position[0]+=m_velocity[0]*dt;
    m_position[1]+=m_velocity[1]*dt;
    m_position[2]+=m_velocity[2]*dt;
}

void CelestialBody::GravitationalForce(double G) {

	CelestialBody& Body1 = Bodies[0];		//Sole
	CelestialBody& Body2 = Bodies[1];		//Generico altro pianeta
	
	double dx = Body1.getX() - Body2.getX();
	double dy = Body1.getY() - Body2.getY();
	double dz = Body1.getZ() - Body2.getZ();

	double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	
	//Versori
	
	double Ux = dx / distance;
	double Uy = dy / distance;
	double Uz = dz / distance;
	
	double force = G * ((Body1.getMass() * Body2.getMass()) / (distance * distance));

	double acceleration1 = force / Body1.getMass();	//da mettere poi la massa ridotta
	double acceleration2 = force / Body2.getMass();	//da mettere poi la massa ridotta
		
	Body1.m_velocity[0]+=acceleration1*Ux;
    	Body1.m_velocity[1]+=acceleration1*Uy;
    	Body1.m_velocity[2]+=acceleration1*Uz;
    	
    	Body2.m_velocity[0]+=acceleration2*Ux;
    	Body2.m_velocity[1]+=acceleration2*Uy;
    	Body2.m_velocity[2]+=acceleration2*Uz;
	
	
	
}


