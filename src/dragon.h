#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(float px, float py);
    double speed;
    double upspeed;
    double downspeed;
    bool moveDown;
    bool moveup;
    double g;
    double friction;
    double jumpspeed;
private:
    VAO *object;
};

#endif // DRAGON_H
