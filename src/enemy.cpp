#include "enemy.h"
#include "main.h"


Enemy::Enemy(float x, float minHeight, bool isBeam, bool isLine){
  this->active = true;
  this->radius = 0.2;
  float diff = 2.0 - minHeight;
  float multiplier = ((float) rand())/(float) RAND_MAX;
  float y = minHeight + diff*multiplier;
  int i;

  this->position = glm::vec3(x, y, 0);
  float diff2 = 0.02;
  float multiplier2 = ((float) rand()) / (float) RAND_MAX;
  if(level == 1)
    this->speed = 0.005 + diff2*multiplier2;
  if(level == 2)
    this->speed = 0.007 + diff2*multiplier2;
  if(level == 3)
    this->speed = 0.009 + diff2*multiplier2;

  this->colornum = rand()%3;
  // color_t colors = {COLOR_PINK, COLOR_LIGHTGREEN, COLOR_LIGHTBLUE};

  if(!this->isBeam && !this->isLine)
  {
    GLfloat vertex_buffer_data[360*9];
    // float r = this->radius;
    float n = 360;
    float r = this-> radius;
    float theta = 2*M_PI/n;
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
    // this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, colors[this->colornum], GL_FILL);
    if(colornum==0)
    {
      this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_PINK, GL_FILL);
    }
    if(colornum==1)
    {
      this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_LIGHTBLUE, GL_FILL);
    }
    if(colornum==2)
    {
      this->object = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data, COLOR_LIGHTGREEN, GL_FILL);
    }
  }
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->block_object);

}

void Enemy::tick() {
    this->position.x += this->speed;
}
