#include "ball.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Ball::Ball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    // onPlatform = false;
    friction = 0.003;
    moveup = false;
    original_speed = 0.04;
    upspeed = 0;
    downspeed = 0;
    speed = 0.04;
    moveDown = false;
    g = 0.006;
    jumpspeed = 0.1;
    
    int numTriangles = 9;
        
    static const GLfloat vertex_buffer_data[] = {
        -0.5f, 0.5f, 20.0f, // neck : begin
        0.0f, 0.70f, 20.0f,
        0.5f, 0.5f, 20.0f, // neck : end
       
        -0.5f,0.5f,20.0f, // body : begin                     
        0.5f,0.5f,20.0f,
        -0.4f,0.0f,20.0f,

        0.5f,0.5f,20.0f, 
        0.4f,0.0f,20.0f,
        -0.4f,0.0f,20.0f,

        -0.4f,0.0f,20.0f,
        0.4f,0.0f,20.0f,
        -0.5f,-0.5f,20.0f,
       
        0.4f,0.0f,20.0f,
        -0.5f,-0.5f,20.0f,
        0.5f,-0.5f,20.0f, // body : end
       
        -0.5f,-0.5f,20.0f, // legs : begin
        -0.2f,-0.5f,20.0f,
        -0.5f,-0.70f,20.0f,
       
        -0.2f,-0.5f,20.0f,
        -0.5f,-0.70f,20.0f,
        -0.2f,-0.70, 20.0f, 

        0.5f,-0.5f,20.0f,
        0.2f,-0.5f,20.0f,
        0.5f,-0.70f,20.0f,
       
        0.2f,-0.5f,20.0f,
        0.5f,-0.70f,20.0f,
        0.2f,-0.70f, 20.0f // legs  : end
    };
    static const GLfloat vertex_zinda_jetfiresbuffer_data2[] = {
        -0.2f,-0.5f,20.0f,
        0.0f,-0.70f,20.0f,
        0.2f,-0.50f, 20.0f 
    };
    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, COLOR_PLAYER, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_zinda_jetfiresbuffer_data2, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP, bool jet) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->onPlatform = false;
    if(!this->speed)
    {
        this->speed -= (this->speed < 0 ? 1.0 : -1.0) * this->friction; 
    }

    if(this->upspeed > 0)
    {   
        if(this->position.y >= 3.05)
        {
            this->position.y = 3.05;
            this->upspeed = 0;
        }
        else
        {
            this->position.y += upspeed;
            this->upspeed -= this->g;
        }
        if(this->upspeed <= 0)
        {
            this->moveDown = true;
            this->downspeed = 0;
            this->upspeed = 0;
        }
    }
    if(this->moveDown)
    {
        this->position.y -= downspeed;
        this->downspeed += this->g;
        if(this->position.y <= -1.8) 
        {
            this->moveDown = false;
            this->downspeed = 0;
            this->position.y = -1.8;
        }
    }
}
