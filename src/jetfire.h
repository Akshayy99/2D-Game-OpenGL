#include "main.h"

#ifndef JETFIRE_H
#define JETFIRE_H


class Jetfire {
public:
    Jetfire() {}
    Jetfire(float x, float y);
    glm::vec3 position;
    float downspeed;
    float g;
    float zoom;
    bool bahar;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object2;
};

#endif
