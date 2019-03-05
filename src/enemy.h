#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float minHeight, bool isBeam, bool isLine);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bool isLine;
    void tick();
    float radius;
    double speed;
    bool active;
    int colornum;
    bool isBeam;
    float rotation;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
};

#endif
