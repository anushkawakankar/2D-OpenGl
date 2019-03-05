#include "main.h"
#include "timer.h"
#include "ball.h"
#include "beam.h"
#include "ground.h"
#include "line.h"
#include "enemy.h"
#include "loop.h"
#include "dragon.h"
#include "magnet.h"
#include "powerups.h"
#include "fireball.h"
#include "boomerang.h"
#include "lives.h"
#include <math.h>
#include <unistd.h>
#include "iceball.h"
#include "level.h"
#include "numbers.h"
// #include <ctime>

#define _USE_MATH_DEFINES

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball;
Enemy enemies[1000];
Ground ground;
Line line[750];
Fireball fireball[7];
Magnet magnet;
Beam beam[7];
Powerups powerups[50];
Loop loop[5];
Dragon dragon[2];
Boomerang boomerang[3];
Iceball ice[2];
Lives lives[3];
Level levels[3];
Numbers numbers[3];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float floorHeight = -1.7;
int i;
int score = 0;
int level = 1;
int life=3;
float start_x,start_x2;
int life_flag;
clock_t beam_start, beam_end,start_mag,start_speed,curr,ice_end;

Timer t60(1.0 / 60);

void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 target (0, 0, 0);
    glm::vec3 up (0, 1, 0);
    Matrices.view = glm::lookAt( eye, target, up );
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;

    ground.draw(VP);
    levels[0].active = true;
    for(i=0;i<3;i++)
    {
      if(levels[i].active)
      {
        levels[i].draw(VP);
        // cout<<" level "<<i<<" active"<<endl;
      }
    }
    ball.draw(VP);
    for(i=0; i<1000; i++)
    {
        if(enemies[i].active)
        {
          enemies[i].draw(VP);
        }
    }
    for(i=0;i<750;i++)
    {
      if(line[i].active)
      {
        line[i].draw(VP);
      }
    }
    magnet.draw(VP);
    for(i=0;i<7;i++)
    {
      beam[i].draw(VP);
      if(fireball[i].active)
      {
        fireball[i].draw(VP);
      }
    }
    for(i=0;i<50;i++)
    {
      if(powerups[i].active)
      {
        powerups[i].draw(VP);
      }
    }
    for(i=0;i<5;i++)
    {
      loop[i].draw(VP);
    }
    for(i=0;i<2;i++)
    {
      dragon[i].draw(VP);
      if(ice[i].active)
      {
        // cout<<"drawing at "<<ice[i].position.x<<" "<<ice[i].position.y<<endl;
        ice[i] = Iceball(dragon[i].position.x, dragon[i].position.y, ball.position.x, dragon[i].speed);
        ice[i].draw(VP);
      }
    }
    for(i=0;i<3;i++)
    {
      if(boomerang[i].active)
        boomerang[i].draw(VP);
    }
    for(i=0;i<3;i++)
    {
      if(lives[i].active)
        lives[i].draw(VP);
    }

    int temp=score;
    int units = temp%10;
    temp/=10;
    numbers[2] = Numbers(-1,3.8);
    numbers[2].draw(VP,units);
    int tens = temp%10;
    temp/=10;
    numbers[1] = Numbers(-1.5,3.8);
    numbers[1].draw(VP,tens);
    int hundreds = temp%10;
    numbers[0] = Numbers(-2,3.8);
    numbers[0].draw(VP,hundreds);
    // numbers[0] = Numbers(-2,3.8);
    // numbers[0].draw(VP,5);



}

void tick_input(GLFWwindow *window) {
  // printf("entered fumc\n");
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);


    reset_screen();

    if(a)
    {
      magnet.position.x +=ball.speed;
      for(i=0;i<1000;i++)
      {
        enemies[i].position.x+=ball.speed;
      }
      for(i=0;i<750;i++)
      {
        line[i].position.x+=ball.speed;
      }
      for(i=0;i<7;i++)
      {
        beam[i].position.x+=ball.speed;
        fireball[i].position.x+=ball.speed;
      }
      for(i=0;i<50;i++)
      {
        powerups[i].position.x+=ball.speed;
      }
      for(i=0;i<5;i++)
      {
        loop[i].position.x += ball.speed;
      }
      for(i=0;i<2;i++)
      {
        dragon[i].position.x += ball.speed;
        ice[i].position.x += ball.speed;
      }
      for(i=0;i<3;i++)
      {
        boomerang[i].position.x += ball.speed;
      }
      if(ball.position.y > -1.0)
      {
        // cout<<ball.position.y<<endl;
        // while(ball.position.y > -1.0)
        {
          // ball.position.y -=ball.downspeed;

          magnet.position.x+=ball.xspeed;
          for(i=0;i<1000;i++)
          {
            enemies[i].position.x+=ball.xspeed;
          }
          for(i=0;i<750;i++)
          {
            line[i].position.x +=ball.xspeed;
            }
            for(i=0;i<7;i++)
            {
              beam[i].position.x+=ball.xspeed;
              fireball[i].position.x+=ball.xspeed;
            }
            for(i=0;i<50;i++)
            {
              powerups[i].position.x+=ball.xspeed;

            }
            for(i=0;i<5;i++)
            {
              loop[i].position.x += ball.xspeed;

            }
            for(i=0;i<2;i++)
            {
              dragon[i].position.x += ball.xspeed;
              ice[i].position.x == ball.xspeed;
            }
            for(i=0;i<3;i++)
            {
              boomerang[i].position.x += ball.xspeed;
            }
          }

      }
    }



    if(d)
    {
      if(ball.inLoop)
      {
        if(!(ball.position.y>2.25 && ball.position.y<3))
          d=0;
      }
      magnet.position.x -=ball.speed;
      for(i=0;i<1000;i++)
      {
        enemies[i].position.x-=ball.speed;
      }
      for(i=0;i<750;i++)
      {
        line[i].position.x-=ball.speed;
      }
      for(i=0;i<7;i++)
      {
        beam[i].position.x-=ball.speed;
        fireball[i].position.x-=ball.speed;
      }
      for(i=0;i<50;i++)
      {
        powerups[i].position.x-=ball.speed;
      }
      for(i=0;i<5;i++)
      {
        loop[i].position.x -= ball.speed;
      }
      for(i=0;i<2;i++)
      {
        dragon[i].position.x -= ball.speed;
        ice[i].position.x -= ball.speed;
      }
      for(i=0;i<3;i++)
      {
        boomerang[i].position.x -= ball.speed;
      }
      if(ball.position.y > -1.0)
      {
        {
          magnet.position.x-=ball.xspeed;
          for(i=0;i<1000;i++)
          {
            enemies[i].position.x-=ball.xspeed;
          }
          for(i=0;i<750;i++)
          {
            line[i].position.x-=ball.xspeed;
          }
            for(i=0;i<7;i++)
            {
              beam[i].position.x-=ball.xspeed;
              fireball[i].position.x-=ball.xspeed;
            }
            for(i=0;i<50;i++)
            {
              powerups[i].position.x-=ball.xspeed;
            }
            for(i=0;i<5;i++)
            {
              loop[i].position.x -= ball.xspeed;
            }
            for(i=0;i<2;i++)
            {
              dragon[i].position.x -= ball.xspeed;
              ice[i].position.x -= ball.xspeed;
            }
            for(i=0;i<3;i++)
            {
              boomerang[i].position.x -= ball.xspeed;
            }
          }
      }
    }

    // movelol();
    reset_screen();
    if(space)
    {
      if(ball.upspeed>0 || ball.down)
      {
        ball.upspeed = 0.1;
        return;
      }
      ball.upspeed = ball.init;
    }

}

