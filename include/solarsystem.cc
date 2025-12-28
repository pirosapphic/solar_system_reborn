#include "solarsystem.h"
#include<iostream>
#include<string>

object::object(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
  m_name(name),
  m_mass(mass),
  m_x(x),
  m_y(y),
  m_z(z),
  m_vx(vx),
  m_vy(vy),
  m_vz(vz)
{}; //default constructor

object::object(std::string name, double mass, double* pos, double* vel):
  m_name(name),
  m_mass(mass),
  m_x(pos[0]),
  m_y(pos[1]),
  m_z(pos[2]),
  m_vx(vel[0]),
  m_vy(vel[1]),
  m_vz(vel[2])
{}; //array constructor



void object::printinfo(){
  std::cout << "Position of "<<m_name<<": ("<<m_x<<", "<<m_y<<", "<<m_z<<")m\n";
  std::cout << "Velocity of "<<m_name<<": ("<<m_vx<<", "<<m_vy<<", "<<m_vz<<")m/s\n";
};

