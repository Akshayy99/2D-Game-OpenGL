#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H


class Platform {
public:
    Platform() {}
    Platform(float top, float bottom);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif
