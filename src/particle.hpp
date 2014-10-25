#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <GL/freeglut.h>
#include <vector>
#include <stdlib.h>

namespace xishanju{
  struct Particle{
    float x;
    float y;
    float z;
    float x_scale;
    float y_scale;
    Particle(float a, float b, float c, float as, float bs):\
      x(a), y(b), z(c), x_scale(as), y_scale(bs){}
  };
  class ParticleSystem {
  public:
    ParticleSystem();
    ~ParticleSystem();
   
    bool initParticles();
    void drawParticles();
  private:
    void createParticles(int n, float center, float range, float x_scale, float y_scale);
    void drawOneParticle(const struct Particle &p);
    float randone();
  private:
    std::vector<struct Particle> particles_;

  
    
  };
}

#endif
