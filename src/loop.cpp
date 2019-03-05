#include "main.h"
#include "loop.h"

using namespace std;

Loop::Loop(float x,float y) {
  this->x = x;
  this->y = y;
  this->position = glm::vec3(x, y, 0);
  static const GLfloat vertex_buffer_data[] = {
    0.0,0.0,0.0,
    0.75,0.0,0.0,
    0.75,1.25,0.0,

    0.0,0.0,0.0,
    0.0,1.25,0.0,
    0.75,1.25,0.0,

    0.0,1.25,0.0,
    0.0,2.0,0.0,
    4.5,2.0,0.0,

    0.0,1.25,0.0,
    4.5,1.25,0.0,
    4.5,2.0,0.0,

    4.5,1.25,0.0,
    3.75,1.25,0.0,
    4.5,0.0,0.0,

    3.75,1.25,0.0,
    3.75,0.0,0.0,
    4.5,0.0,0.0
  };
  this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_LIGHTGREY, GL_FILL);
}

void Loop::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}
