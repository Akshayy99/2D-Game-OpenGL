#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y);
    glm::vec3 position;
    float radius;
    float speedx;
    float rotation;
    int flag;
    bool injure;
    bool turn;
    void draw(glm::mat4 VP, int level);
    void tick();
    // glm::mat4 rotate;
    // glm::mat4 rotMatrix;
private:
    VAO *object;
    VAO *object2;
};

#endif
