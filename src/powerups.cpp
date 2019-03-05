#include "main.h"
#include "powerups.h"

Powerups::Powerups(float x, float minHeight, bool incSpeed, bool coinMagnet) {
  this->active = true;
  this->radius = 0.2;
  this->incSpeed = incSpeed;
  this->coinMagnet = coinMagnet;
  float diff = 2.0 - minHeight;
  float multiplier = ((float) rand())/(float) RAND_MAX;
  float y = minHeight + diff*multiplier;
  int i;

  this->position = glm::vec3(x, y, 0);
  this->speed = -0.1;
  this->acc = 0.003;
  this->upspeed = 0.1;
  this->downspeed =0.0;

  GLfloat vertex_buffer_data[360*9];
  GLfloat vertex_buffer_data2[360*9];
  float n = 360;
  float r = this-> radius;
  float theta = 2*M_PI/n;
  float r2 = r/2;
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
  for(i=0;i<n;i++)
  {
    float angle1=theta*i;
    float angle2 = angle1+theta;

    vertex_buffer_data2[i*9]= 0.0f;
    vertex_buffer_data2[i*9+1]= 0.0f;
    vertex_buffer_data2[i*9+2]=0.0f;
    vertex_buffer_data2[i*9+3]= r2*cos(angle1);
    vertex_buffer_data2[i*9+4]=r2*sin(angle1);
    vertex_buffer_data2[i*9+5]=0.0f;
    vertex_buffer_data2[i*9+6]=r2*cos(angle2);
    vertex_buffer_data2[i*9+7]=r2*sin(angle2);
    vertex_buffer_data2[i*9+8]=0.0f;
  }
  if(incSpeed)
  {
    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_FORESTGREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data2, COLOR_MEDIUMGREEN, GL_FILL);
  }
  if(coinMagnet)
  {
    this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data2, COLOR_LIGHTGOLD, GL_FILL);
  }
}

void Powerups::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);

  }

  void Powerups::tick() {
    if(this->upspeed > 0)
    {
      this->position.y += upspeed;
      upspeed-=acc;
    }
    if(this->upspeed <0)
    {
      this->position.y-=this->downspeed;
      this->downspeed += this->acc;
    }
    this->position.x+=this->speed;
    if(this->position.y <-1.7)
    {
      this->upspeed = 0.1;
      this->downspeed =0;
    }


  }
