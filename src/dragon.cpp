#include "dragon.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    float zoom = 0.2;
    int numTriangles = 20;
        
    static const GLfloat vertex_buffer_data[] = {
        // neck + face
        zoom*-3.0f, zoom*3.0f, 0.0f, // neck
        zoom*-1.0f, zoom*3.0f, 0.0f,
        zoom*-1.5f, zoom*6.0f, 0.0f,

        zoom*-1.0f, zoom*3.0f, 0.0f,
        zoom*-1.5f, zoom*6.0f, 0.0f, 
        zoom*0.0f, zoom*6.0f, 0.0f, //

        zoom*-1.5f, zoom*6.0f, 0.0f, // back of head
        zoom*0.0f, zoom*6.0f, 0.0f,
        zoom*-1.0f, zoom*8.0f, 0.0f, //

        zoom*1.0f, zoom*9.0f, 0.0f, // right ear
        zoom*-1.0f, zoom*8.0f, 0.0f, 
        zoom*-0.5f, zoom*5.0f, 0.0f, //

        zoom*-1.0f, zoom*8.0f, 0.0f, // left ear
        zoom*-1.0f, zoom*10.0f, 0.0f,
        zoom*-1.5f, zoom*7.166666f, 0.0f, //43/6=7.16666

        zoom*-1.0f, zoom*8.0f, 0.0f, // upper jaw
        zoom*-4.0f, zoom*7.0f, 0.0f,
        zoom*-1.25f, zoom*7.0f, 0.0f, //

        zoom*-2.0f, zoom*7.0f, 0.0f, // lower jaw 
        zoom*-5.0f, zoom*6.0f, 0.0f, 
        zoom*-3.0f, zoom*5.0f, 0.0f, 

        zoom*-2.0f, zoom*7.0f, 0.0f,
        zoom*-3.0f, zoom*5.0f, 0.0f, 
        zoom*-1.5f, zoom*6.0f, 0.0f,

        zoom*-2.0f, zoom*7.0f, 0.0f, 
        zoom*-1.25f, zoom*7.0f, 0.0f,
        zoom*-1.5f, zoom*6.0f, 0.0f, //

        zoom*-3.0f, zoom*3.0f, 0.0f, // chest
        zoom*-1.0f, zoom*3.0f, 0.0f,
        zoom*-2.0f, zoom*0.5f, 0.0f,

        zoom*-1.0f, zoom*3.0f, 0.0f, 
        zoom*-2.0f, zoom*0.5f, 0.0f,
        zoom*0.0f, zoom*1.0f, 0.0f,
        
        zoom*0.0f, zoom*1.0f, 0.0f, 
        zoom*-2.0f, zoom*0.5f, 0.0f,
        zoom*0.0f, zoom*0.0f, 0.0f,  //

        zoom*0.0f, zoom*0.0f, 0.0f, // middle
        zoom*5.0f, zoom*5.0f, 0.0f,
        zoom*0.0f, zoom*1.0f, 0.0f,
        
        zoom*0.0f, zoom*0.0f, 0.0f,
        zoom*5.0f, zoom*5.0f, 0.0f,
        zoom*5.0f, zoom*3.0f, 0.0f, //

        zoom*5.0f, zoom*5.0f, 0.0f,
        zoom*5.0f, zoom*3.0f, 0.0f,
        zoom*7.0f, zoom*4.0f, 0.0f,

        zoom*7.0f, zoom*4.0f, 0.0f,
        zoom*5.0f, zoom*3.0f, 0.0f,
        zoom*4.0f, zoom*-0.5f, 0.0f,

        zoom*4.0f, zoom*-0.5f, 0.0f,
        zoom*7.0f, zoom*4.0f, 0.0f,
        zoom*6.0f, zoom*1.0f, 0.0f,

        zoom*6.0f, zoom*1.0f, 0.0f,
        zoom*4.0f, zoom*-0.5f, 0.0f,
        zoom*5.2f, zoom*-1.0f, 0.0f,

        zoom*5.2f, zoom*-1.0f, 0.0f,
        zoom*6.0f, zoom* 1.0f, 0.0f,
        zoom*6.5f, zoom*0.0f, 0.0f,
        
        zoom*6.5f, zoom*0.0f, 0.0f,
        zoom*6.0f, zoom*1.0f, 0.0f, 
        zoom*8.0f, zoom*2.5f, 0.0f // legs end
    };
    this->object = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick(float px, float py) {

    if(this->position.x - px <= 3)
        this->position.x = px + 3;

    this->position.y += ((py-this->position.y-1.2 > 0) ? 1 : -1) * 0.05;

}
