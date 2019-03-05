#include "main.h"
#include "iceball.h"

using namespace std;

Iceball::Iceball(float x,float y, float pos, double v) {
  this->active = true;
  this->position = glm::vec3(x+0.2, y+0.65, 0);
  this->speed = v;
  this->leftspeed = v;
  this->rightspeed =0.0;
  float len;
  if(x<pos)
    len = 2.0;
  else
    len = -2.0;
// cout<<"ball at "<<pos<<" dragon at "<<x<<" len= "<<len<<endl;
  static const GLfloat vertex_buffer_data[]= {
    0.0,0.0,0.0,
    0.0,0.085,0.0,
    len,0.085,0.0,

    0.0,0.0,0.0,
    len,0.0,0.0,
    len,0.085,0.0,

    0.0,0.0,0.0,
    0.0,-0.085,0.0,
    len,-0.085,0.0,

    0.0,0.0,0.0,
    len,0.0,0.0,
    len,-0.085,0.0
  };
static const GLfloat vertex_buffer_data2[]= {
    0.0,0.0,0.0,
    0.0,0.025,0.0,
    len,0.025,0.0,

    0.0,0.0,0.0,
    len,0.0,0.0,
    len,0.025,0.0,

    0.0,0.0,0.0,
    0.0,-0.025,0.0,
    len,-0.025,0.0,

    0.0,0.0,0.0,
    len,0.0,0.0,
    len,-0.025,0.0
  };
this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, COLOR_LSTEELBLUE, GL_FILL);
this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_STEELBLUE, GL_FILL);

}

void Iceball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
  }

void Iceball::tick(float pos) {
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
