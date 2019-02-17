#include "main.h"

#ifndef LASER_H
#define LASER_H


class Laser {
public:
    Laser() {}
    Laser(float x, float y);
    glm::vec3 position;
    float a;
    float r;
    float len;
    float gap;
    float speedy;
    bool injure;
    bool balloon_hit;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;    
    VAO *object5;
    VAO *object6;
};

#endif
