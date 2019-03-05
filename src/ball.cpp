#include "ball.h"
#include "main.h"
#include <math.h>
#define _USE_MATH_DEFINES

Ball::Ball(float x, float y, color_t color, int slab) {
    this->position = glm::vec3(x, y, 0);
    this->radius = 0.3;
    float floorHeight=-1.7;
    this->coinMag = false;
    this->magUpSpeed = 0.0;
    this->inLoop=false;
    float n = 360;
    float r = this-> radius;
    float theta = 2*M_PI/n;
    int i;
    this->xspeed = 0.15;
    this->speed = 0.15;
    this->upspeed=0.0;
    this->downspeed = 0.0;
    this->init = 0.15;
    this->down = false;
    this->onGround=true;
    this->acceleration=0.003;
    this->magSpeed = 0.0;
    this->magAcc = 0.0009;
    // this->xspeed=0.1;
    // this->acceleration=0.00;
      GLfloat vertex_buffer_data[360*9];

      for(i=0;i<n;i++)
      {
        float angle1=theta*i;
        float angle2 = angle1+theta;

        vertex_buffer_data[i*9]= 0.0f;
        vertex_buffer_data[i*9+1]= 0.0f;
        vertex_buffer_data[i*9+2]=0.0f;
        vertex_buffer_data[i*9+3]= r*cos(angle1);
        vertex_buffer_data[i*9+4]=r*sin(angle1);
        vertex_buffer_data[i*9+5]=0.0f;
        vertex_buffer_data[i*9+6]=r*cos(angle2);
        vertex_buffer_data[i*9+7]=r*sin(angle2);
        vertex_buffer_data[i*9+8]=0.0f;

      }
      this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->position += speed;
    float floorHeight= -1.7;
    this->onGround = false;
    if(this->upspeed > 0)
    {
      this->position.y += upspeed;
      this->upspeed -= this->acceleration;
      if(this->upspeed <=0)
      {
        this->down = true;
        this->downspeed = 0.0;
      }
      // this->position.x += this->xspeed;
    }
    if(this->down)
    {
      if(this->position.y-this->downspeed > floorHeight)
      {
        this->position.y-=this->downspeed;
      }
      else
      {
        this->position.y = floorHeight;
        this->down = false;
        this->onGround = true;
        this->downspeed=0.0;
        // this->speed=0;
      }
      this->downspeed+=this->acceleration;
      // this->position.x += this->xspeed;
      // this->position.x += this->magSpeed;
      // this->position.y += this->magSpeed;
    }
    // this->xspeed = 0;
    if(this->position.y < -1.0)
    {
      this->xspeed=0.0;
    }

}

void Ball::tick2(float pos) {
  if(pos-this->position.x>0)
  {
    if(pos-this->position.x > 0)
    {
      this->magSpeed+=this->magAcc;
    }
  }
  else if(this->position.x - pos >= 7)
  {
    if(this->position.x - pos >= 7)
    {
      this->magSpeed -= this->magAcc;
    }
  }

}

void Ball::comeDown() {
  float floorHeight = -1.7;
  if(this->position.y-this->downspeed > floorHeight)
  {
    this->position.y-=this->downspeed;
  }
  else
  {
    this->position.y = floorHeight;
    this->down = false;
    this->onGround = true;
    this->downspeed=0.0;
    // this->speed=0;
  }
  this->downspeed+=this->acceleration;
  tick();
}

bounding_box_t Ball::bounding_box() {
  float x = this->position.x;
  float y = this->position.y;
  bounding_box_t bbox = {x,y,0.3,0.4};
  return bbox;
}
