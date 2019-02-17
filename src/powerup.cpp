#include "powerup.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;

Powerup::Powerup(float x, float y, int type) {
    this->position = glm::vec3(x, y, 0);
    this->radius = (type) ? 0.30 : 0.20;
    this->far = false;
    this->speedx = (type) ? 0.04 : 0.06;
    this->scored = false;
    // this->speedy = 0.07;
    // this->g = -0.008;
    float n = 360;
    // float r = 0.30;
    float theta = 2*3.14159/n;

    int numTriangles = 360;

    GLfloat vertex_buffer_data[numTriangles*9];

    int i;
    for(i=0; i<numTriangles; i++)
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

    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, (type) ? COLOR_BLUE : COLOR_RED, GL_FILL);
}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Powerup::tick() {
    this->far = false;
    this->position.x -= speedx;
    this->position.y += this->speedy;
    this->speedy += this->g;
    if(this->position.y >= 0.5)
    {
        // if(this->speedy < 0) this->g = -0.01;
        this->g = -0.01;
    }
    else if(this->position.y < 0.5)
    {
        // if(this->speedy < 0) this->g = 0.01;
        this->g = 0.01;
    }
    if(this->position.y >= 2.2)
    {
        this->position.y = 2.199;
        this->speedy = 0;
    }
    if(this->position.y <= -1.0)
    {
        this->speedy = -this->speedy;
        this->position.y = -0.99;
    }

}
