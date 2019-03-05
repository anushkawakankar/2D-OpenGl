#include "main.h"

#ifndef LINE_H
#define LINE_H


class Line {
public:
    Line() {}
    Line(float x, float minHeight);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    bool active;
    double speed;
    float rotation;
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
};

#endif
