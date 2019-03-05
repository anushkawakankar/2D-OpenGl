#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float minHeight);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick(float pos);
    float apex;
    float flyTime;
    float radius;
    float leftspeed;
    float rightspeed;
    float downspeed;
    float upspeed;
    double speed;
    bool active;
    float rotation;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
    VAO *object2;
};

#endif
