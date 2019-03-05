#include "main.h"

#ifndef LEVEL_H
#define LEVEL_H


class Level {
public:
    Level() {}
    Level(float x);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    bool active;
private:
    VAO *object;
};

#endif // BALL_H
