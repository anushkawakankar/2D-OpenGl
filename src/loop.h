#include "main.h"

#ifndef LOOP_H
#define LOOP_H

class Loop {
public:
  Loop() {}
  Loop(float x, float y);
  glm::vec3 position;
  void draw(glm::mat4 VP);
  void tick();
  float x;
  float y;
private:
  VAO *object;
  VAO *object2;
};

#endif
