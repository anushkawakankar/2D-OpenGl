#include "main.h"
#include "magnet.h"

using namespace std;

Magnet::Magnet(float x , float y) {
  this->speed = 0.03;
  this->x = x;
  this->y = y;
  this->position = glm::vec3(x, y, 0);
  this->ticks = 0;
  // this->80 = 80;
  // this->200 = 200;
  this->field = false;
  this->duration= 5*CLOCKS_PER_SEC;


  static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.3, 0.0f,
        0.0f, 0.45, 0.0f,
        0.7, 0.45, 0.0f,

        0.7, 0.45, 0.0f,
        0.7, 0.3, 0.0f,
        0.0f, 0.3, 0.0f,

        0.0f, -0.3, 0.0f,
        0.0f, -0.45, 0.0f,
        0.7, -0.3-0.15, 0.0f,

        0.7, -0.45, 0.0f,
        0.7, -0.3, 0.0f,
        0.0f, -0.3, 0.0f,

        0.7, 0.45, 0.0f,
        0.85, 0.45, 0.0f,
        0.7, -0.45, 0.0f,

        0.7, -0.45, 0.0f,
        0.85, -0.45, 0.0f,
        0.85, 0.45, 0.0f,
    };
    static const GLfloat vertex_buffer_data2[] = {
      0.0f,0.3,0.0f,
      0.0f,0.45,0.0f,
      -0.1,0.45,0.0f,

      0.0f,0.3,0.0f,
      -0.1,0.45,0.0f,
      -0.1,0.3,0.0f,

      0.0f,-0.3,0.0f,
      0.0f,-0.45,0.0f,
      -0.1,-0.45,0.0,

      0.0f,-0.3,0.0f,
      -0.1,-0.45,0.0f,
      -0.1,-0.3,0.0f,
    };
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_MAGRED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_GREY, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);

}

void Magnet::start()
{
    this->position = glm::vec3(this->x, this->y, 0);
    this->ticks=0;
    this->field = true;
    // this->start_time = clock();
}

void Magnet::tick()
{

        // this->end = clock();
        // cout<<(this->end - this->start_time)/CLOCKS_PER_SEC<<endl;
        if(this->ticks < 80)
        {
          // if((this->end - this->start_time)/CLOCKS_PER_SEC >= this->duration)
            this->position.y +=  this->speed;
        }
        else if(this->ticks >= 80 && this->ticks < 280)
          this->field=false;
        else if(this->ticks >= 140 && this->ticks < 360)
        {
            this->field=true;
            this->position.y -=this->speed;
            // this->start_time = clock();
        }
        else if(this->ticks==360)
        {
            this->ticks=0;
        }
        this->ticks++;


}
