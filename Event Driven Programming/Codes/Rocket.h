#ifndef SAMPLE_PROJECT_ROCKET_H
#define SAMPLE_PROJECT_ROCKET_H

#include "rsdl.hpp"

#define GRAVITY 10
#define INITIAL_JUMP_SPEED -50

class rocket {
public:
    rocket(Point top_left , int width , int height , Game* game);
    void draw_img();
    void update();
    void draw(window* win);
    void handle_key_press(char key);
    void handle_key_release(char key);
private:
    bool check_in_screen();
    
    Point top_left;
    int width, height;
    double vx , vy;
    double ay;
    Game* game;
};

#endif