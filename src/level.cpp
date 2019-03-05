#include "main.h"
#include "level.h"

Level::Level(float x) {
  this->active = false;
  this->position = glm::vec3(x,3,0);
  static const GLfloat vertex_buffer_data[]= {
    0.0,0.3,0.0,
    0.3,0.0,0.0,
    -0.3,0.0,0.0,

    0.0,-0.1,0.0,
    0.3,0.2,0.0,
    -0.3,0.2,0.0


  };

  this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Level::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
  }