void tick_elements() {
    camera_rotation_angle = 32*M_PI ;
    magnet.tick();
    // cout<<ball.coinMag<<endl;

    if(magnet.field && !ball.inLoop && abs(magnet.position.x - ball.position.x)<5 && magnet.position.x>ball.position.x)
    {
      // ball.down=true;
      // ball.onGround=false;
      ball.tick2(magnet.position.x);
      if(ball.position.y < magnet.position.y)
      {
        ball.position.y += ball.magSpeed;
        // cout<<ball.position.y<<endl;

      }
      // if(ball.position.y>4)
      //   ball.comeDown();

      // if(ball.position.y > -1.7)
      //   ball.comeDown();
      if(ball.position.y > -1.0)// && (ball.position.x - magnet.position.x) <= 7.0)
      {
        magnet.position.x-=ball.magSpeed;
        for(i=0;i<1000;i++)
          enemies[i].position.x-=ball.magSpeed;
        for(i=0;i<750;i++)
          line[i].position.x-=ball.magSpeed;
        for(i=0;i<7;i++)
        {
          beam[i].position.x-=ball.magSpeed;
          fireball[i].position.x-=ball.magSpeed;
        }
        for(i=0;i<50;i++)
        {
          powerups[i].position.x-=ball.magSpeed;
        }
        for(i=0;i<2;i++)
        {
          dragon[i].position.x -= ball.magSpeed;
          ice[i].position.x -= ball.magSpeed;
        }
        for(i=0;i<3;i++)
        {
          boomerang[i].position.x -= ball.magSpeed;
        }
      }
    }
    else
    {
      // cout<<ball.position.y<<endl;
      if(ball.position.y!=-2)
        ball.comeDown();
      ball.magSpeed=0.0;
    }
    ball.tick();
    for(i=0;i<1000;i++)
    {
      enemies[i].tick();
    }
    for(i=0;i<750;i++)
    {
      line[i].tick();
    }
    for(i=0;i<7;i++)
    {
      beam[i].tick();
      fireball[i].tick();
    }
    for(i=0;i<50;i++)
    {
      powerups[i].tick();
    }
    for(i=0;i<2;i++)
    {
      dragon[i].tick(ball.position.x);
      ice[i].tick(ball.position.x);
    }
    for(i=0;i<3;i++)
    {
      boomerang[i].tick(35*(i+1));
    }

    for(i=0;i<1000;i++)
    {
      curr = clock();
      if((curr - start_mag)/CLOCKS_PER_SEC > 3)
      {
          if(abs(enemies[i].position.x - ball.position.x) < 0.002 )
            {
              if(!enemies[i].isBeam && !enemies[i].isLine)
              {
                enemies[i].active = false;
                score += 10*(enemies[i].colornum+1);
              }
            }
        }
        // else
        {
            if(enemies[i].active && collision(i))
            {
              if(!enemies[i].isBeam && !enemies[i].isLine)
              {
                if(score>200&& score <400)
                {
                  level = 2;
                  levels[1].active=true;
                }
                if(score >= 400)
                {
                  level = 3;
                  levels[2].active=true;
                }
                if(score >= 700)
                {
                  printf("YOU WIN!!\n");
                  exit(0);
                }
                enemies[i].active = false;
                score += 5*(enemies[i].colornum+1);
                continue;
              }
            }
          }
      }
      int flag=0;
      for(i=0;i<750;i++)
      {
        if(detect_line_collision(i) && flag==0 &&  line[i].active)
        {
            line[i].active=false;
            score-=5;
        }
      }
      for(i=0;i<7;i++)
      {
        if(detect_beam_collision(i) && fireball[i].active)
        {
          fireball[i].active=false;
          score -= 20;
        }
      }

      for(i=0;i<50;i++)
      {
        if(powerups[i].active && detect_powerups_collision(i))
        {
          powerups[i].active = false;
          if(powerups[i].coinMagnet)
          {
            ball.coinMag = true;
            start_x2=ball.position.x;
            start_mag = clock();
          }
          else if(powerups[i].incSpeed)
          {
            start_x = ball.position.x;
            ball.speed = 0.3;
            start_speed = clock();
          }
        }
      }

      for(i=0;i<5;i++)
      {
        if(detect_loop(i))
        {
          ball.inLoop = true;
        }
      }
      for(i=0;i<2;i++)
      {
        if(detect_dragon(i))
        {
          printf("YOU TOUCHED A DRAGON!! CERTAIN DEATH TO YOU!!!!\n");
          // exit(0);
        }

      }

      for(i=0;i<2;i++)
      {
        if(detect_ice(i) && ice[i].active)
        {
          ice[i].active=false;
          life--;
          lives[life].active=false;
        }
      }
      for(i=0;i<3;i++)
      {
        if(detect_boom(i) && boomerang[i].active)
        {
          boomerang[i].active = false;
          score -= 20;
        }
      }
}

