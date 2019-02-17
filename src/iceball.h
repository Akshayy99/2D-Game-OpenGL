#include "main.h"

#ifndef ICEBALL_H
#define ICEBALL_H


class Iceball {
public:
    Iceball() {}
    Iceball(float x, float y);
    glm::vec3 position;
    float radius1;
    float radius2;
    float zoom;
    float downspeed;
    float g;
    float speed;
    bool hit;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif
