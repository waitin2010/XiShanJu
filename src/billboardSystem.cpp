#include "billboardSystem.hpp"
#include <GL/freeglut.h>
#include "common.h"

using namespace xishanju;

Billboard::Billboard(float a, float b, float c, float xw, float yw):\
  x(a), y(b), z(c), x_width(xw/2), y_width(yw/2), tex_id(0){

}
Billboard::~Billboard(){
}

void Billboard::drawBillboard(){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex_id);

  glEnable(GL_BLEND);

  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex3f(x - x_width, y - y_width, z);
  glTexCoord2f(1, 0);
  glVertex3f(x + x_width, y - y_width, z);
  glTexCoord2f(1, 1);
  glVertex3f(x + x_width, y + y_width, z);
  glTexCoord2f(0, 1);
  glVertex3f(x - x_width, y + y_width, z);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);

  
}
void Billboard::useTexture(char *fileName){
  tex_id = createTexture(fileName);
  printf("%d \n", tex_id);
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
  
  b1.useTexture("../image/center.png");
  b2.useTexture("../image/b1.png");
  b3.useTexture("../image/b2.png");
  b4.useTexture("../image/b3.png");
  b5.useTexture("../image/b4.png");

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
