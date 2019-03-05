#include "fireball.h"
// #include "beam.h"
#include "main.h"

Fireball::Fireball(float x, float y) {
  this->active = true;
  this->radius= 0.15;
  this->position = glm::vec3(x, y, 0);

  this->acceleration = 0.001;
  this->downspeed = 0.0;
  this->xspeed = 0.05;
  this->upspeed = 0.02;
  this->speed = 0.02;

      static const GLfloat vertex_buffer_data[]= {
      0.0,0.0,0.0,
      0.0,0.075,0.0,
      4.0,0.075,0.0,

      0.0,0.0,0.0,
      4.0,0.0,0.0,
      4.0,0.075,0.0,

      0.0,0.0,0.0,
      0.0,-0.075,0.0,
      4.0,-0.075,0.0,

      0.0,0.0,0.0,
      4.0,0.0,0.0,
      4.0,-0.075,0.0
    };
    static const GLfloat vertex_buffer_data2[]= {
      0.0,0.0,0.0,
      0.0,0.025,0.0,
      4.0,0.025,0.0,

      0.0,0.0,0.0,
      4.0,0.0,0.0,
      4.0,0.025,0.0,

      0.0,0.0,0.0,
      0.0,-0.025,0.0,
      4.0,-0.025,0.0,

      0.0,0.0,0.0,
      4.0,0.0,0.0,
      4.0,-0.025,0.0
    };
  this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
  this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_ORANGE, GL_FILL);


}

void Fireball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);

}

void Fireball::tick() {
  this->position.y+=this->speed;
  if(this->position.y>=3)
    this->speed = -this->speed;
  if(this->position.y <= -1.0)
    this->speed =-this->speed;
}
