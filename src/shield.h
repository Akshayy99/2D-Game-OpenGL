#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H


class Shield {
public:
    Shield() {}
    Shield(float x, float y);
    glm::vec3 position;
    float radius1;
    float radius2;
    bool scored;
    double speedx;
    void draw(glm::mat4 VP, int level);
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif
