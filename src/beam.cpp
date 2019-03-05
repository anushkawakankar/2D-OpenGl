#include "beam.h"
#include "main.h"

Beam::Beam(float x, float minHeight) {
  this->radius=0.15;
  float diff = 2.0 - minHeight;
  float multiplier = ((float) rand())/(float) RAND_MAX;
  float y = minHeight + diff*multiplier;

  this->position = glm::vec3(x, y, 0);
  this->speed = 0.02;

  static const GLfloat vertex_buffer_data[]= {
    0.0,0.25,0.0,
    0.0,0.1,0.0,
    0.5,0.25,0.0,

    0.0,0.1,0.0,
    0.5,0.1,0.0,
    0.5,0.25,0.0,

    0.0,-0.1,0.0,
    0.0,-0.25,0.0,
    0.5,-0.1,0.0,

    0.0,-0.25,0.0,
    0.5,-0.1,0.0,
    0.5,-0.25,0.0,
  };
  static const GLfloat vertex_buffer_data2[]= {
    0.0,0.25,0.0,
    -0.15,0.25,0.0,
    -0.15,-0.25,0.0,

    0.0,0.25,0.0,
    -0.15,-0.25,0.0,
    0.0,-0.25,0.0,
  };
  this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
  this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_GREY, GL_FILL);

}

void Beam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);

}

void Beam::tick() {
  this->position.y+=this->speed;
  if(this->position.y>=3)
    this->speed = -this->speed;
  if(this->position.y <= -1.0)
    this->speed =-this->speed;
}
