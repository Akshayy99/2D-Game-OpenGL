#include "waterballoon.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Waterballoon::Waterballoon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->radius = 0.18;
    this->hit = false;
    float n = 360;
    this->downspeed = 0;
    this->g = 0.001;
    this->speed = 0.06;
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
        vertex_buffer_data[i*9+2] = 0.0f;
        vertex_buffer_data[i*9+3] = this->radius * cos(angleBefore);
        vertex_buffer_data[i*9+4] = this->radius * sin(angleBefore);
        vertex_buffer_data[i*9+5] = 0.0f;
        vertex_buffer_data[i*9+6] = this->radius * cos(angle);
        vertex_buffer_data[i*9+7] = this->radius * sin(angle);
        vertex_buffer_data[i*9+8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, COLOR_SEAGREEN, GL_FILL);
}

void Waterballoon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Waterballoon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Waterballoon::tick() {
    this->position.y -= this->downspeed;
    this->downspeed += this->g;
    this->position.x += this->speed;

    // if(this->position.y == -1)
    // {
    //     this->hit = true;
    // }
}
