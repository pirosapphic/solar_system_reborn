#ifndef solarsystem_h
#define solarsystem_h
#include<string>
//alternatively
//#pragma once
//!without endif!

class object{
  public:
    void printinfo();
    object(std::string name, double mass ,double x, double y, double z, double vx, double vy, double vz); //default constructor
    object(std::string name, double mass, double* pos, double* vel); //array constructor
    ~object(); //destructor
  private: //or protected???
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
};

#endif
