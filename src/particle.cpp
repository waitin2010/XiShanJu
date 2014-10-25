#include "particle.hpp"
#include <stdio.h>
#include <math.h>

using namespace xishanju;

ParticleSystem::ParticleSystem(){
}

ParticleSystem::~ParticleSystem(){
  if(particles_.size()>0)
    particles_.clear();
}

void ParticleSystem::drawParticles(){
  
  for(int i=0;i<particles_.size();i++){
    drawOneParticle(particles_[i]);
  }

}

void ParticleSystem::drawOneParticle(const struct Particle &p){
  //  printf("%f, %f, %f \n", p.x, p.y, p.z);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  //left_up
  glVertex3f(p.x - p.x_scale, p.y + p.y_scale, p.z);
  //left_down
  glVertex3f(p.x - p.x_scale, p.y - p.y_scale, p.z);
  //right_down
  glVertex3f(p.x + p.x_scale, p.y - p.y_scale, p.z);
  //right_up
  glVertex3f(p.x + p.x_scale, p.y + p.y_scale, p.z);
  glEnd();
}

float ParticleSystem::randone(){
  return float(rand()) / RAND_MAX;
}
void ParticleSystem::createParticles(int n, float center, float range, float x_scale, float y_scale){
  for (int i=0;i<n;i++){
    float x = randone() * 2 - 1;
    float y = randone() * 2 - 1;
    float z = randone() * 2 - 1;

    float distance = x * x + y * y + z * z;
    x = x/ sqrt(distance);
    y = y/ sqrt(distance);
    z = z/ sqrt(distance);
    
    x *= randone() * range + center;
    y *= randone() * range + center;
    z *= randone() * range + center;

    struct Particle p(x, y, z, x_scale, y_scale);
    particles_.push_back(p);
  }
}

bool ParticleSystem::initParticles(){
  createParticles(20, 150, 10, 2.5, 2.5);
  createParticles(100, 300, 10, 1.6, 1.6);
  createParticles(200, 500, 10, 0.8, 0.8);
  createParticles(100, 650, 10, 0.5, 0.5);

  return true;
}
