#include <iostream>
#include <vector>
#include <string>

#include "solarsystem.h"

CelestialBody::CelestialBody (std::string name, double mass, std::vector<double> position) {
    m_mass = mass;
    m_position = position;
}

void CelestialBody::printState() {
    std::cout << "The state of " << m_name << " is:\n";
    std::cout << "  mass: " << m_mass << "\n";
    std::cout << "  position: (" << m_position[0] << ", " << m_position[1] << ")\n";
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

std::vector<double> CelestialBody::getPos() {
    return m_position;
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

void CelestialBody::setPos(std::vector<double> new_pos) {
    m_position = new_pos;
}
