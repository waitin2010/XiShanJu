#include "billboardSystem.hpp"
#include <GL/freeglut.h>
using namespace xishanju;

Billboard::Billboard(float a, float b, float c, float xw, float yw):\
  x(a), y(b), z(c), x_width(xw/2), y_width(yw/2){

}
Billboard::~Billboard(){
}

void Billboard::drawBillboard(){
  glColor3f(0.0, 0.2, 0.0);
  glBegin(GL_QUADS);
  glVertex3f(x - x_width, y - y_width, z);
  glVertex3f(x + x_width, y - y_width, z);
  glVertex3f(x + x_width, y + y_width, z);
  glVertex3f(x - x_width, y + y_width, z);
  glEnd();
}

BillboardSystem::BillboardSystem(){
}

BillboardSystem::~BillboardSystem(){
  if(billboards_.size() > 0)
    billboards_.clear();
}

bool BillboardSystem::initBillboards(){
  Billboard b1(0, 0, 0, 387, 167);
  Billboard b2(-400, 100, 10);
  Billboard b3(-200, -60, 30);
  Billboard b4(400, -25, 10);
  Billboard b5(200, 70, 50);
  
  billboards_.push_back(b1);
  billboards_.push_back(b2);
  billboards_.push_back(b3);
  billboards_.push_back(b4);
  billboards_.push_back(b5);
  
  return true;
}

void BillboardSystem::drawBillboards(){
  for(int i=0;i<billboards_.size();i++)
    billboards_[i].drawBillboard();
}
