#include "main.h"

#ifndef WALL_H
#define WALL_H


class Wall {
public:
    Wall() {}
    Wall(float top, float bottom);
    glm::vec3 position;
    void draw(glm::mat4 VP, int level);
private:
    VAO *object1;
    VAO *object2;
};

#endif
