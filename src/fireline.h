#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y);
    glm::vec3 position;
    float a;
    float len;
    float rotation;
    bool injure;
    bool balloon_hit;
    void draw(glm::mat4 VP);
    void tick();
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif
