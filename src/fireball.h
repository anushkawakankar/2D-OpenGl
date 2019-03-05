#include "main.h"

#ifndef FIREBALL_H
#define FIREBALL_H


class Fireball {
public:
    Fireball() {}
    Fireball(float x, float y);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    // void set_position(float x, float y);
    void tick();
    double acceleration;
    double xspeed;
    double downspeed;
    float upspeed;
    float speed;
    bool active;
private:
    VAO *object;
    VAO *object2;
};

#endif // BALL_H
