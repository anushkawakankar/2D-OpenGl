#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, int slab);
    glm::vec3 position;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void tick1(int flag, float pos);
    void tick2(float pos);
    void comeDown();
    double upspeed;
    double acceleration;
    double xspeed;
    double xacceleration;
    double speed;
    double magUpSpeed;
    bool inLoop;
    double downspeed;
    double init;
    double magSpeed;
    bool down;
    bool onGround;
    double magAcc;
    bool coinMag;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
