#include <GL/freeglut.h>
#include <stdio.h>

#include "particle.hpp"
#include "billboardSystem.hpp"

const float pi = 3.1415926f;
// window size
int width = 1200;
int height = 400;

// camera info
float x_angle = 0.0;
float y_angle = 0.0;
bool left_botton_down = false;

// Particle System
xishanju::ParticleSystem ps;

// Billboard Sytem
xishanju::BillboardSystem bs;

void handleMouse(int button, int state, int x, int y){
  if (button ==GLUT_LEFT_BUTTON){
    if (state == GLUT_DOWN){
      left_botton_down = true;
    }else {
      left_botton_down = false;
    }
  }
}

void handleMotion(int x, int y){
  if (left_botton_down){
    x_angle = float(x - width / 2)/width * pi;
    y_angle = float(y - height / 2)/height * pi;
    //    printf("%f %f\n", x_angle, y_angle);
   }
  glutPostRedisplay();
}
void initRendering(){
  glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h){
  width = w;
  height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(20.0, float(w)/float(h), 1, 10000);

  
}

void drawScene() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //  printf("%f %f\n", x_angle, y_angle);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 300, 1600, 0, 0, 0, 0, 1, 0);

  glRotatef(x_angle * 30, 0.0, 1.0, 0.0);
  glRotatef(y_angle * 20, 1.0, 0.0, 0.0);
  
  ps.drawParticles();
  bs.drawBillboards();

  glutSwapBuffers();
}
int main(int argc, char **argv){
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  
  glutCreateWindow("XiShanJu Demo");
  
  initRendering();
  ps.initParticles();
  bs.initBillboards();

  glutDisplayFunc(drawScene);
  glutReshapeFunc(handleResize);
  glutMotionFunc(handleMotion);
  glutMouseFunc(handleMouse);
  glutMainLoop();

  return 0;
}
