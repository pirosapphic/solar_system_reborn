#include<iostream>
#include<string>
#include<vector>
#include"solarsystem.h"

int main () {
  std::vector<double> pos = {0.,0.,0.};
  std::vector<double> vel = {1.,1.,1.};
  CelestialBody* obj = new CelestialBody("generico",0.,0.,0.,0.,1.,0.,1.);
  Star* s = new Star("sole",1e5,pos,vel);
  Planet* t = new Planet("terra",1e3,pos,vel);
  Moon* l = new Moon();
  obj->printInfo();
  s->printInfo();
  t->printInfo();
  l->printInfo();
  double dt = 1;
  obj->updatePos(dt);
  s->updatePos(dt);
  t->updatePos(dt);
  l->updatePos(dt);
  std::cout << "POSITIONS UPDATED\n";
  obj->printInfo();
  s->printInfo();
  t->printInfo();
  l->printInfo();
  std::vector<double> acc = {1.,1.,1.};
  obj->updateVel(acc,dt);
  s->updateVel(acc,dt);
  t->updateVel(acc,dt);
  l->updateVel(acc,dt);
  std::cout << "VELOCITIES UPDATED\n"; 
  obj->printInfo();
  s->printInfo();
  t->printInfo();
  l->printInfo();
  return 0;
}
