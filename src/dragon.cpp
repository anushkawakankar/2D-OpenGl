#include "main.h"
#include "dragon.h"

// using namespace std;

Dragon::Dragon(float x, float y, double v) {
  this->position = glm::vec3(x, y, 0);
  this->speed = v;
  this->leftspeed = v;
  this->rightspeed =0.0;
  static const GLfloat vertex_buffer_data[] = {
        -0.35,0.0,0.0,
        -0.35,0.5,0.0,
        0.35,0.0,0.0,

        0.35,0.0,0.0,
        -0.35,0.5,0.0,
        0.35,0.5,0.0,

        -0.25,0.8,0.0,
        -0.25,1.0,0.0,
        -0.08,0.8,0.0,

        0.25,0.8,0.0,
        0.08,0.8,0.0,
        0.25,1.0,0.0,
    };
    static const GLfloat vertex_buffer_data2[] = {
      -0.25,0.5,0.0,
      -0.25,0.8,0.0,
      0.25,0.8,0.0,

      0.25,0.8,0.0,
      0.25,0.5,0.0,
      -0.25,0.5,0.0
    };
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_STEELBLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_LSTEELBLUE, GL_FILL);

}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Dragon::tick( float pos) {
  if(pos<this->position.x)
  {
    this->leftspeed = this->speed;
    this->rightspeed = 0.0;
  }
  if(pos - this-> position.x >= 3.5)
  {
    this->rightspeed = this->speed;
    this->leftspeed = 0.0;
  }
  this->position.x += this->rightspeed;
  this->position.x -= this->leftspeed;
}
