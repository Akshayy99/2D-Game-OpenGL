#include "main.h"

#ifndef SEMICIRCLE_H
#define SEMICIRCLE_H


class Semicircle {
public:
    Semicircle() {}
    Semicircle(float x, float y);
    glm::vec3 position;
    float radius1;
    float radius2;
    bool scored;
    // double speedx;
    void draw(glm::mat4 VP);
    void tick();
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object1;
    VAO *object2;
};

#endif
