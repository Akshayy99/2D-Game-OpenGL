#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y);
    float radius1;
    float radius2;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object2;
    VAO *object1;
    VAO *object3;
};

#endif
