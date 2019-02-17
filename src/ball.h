#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP, bool jet);
    void set_position(float x, float y);
    void tick();
    double speed;
    double upspeed;
    double original_speed;
    double downspeed;
    // bool onPlatform;
    bool moveDown;
    bool moveup;
    double g;
    double friction;
    double jumpspeed;
private:
    VAO *object1;
    VAO *object2;
};

#endif // BALL_H
