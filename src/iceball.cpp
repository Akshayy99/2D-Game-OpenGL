#include "iceball.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Iceball::Iceball(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->zoom = 1;
    this->radius1 = this->zoom*0.2;
    this->radius2 = this->zoom*0.25;
    this->hit = false;
    float n = 360;
    this->downspeed = -0.05;
    this->g = 0.002;
    this->speed = 0.08;
    // float r = 0.10;
    float theta = 2*3.14159/n;

    int numTriangles = 360;

    GLfloat vertex_buffer_data[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;
        vertex_buffer_data[i*9] = 0.0f;
        vertex_buffer_data[i*9+1] = 0.0f;
        vertex_buffer_data[i*9+2] = 2.0f;
        vertex_buffer_data[i*9+3] = ((i%2==0)?this->radius2:this->radius1) * cos(angleBefore);
        vertex_buffer_data[i*9+4] = ((i%2==0)?this->radius2:this->radius1) * sin(angleBefore);
        vertex_buffer_data[i*9+5] = 2.0f;
        vertex_buffer_data[i*9+6] = ((i%2==0)?this->radius2:this->radius1) * cos(angle);
        vertex_buffer_data[i*9+7] = ((i%2==0)?this->radius2:this->radius1) * sin(angle);
        vertex_buffer_data[i*9+8] = 2.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, COLOR_DARKBLUE, GL_FILL);
}

void Iceball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Iceball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Iceball::tick() {
    this->position.x -= this->speed;
    this->position.y -= this->downspeed;
    this->downspeed += this->g;
    // this->position.x += this->speed;

    if(this->position.y == -1)
    {
        this->hit = true;
    }
}
