#include "wall.h"
#include "main.h"

Wall::Wall(float top, float bottom) {
    float center = (top+bottom)/2;
    float division = bottom + ((top-bottom)*5)/6;
    this->position = glm::vec3(0, center, 0);

    float length = 4000.0;

    static const GLfloat vertex_buffer_data[] = {
        -length, length, -50,
        length,  length, -50,
        -length,  -length, -50,

        length,  length, -050,
        -length, -length, -50,
        length, -length, -50
    };
    static const GLfloat vertex_buffer_data2[] = {
        -length, length, -50,
        length,  length, -50,
        -length,  -length, -50,

        length,  length, -050,
        -length, -length, -50,
        length, -length, -50
    };
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
}

void Wall::draw(glm::mat4 VP, int level) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(level==1 ? this->object1 : this->object2);
}
