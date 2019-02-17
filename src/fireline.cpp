#include "fireline.h"
#include "main.h"

Fireline::Fireline(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    // this->radius = 0.4;
    this->len = 0.4;
    this->balloon_hit = false;
    int max_angle = 45;
    this->rotation = (rand() % (1+2*max_angle)) - max_angle; // rotation is between -45 to +45
    this->rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->injure = false;
    this->a = 0.2;

    float length = this->len;

    static const GLfloat vertex_buffer_data1[] = {
        -a, -a, 0,
        -a, a, 0, 
        a, a, 0,
        -a, -a, 0,
        a, a, 0,
        a, -a, 0
    };

    float thickness = this->a/2;
    float up = thickness/2;
    float down = -thickness/2;

    static const GLfloat vertex_buffer_data2[] = {
        a, down, 0,
        a+length, down, 0,
        a+length, up, 0,

        a+length, up, 0,
        a, up, 0,
        a, down, 0
    };

    static const GLfloat vertex_buffer_data3[] = {
        a+length, a, 0,
        3*a+length, a, 0,
        a+length, -a, 0,

        3*a+length, a, 0,
        a+length, -a, 0,
        3*a+length, -a, 0
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_YELLOW, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}
