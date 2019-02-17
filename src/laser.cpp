#include "laser.h"
#include "main.h"

Laser::Laser(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->a = 0.05;
    this->len = 3.0;
    this->speedy = 0.01;
    this->injure = false;
    this->balloon_hit = false;
    this->r = 0.07;
    this->gap = 2;
    float n = 360;
    float theta = 2*3.14159/n;
    int numTriangles = 360;
    float length = this->len;

    float thickness = this->a/2;
    float up1 = thickness/2;
    float down1 = -thickness/2;    
    float up2 = -gap + thickness/2;
    float down2 = -gap - thickness/2;


    GLfloat vertex_buffer_data1[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*9] = 0.0f;
        vertex_buffer_data1[i*9+1] = 0.0f;
        vertex_buffer_data1[i*9+2] = 0.0f;
        vertex_buffer_data1[i*9+3] = this->r * cos(angleBefore);
        vertex_buffer_data1[i*9+4] = this->r * sin(angleBefore);
        vertex_buffer_data1[i*9+5] = 0.0f;
        vertex_buffer_data1[i*9+6] = this->r * cos(angle);
        vertex_buffer_data1[i*9+7] = this->r * sin(angle);
        vertex_buffer_data1[i*9+8] = 0.0f;
    };

    static const GLfloat vertex_buffer_data2[] = {
        0, up1, 0,
        0, down1, 0,
        length, up1, 0,

        length,  up1, 0,
        0, down1, 0,
        length, down1, 0
    };

    GLfloat vertex_buffer_data3[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*9] = length;
        vertex_buffer_data3[i*9+1] = 0.0f;
        vertex_buffer_data3[i*9+2] = 0.0f;
        vertex_buffer_data3[i*9+3] = length +  this->r * cos(angleBefore);
        vertex_buffer_data3[i*9+4] = this->r * sin(angleBefore);
        vertex_buffer_data3[i*9+5] = 0.0f;
        vertex_buffer_data3[i*9+6] = length + this->r * cos(angle);
        vertex_buffer_data3[i*9+7] = this->r * sin(angle);
        vertex_buffer_data3[i*9+8] = 0.0f;
    };

    GLfloat vertex_buffer_data4[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data4[i*9] = 0.0f;
        vertex_buffer_data4[i*9+1] = -gap + 0.0f;
        vertex_buffer_data4[i*9+2] = 0.0f;
        vertex_buffer_data4[i*9+3] = this->r * cos(angleBefore);
        vertex_buffer_data4[i*9+4] = -gap + this->r * sin(angleBefore);
        vertex_buffer_data4[i*9+5] = 0.0f;
        vertex_buffer_data4[i*9+6] = this->r * cos(angle);
        vertex_buffer_data4[i*9+7] = -gap + this->r * sin(angle);
        vertex_buffer_data4[i*9+8] = 0.0f;
    };

    static const GLfloat vertex_buffer_data5[] = {
        0, up2, 0,
        0, down2, 0,
        length, up2, 0,

        length,  up2, 0,
        0, down2, 0,
        length, down2, 0
    };

    GLfloat vertex_buffer_data6[numTriangles*9];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data6[i*9] = length + 0.0f;
        vertex_buffer_data6[i*9+1] = -gap + 0.0f;
        vertex_buffer_data6[i*9+2] = 0.0f;
        vertex_buffer_data6[i*9+3] = length + this->r * cos(angleBefore);
        vertex_buffer_data6[i*9+4] = -gap + this->r * sin(angleBefore);
        vertex_buffer_data6[i*9+5] = 0.0f;
        vertex_buffer_data6[i*9+6] = length + this->r * cos(angle);
        vertex_buffer_data6[i*9+7] = -gap + this->r * sin(angle);
        vertex_buffer_data6[i*9+8] = 0.0f;
    }
    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data3, COLOR_RED, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data4, COLOR_RED, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, COLOR_RED, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data6, COLOR_RED, GL_FILL);
}

void Laser::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Laser::tick()
{
    this->position.y += this->speedy;
    if(this->position.y <= 0)
    {   
        this->position.y = 0.001;
        this->speedy *= -1;
    }
    if(this->position.y >= 3) {
        this->speedy *= -1;
        this->position.y = 2.999;
    }
}