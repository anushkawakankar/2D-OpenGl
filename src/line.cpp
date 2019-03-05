#include "line.h"
#include "main.h"

Line::Line(float x, float minHeight) {
  this->radius=0.15;
  this->active = true;
  float diff = 2.0 - minHeight;
  float multiplier = ((float) rand())/(float) RAND_MAX;
  float y = minHeight + diff*multiplier;

  this->position = glm::vec3(x, y, 0);
  float diff2 = 0.02;
  float multiplier2 = ((float) rand()) / (float) RAND_MAX;
  this->speed = 0.02 + diff2*multiplier2;

  static const GLfloat block_vertex_buffer_data[] = {
      0.0f,0.0f,0.0f,
      0.5,0.0f,0.0f,
      0.0f,0.1,0.0f,

      0.5,0.0f,0.0f,
      0.0f,0.1,0.0f,
      0.5,0.1,0.0f

  };
  this->object = create3DObject(GL_TRIANGLES, 2*3, block_vertex_buffer_data, COLOR_ORANGE, GL_FILL);
}

void Line::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->block_object);

}

void Line::tick() {
    this->position.x += this->speed;
}
