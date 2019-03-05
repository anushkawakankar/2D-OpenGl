#include "main.h"

#ifndef ICEBALL_H
#define ICEBALL_H


class Iceball {
public:
    Iceball() {}
    Iceball(float x, float y, float pos, double v);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
    void tick(float pos);
    double leftspeed;
    double rightspeed;
    double speed;
    bool active;
private:
    VAO *object;
    VAO *object2;
};

#endif // BALL_H
