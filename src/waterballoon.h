#include "main.h"

#ifndef WATERBALLOON_H
#define WATERBALLOON_H


class Waterballoon {
public:
    Waterballoon() {}
    Waterballoon(float x, float y);
    glm::vec3 position;
    float radius;
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
