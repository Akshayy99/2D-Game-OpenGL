#include "jetfire.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Jetfire::Jetfire(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->bahar = false;
    this->downspeed = 0.04;
    this->g = 0.002;
    zoom = 1.5;
    
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 10.0f,
        zoom*0.05f, 0.0f, 10.0f,
        zoom*0.05f, zoom*0.05f, 10.0f,

        0.0f, 0.0f, 10.0f,
        0.0f, zoom*0.05f, 10.0f, 
        zoom*0.05f, zoom*0.05f, 10.0f
    };
    static const GLfloat vertex_buffer_data2[] = {
        0.0f, -zoom*0.05f+0.0f, 10.0f,
        zoom*0.05f, -zoom*0.05f+0.0f, 10.0f,
        zoom*0.05f, -zoom*0.05f+zoom*0.05f, 10.0f,

        0.0f, -zoom*0.05f+0.0f, 10.0f,
        0.0f, -zoom*0.05f+zoom*0.05f, 10.0f, 
        zoom*0.05f, -zoom*0.05f+zoom*0.05f, 10.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
}

void Jetfire::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Jetfire::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Jetfire::tick() {
    this->position.y -= this->downspeed;
    this->downspeed += this->g;
    // if(this->position.y <= -4)
        // this->bahar = true;

}
