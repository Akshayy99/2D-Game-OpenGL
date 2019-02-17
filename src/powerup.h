#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y, int type);
    glm::vec3 position;
    float radius;
    bool far;
    bool scored;
    double speedx;
    double speedy;
    bool moveDown = false;
    bool moveup = false;
    double g = 0.01;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