void initGL(GLFWwindow *window, int width, int height) {

    for(i=0;i<5;i++)
    {
      loop[i] = Loop((i+1)*50, 1);
    }
    ball       = Ball(0, floorHeight, COLOR_RED,0);
    ground      = Ground(floorHeight-0.3, -4.0);
    for(i=0; i<1000; i++)
    {
        enemies[i] = Enemy(-1.0+(i*0.7), floorHeight + 2*ball.radius + 0.6, false,false);
    }
    for(i=0;i<750;i++)
    {
      line[i] = Line(-1.0+(i*1.5),floorHeight+2*ball.radius + 0.5);
    }

    magnet = Magnet(30,2.0);
    // beam = Beam(40,-1);
    // fireball = Fireball(beam.position.x, beam.position.y);
    for(i=0;i<7;i++)
    {
      beam[i] = Beam(20*(i+1),-1);
      fireball[i] = Fireball(beam[i].position.x, beam[i].position.y);
    }


    for(i=0;i<50;i++)
    {
      if(i%2==0)
        powerups[i] = Powerups(15*(i+1),floorHeight+2*ball.radius+0.5,true,false);
      else
        powerups[i] = Powerups(15*(i+1),floorHeight+2*ball.radius+0.5,false,true);
    }

    // dragon[0] = Dragon(10,-1.9,0.075);
    dragon[0]=Dragon(50,-1.9,0.075);
    dragon[1] = Dragon(300,-1.9,0.1);
    // boomerang[0] = Boomerang(1,1.5);


    // for(i=0;i<2;i++)
    // {
    //   ice[i] = Iceball(dragon[i].position.x, dragon[i].position.y, ball.position.x, dragon[i].speed);
    //   // ice[i] = Iceball(-1,1);
    //   // ice2[i] = Iceball(dragon[1].position.x, dragon[1].position.y);
    // }
    for(i=0;i<3;i++)
    {
      boomerang[i] = Boomerang(35*(i+1),1.5);
    }

    for(i=0;i<3;i++)
    {
      lives[i] = Lives(-(i*0.5)-2.5);
    }

    for(i=0;i<3;i++)
    {
      levels[i] = Level(-(i*0.5)-2.5);
    }





    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    printf("%f, %f\n",ball.position.x, ball.position.y);

    reshapeWindow (window, width, height);
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));

    int width  = 800;
    int height = 800;
    int tickcount= 360;
    int gap = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
      beam_start = clock();
      // cout<<(beam_start-beam_end)/CLOCKS_PER_SEC<<endl;
      for(i=0;i<7;i++)
      {
        if((beam_start-beam_end)/CLOCKS_PER_SEC >= 5)
        {
          // printf("%lld\n",(beam_start-beam_end)/CLOCKS_PER_SEC);
          // cout<<(beam_start-beam_end)/CLOCKS_PER_SEC<<endl;
          fireball[i].active = true;
        }
      }
      for(i=0;i<2;i++)
      {
        if((beam_start-ice_end)/CLOCKS_PER_SEC >= 1)
        {
          ice[i].active=true;
        }
      }
      curr = clock();
      if((curr - start_mag)/CLOCKS_PER_SEC >= 3 || !ball.coinMag)
      {
        ball.coinMag = false;
      }
      if((curr-start_speed)/CLOCKS_PER_SEC >=3)
      {
        ball.speed = 0.15;
      }


        // Process timers

        if (t60.processTick()) {
            tickcount++;
            if(tickcount == gap + 360)
            {
                tickcount=0;
                magnet.start();
            }
            if(abs(ball.position.x - start_x) > 10 )
            {
              ball.speed = 0.15;
              // ball.incSpeed=false;
            }
            if(abs(ball.position.x - start_x2) > 2 )
            {
              ball.coinMag = false;
            }
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            if(life <= 0)
            {
              printf("YOU DIED!\n");
              exit(0);
            }

            char titleString[64];
            sprintf(titleString, "Score: %d\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tLevel: %d" , score,level);
            glfwSetWindowTitle(window,titleString);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

// bool detect_collision(bounding_box_t a, bounding_box_t b) {
//     return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
//            (abs(a.y - b.y) * 2 < (a.height + b.height));
// }

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 2500.0f);
}

bool collision(int i)
{
  // if(ball.upspeed> 0)
  //   return false;
  if(abs(ball.position.y - enemies[i].position.y) < 0.5 && abs(ball.position.x - enemies[i].position.x) < 0.5)
  {
    // printf("collided\n");
    return true;
  }
  return false;
}

bool detect_line_collision(int i)
{
  if(abs(ball.position.y - line[i].position.y)<0.1 && abs(ball.position.x - line[i].position.x) <= 0.4)
  {
    // printf("collided\n");
    // line[i].active=false;
    return true;
  }
  return false;

}

bool detect_beam_collision(int i)
{
  if(abs(ball.position.y - fireball[i].position.y) <= 0.1 && abs(ball.position.x - fireball[i].position.x) <= 6.0 && ball.position.x>= fireball[i].position.x)
  {
    beam_end= clock();
    // printf("collided %d\n",fireball.active);
    return true;
  }
  return false;
}

bool detect_ice(int i)
{
  if(abs(ball.position.y - ice[i].position.y)<=0.1 && abs(ball.position.x - ice[i].position.x) <= 2.0 && ball.position.x >= ice[i].position.x)
  {
    ice_end = clock();
    return true;
  }
  return false;
}

bool detect_powerups_collision(int i)
{
  if(abs(ball.position.y - powerups[i].position.y) < 0.5 && abs(ball.position.x - powerups[i].position.x) < 0.5)
  {
    return true;
  }
  return false;
}

bool detect_loop(int i)
{
  if(loop[i].position.x < ball.position.x && loop[i].position.x+0.75 > ball.position.x && loop[i].position.y < ball.position.y && ball.position.y < loop[i].position.y+2)
  {
    return true;
  }
  return false;
}

bool detect_dragon(int i)
{
  if(abs(ball.position.x - dragon[i].position.x)<0.4 && abs(ball.position.y - dragon[i].position.y)<1)
  {
    return true;
  }
  return false;
}
bool detect_boom(int i)
{
  if(abs(ball.position.x - boomerang[i].position.x)<0.4 && abs(ball.position.y - boomerang[i].position.y)<1)
    return true;
  return false;
}
