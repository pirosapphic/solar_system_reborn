#include "solarsystem.h"
#include<iostream>
#include<string>

//OBJECT

object::object():
  m_name("DEFAULT"),
  m_mass(0.),
  m_x(0.),
  m_y(0.),
  m_z(0.),
  m_vx(0.),
  m_vy(0.),
  m_vz(0.)
{}; //default-valued constructor

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
  std::cout << "Mass of "<<m_name<<": "<<m_mass<<"kg\n";
  std::cout << "Position of "<<m_name<<": ("<<m_x<<", "<<m_y<<", "<<m_z<<")m\n";
  std::cout << "Velocity of "<<m_name<<": ("<<m_vx<<", "<<m_vy<<", "<<m_vz<<")m/s\n";
};

void object::update_pos(double dt){
  m_x += m_vx*dt;
  m_y += m_vy*dt;
  m_z += m_vz*dt;
};

void object::update_vel(double ax, double ay, double az, double dt){
  m_vx +=ax*dt;
  m_vy +=ay*dt;
  m_vz +=az*dt;
};

void object::update_vel(double* acc, double dt){
  object::update_vel(acc[0],acc[1],acc[2], dt);
};


//-------------------------------------------------------------------------------

//STAR

star::star():
  object()
{}; //default-valued constructor

star::star(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
  object(name, mass, x, y, z, vx, vy, vz)
{}; //default constructor using object default constructor


star::star(std::string name, double mass, double* pos, double* vel):
  object(name, mass, pos, vel)
{}; //array constructor using object array constructor

void star::printinfo(){
  //std::cout << m_name<<" is a star!\n";
  object::printinfo(); //cool mechanism! 
};

void star::update_pos(double dt){
  object::update_pos(dt);
};

void star::update_vel(double ax, double ay, double az, double dt){
  object::update_vel(ax,ay,az,dt);
};

void star::update_vel(double* acc,double dt){
  object::update_vel(acc,dt);
};


//-------------------------------------------------------------------------------

//PLANET

planet::planet():
  object()
{}; //default-valued constructor

planet::planet(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
  object(name, mass, x, y, z, vx, vy, vz)
{}; //default constructor using object default constructor


planet::planet(std::string name, double mass, double* pos, double* vel):
  object(name, mass, pos, vel)
{}; //array constructor using object array constructor

void planet::printinfo(){
  //std::cout << m_name<<" is a planet!\n";
  object::printinfo(); //cool mechanism! 
};

void planet::update_pos(double dt){
  object::update_pos(dt);
};

void planet::update_vel(double ax, double ay, double az, double dt){
  object::update_vel(ax,ay,az,dt);
};

void planet::update_vel(double* acc,double dt){
  object::update_vel(acc,dt);
};


//-------------------------------------------------------------------------------

//MOON

moon::moon():
  object()
{}; //default-valued constructor

moon::moon(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz):
  object(name, mass, x, y, z, vx, vy, vz)
{}; //default constructor using object default constructor

moon::moon(std::string name, double mass, double* pos, double* vel):
  object(name, mass, pos, vel)
{}; //array constructor using object array constructor

void moon::printinfo(){
//  std::cout << m_name<<" is a moon\n";
  object::printinfo(); //cool mechanism! 
};

void moon::update_pos(double dt){
  object::update_pos(dt);
};

void moon::update_vel(double ax, double ay, double az, double dt){
  object::update_vel(ax,ay,az,dt);
};

void moon::update_vel(double* acc,double dt){
  object::update_vel(acc,dt);
};
