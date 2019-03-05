#include "main.h"

#ifndef POWERUPS_H
#define POWERUPS_H


class Powerups {
public:
    Powerups() {}
    Powerups(float x, float minHeight, bool incSpeed, bool coinMagnet);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    double speed;
    double upspeed;
    double downspeed;
    double acc;
    bool active;
    float rotation;
    bool incSpeed;
    bool coinMagnet;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
    VAO *object2;
};

#endif
