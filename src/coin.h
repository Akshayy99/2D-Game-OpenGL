#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, int type);
    glm::vec3 position;
    float radius;
    bool scored;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif
