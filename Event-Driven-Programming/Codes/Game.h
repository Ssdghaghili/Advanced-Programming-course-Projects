#ifndef SAMPLE_PROJECT_GAME_H
#define SAMPLE_PROJECT_GAME_H

#include"rocket.h"

class Game {
public:
    Game();
    void run();
private:
    void process_events();
    void draw_screen();
    void update_object();
    
    bool game_running;
    rocket rocket;
    Window win;
};


#endif