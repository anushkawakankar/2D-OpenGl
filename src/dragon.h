#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, double v);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick(float pos);
    float radius;
    double speed;
    double leftspeed;
    double rightspeed;
    float rotation;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
    VAO *object2;
};

#endif
