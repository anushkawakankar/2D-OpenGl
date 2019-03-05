#include "main.h"

#ifndef LIVES_H
#define LIVES_H


class Lives {
public:
    Lives() {}
    Lives(float x);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    bool active;
private:
    VAO *object;
};

#endif // BALL_H
