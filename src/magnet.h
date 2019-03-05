#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet {
public:
  Magnet() {}
  Magnet(float x, float y);
  glm::vec3 position;
  void draw(glm::mat4 VP);
  void tick();
  float x;
  float y;
  float speed;
  bool field;
  int ticks;
  int enter;
  int stay;
  clock_t start_time;
  clock_t duration;
  clock_t end;
  void start();
private:
  VAO *object;
  VAO *object2;
};

#endif
