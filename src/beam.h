#include "main.h"

#ifndef BEAM_H
#define BEAM_H


class Beam {
public:
    Beam() {}
    Beam(float x, float minHeight);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    double speed;
    float rotation;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
    VAO *object2;
};

#endif
