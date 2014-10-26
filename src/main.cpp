#include <GL/freeglut.h>

#include "particle.hpp"
#include "billboardSystem.hpp"

// window size
int width = 1200;
int height = 400;

// Particle System
xishanju::ParticleSystem ps;

// Billboard Sytem
xishanju::BillboardSystem bs;

void initRendering(){
  glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h){
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(20.0, float(w)/float(h), 1, 10000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 300, 1600, 0, 0, 0, 0, 1, 0);
  
}

void drawScene() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
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
  glutMainLoop();

  return 0;
}
