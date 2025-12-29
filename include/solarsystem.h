#ifndef solarsystem_h
#define solarsystem_h
#include<string>
//alternatively
//#pragma once
//!without endif!

class object{
  public:
    void printinfo();
    void update_pos(double dt);
    void update_vel(double ax, double ay, double az, double dt);
    void update_vel(double* acc, double dt);
  
    object();
    object(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz); //default constructor
    object(std::string name, double mass, double* pos, double* vel); //array constructor
    ~object(); //destructor
  protected:
    std::string m_name;
    double m_mass;
    double m_x;
    double m_y;
    double m_z;
    double m_vx;
    double m_vy;
    double m_vz;
};

class star: public object{
  public:
    void printinfo();
    void update_pos(double dt);
    void update_vel(double ax, double ay, double az, double dt);
    void update_vel(double* acc, double dt);
    
    star();
    star(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz); //default constructor
    star(std::string name, double mass, double* pos, double* vel); //array constructor
    ~star();
};

class planet: public object{
  public:
    void printinfo();
    void update_pos(double dt);
    void update_vel(double ax, double ay, double az, double dt);
    void update_vel(double* acc, double dt);
    
    planet();
    planet(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz); //default constructor
    planet(std::string name, double mass, double* pos, double* vel); //array constructor
    ~planet();
};


class moon: public object{
  public:
    void printinfo();
    void update_pos(double dt);
    void update_vel(double ax, double ay, double az, double dt);
    void update_vel(double* acc, double dt);
    
    moon();
    moon(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz); //default constructor
    moon(std::string name, double mass, double* pos, double* vel); //array constructor
    ~moon();
};
#endif
