#include "platform.h"
#include "main.h"

Platform::Platform(float top, float bottom) {
    float center = (top+bottom)/2;
    float division = bottom + ((top-bottom)*5)/6;
    this->position = glm::vec3(0, center, 0);

    float up2 = division - center;
    float down2 = -40.0;

    float length = 1000.0;

    static const GLfloat vertex_buffer_data_2[] = {
        -length, down2, -0.5,
        length,  down2, -0.5,
        length,  up2, -0.5,

        length,  up2, -0.5,
        -length, up2, -0.5,
        -length, down2, -0.5
    };

    float up1 = top - center;
    float down1 = up2;

    static const GLfloat vertex_buffer_data_1[] = {
        -length, down1, 0,
        length,  down1, 0,
        length,  up1, 0,

        length,  up1, 0,
        -length, up1, 0,
        -length, down1, 0
    };

    float up3 = top + 9.5;
    float up4 = up3 + 3;

    static const GLfloat vertex_buffer_data_3[] = {
        -length, up3, 0,
        length,  up3, 0,
        length,  up4, 0,

        length,  up4, 0,
        -length, up4, 0,
        -length, up3, 0
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_1, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_BROWN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_RED, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}
