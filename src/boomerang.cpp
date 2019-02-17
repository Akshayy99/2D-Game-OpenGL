#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->radius = 0.25;
    this->rotation = 0;
    // this->rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->speedx = -0.08;
    this->injure = false;
    this->turn = false;
    this->flag = 0;

    int numTriangles = 2;
    static const GLfloat vertex_buffer_data[] = {
        -0.25f, 0.5f, -2.0f,
        -0.25f,  0.0f, -2.0f, 
        0.0f, 0.0f, -2.0f, 

        0.25f, 0.0f, -2.0f,
        0.25f, 0.5f, -2.0f, 
        0.0f, 0.0f, -2.0f
    };
    static const GLfloat vertex_buffer_data2[] = {
        -0.25f, 0.5f, -2.0f,
        -0.25f,  0.0f, -2.0f, 
        0.0f, 0.0f, -2.0f, 

        0.25f, 0.0f, -2.0f,
        0.25f, 0.5f, -2.0f, 
        0.0f, 0.0f, -2.0f
    };
    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP, int level) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(level==1 ? this->object2 : this->object);
}

void Boomerang::tick() {
    // cout << this->radius << endl;
    // this->g = -0.008;
    // this->speedy = ((rand() + 0.001)/(RAND_MAX )) * 1;
    // this->far = false;
    this->rotation += 8;
    this->position.x += speedx;
    // this->position.y += this->speedy;
    // this->speedy += this->g;
    // if(this->position.y >= 0.5)
    // {
        // if(this->speedy < 0) this->g = -0.01;
        // this->g = -0.01;
    // }
    // else if(this->position.y < 0.5)
    // {
        // if(this->speedy < 0) this->g = 0.01;
        // this->g = 0.01;
    // }
    if(this->speedx > 0) this->flag = 2;
    if(this->flag == 2)
    {
        if(this->speedx <= 0.8) this->speedx += 0.005;
    }
    if(this->turn && this->flag)
    {
        this->speedx += 0.005;
        // if(this->speedx >= 0.07) this->flag = false;

        if(this->position.y > -1)
        {
            this->position.y -= 0.09;
            // this->speedy = 0;
        }
        if(this->position.y <= -1.2)
        {
            // this->speedy = -this->speedy;
            this->position.y = -1;
            this->flag = false;
        }
    }

}