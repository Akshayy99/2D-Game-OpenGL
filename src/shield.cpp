#include "shield.h"
#include "main.h"
#include<bits/stdc++.h>
using namespace std;

Shield::Shield(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->radius1 = 1.2;
    this->radius2 = 1.5;
    this->rotate = glm::rotate((float) (105 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->speedx = 0.04;
    this->scored = false;
    float n = 360;
    float theta = 2*3.14159/n;
    int numTriangles = 150;
    GLfloat vertex_buffer_data1[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*9] = 0.0f;
        vertex_buffer_data1[i*9+1] = 0.0f;
        vertex_buffer_data1[i*9+2] = -11.0f;
        vertex_buffer_data1[i*9+3] = this->radius1 * cos(angleBefore);
        vertex_buffer_data1[i*9+4] = this->radius1 * sin(angleBefore);
        vertex_buffer_data1[i*9+5] = -11.0f;
        vertex_buffer_data1[i*9+6] = this->radius1 * cos(angle);
        vertex_buffer_data1[i*9+7] = this->radius1 * sin(angle);
        vertex_buffer_data1[i*9+8] = -11.0f;
    }
    GLfloat vertex_buffer_data2[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data2[i*9] = 0.0f;
        vertex_buffer_data2[i*9+1] = 0.0f;
        vertex_buffer_data2[i*9+2] = -12.0f;
        vertex_buffer_data2[i*9+3] = this->radius2 * cos(angleBefore);
        vertex_buffer_data2[i*9+4] = this->radius2 * sin(angleBefore);
        vertex_buffer_data2[i*9+5] = -12.0f;
        vertex_buffer_data2[i*9+6] = this->radius2 * cos(angle);
        vertex_buffer_data2[i*9+7] = this->radius2 * sin(angle);
        vertex_buffer_data2[i*9+8] = -12.0f;
    }
    GLfloat vertex_buffer_data3[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*9] = 0.0f;
        vertex_buffer_data3[i*9+1] = 0.0f;
        vertex_buffer_data3[i*9+2] = -11.0f;
        vertex_buffer_data3[i*9+3] = this->radius1 * cos(angleBefore);
        vertex_buffer_data3[i*9+4] = this->radius1 * sin(angleBefore);
        vertex_buffer_data3[i*9+5] = -11.0f;
        vertex_buffer_data3[i*9+6] = this->radius1 * cos(angle);
        vertex_buffer_data3[i*9+7] = this->radius1 * sin(angle);
        vertex_buffer_data3[i*9+8] = -11.0f;
    }
    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data1, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data2, COLOR_BRICK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data3, COLOR_BACKGROUND, GL_FILL);
}

void Shield::draw(glm::mat4 VP, int level) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(level==1 ? this->object1 : this->object3);
    draw3DObject(this->object2);
}
