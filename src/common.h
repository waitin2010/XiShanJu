#ifndef __COMMON_H__
#define __COMMON_H__

#include <GL/freeglut.h>
#include "png1.h"

inline GLuint createTexture(char *fileName){
  mPng::Image image;
  mPng::read(fileName, image);

  printf("%d %d %d\n", image.width, image.height, image.data[0]);
  GLuint tex_id;
  glGenTextures(1, &tex_id);
  glBindTexture(GL_TEXTURE_2D, tex_id);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


  return tex_id;
  
}
#endif
