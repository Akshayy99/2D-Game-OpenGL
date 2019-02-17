#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, int type) {
    this->position = glm::vec3(x, y, 0);
    this->radius = (type) ? 0.1 : 0.15;
    this->scored = false;
    float n = 360;
    // float r = 0.10;
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
        vertex_buffer_data[i*9+2] = -1.0f;
        vertex_buffer_data[i*9+3] = this->radius * cos(angleBefore);
        vertex_buffer_data[i*9+4] = this->radius * sin(angleBefore);
        vertex_buffer_data[i*9+5] = -1.0f;
        vertex_buffer_data[i*9+6] = this->radius * cos(angle);
        vertex_buffer_data[i*9+7] = this->radius * sin(angle);
        vertex_buffer_data[i*9+8] = -1.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, (type) ? COLOR_YELLOW : COLOR_GREEN, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
