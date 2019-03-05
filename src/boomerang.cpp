#include "main.h"
#include "boomerang.h"

using namespace std;

Boomerang::Boomerang(float x, float minHeight) {
  this->active = true;
  float diff = 2.0 - minHeight;
  float multiplier = ((float) rand())/(float) RAND_MAX;
  float y = minHeight + diff*multiplier;
  int i;
  this->upspeed = 0.1;
  this->downspeed =0.0;
  this->leftspeed = 0.1;
  this->rightspeed = 0.0;
  this->speed = 0.2;

  this->position = glm::vec3(x, y, 0);

  static GLfloat vertex_buffer_data[] = {
    0.0f,0.5,0.0f,
    0.0f,0.15,0.0f,
    0.7,0.0,0.0,

    0.0,0.5,0.0,
    0.0,0.15,0.0,
    -0.7,0.0,0.0
  };
  this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BROWN, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation *M_PI/180.0f), glm::vec3(0,0,1));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Boomerang::tick(float pos) {
  this->rotation += 5%360;

  if(this->upspeed > 0)
  {
    this->position.y += this->upspeed;
    this->upspeed-=0.002;
  }
  if(this->upspeed <0)
  {
    this->position.y-=this->downspeed;
    this->downspeed += 0.002;
  }
  // this->position.x+=this->speed;
  if(this->position.y <-0.25)
  {
    this->upspeed = 0.1;
    this->downspeed =0;
  }
  if(this->leftspeed >0)
  {
    this->position.x -= this->leftspeed;
    this->leftspeed -=0.002;
  }
  if(this->leftspeed < 0)
  {
    this->position.x += this->rightspeed;
    this->rightspeed += 0.002;
  }
  if(this->rightspeed>0.1)
  {
    this->leftspeed = 0.1;
    this->rightspeed = 0.0;
  }

}
