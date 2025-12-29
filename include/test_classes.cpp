#include<iostream>
#include<string>
#include"solarsystem.h"

int main () {
  double pos[3] = {0.,0.,0.};
  double vel[3] = {1.,1.,1.};
  object* obj = new object("generico",0.,0.,0.,0.,1.,0.,1.);
  star* s = new star("sole",1e5,pos,vel);
  planet* t = new planet("terra",1e3,pos,vel);
  moon* l = new moon();
  obj->printinfo();
  s->printinfo();
  t->printinfo();
  l->printinfo();
  double dt = 1;
  obj->update_pos(dt);
  s->update_pos(dt);
  t->update_pos(dt);
  l->update_pos(dt);
  std::cout << "POSITIONS UPDATED\n";
  obj->printinfo();
  s->printinfo();
  t->printinfo();
  l->printinfo();
  double acc[3] = {1.,1.,1.};
  obj->update_vel(acc,dt);
  s->update_vel(acc,dt);
  t->update_vel(acc,dt);
  l->update_vel(acc,dt);
  std::cout << "VELOCITIES UPDATED\n"; 
  obj->printinfo();
  s->printinfo();
  t->printinfo();
  l->printinfo();
  return 0;
}
