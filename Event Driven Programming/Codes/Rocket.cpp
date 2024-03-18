#include "Rocket.h"
#include "Game.h"

rocket::rocket(Point _top_left, int _width, int _height ,Game* _game) : top_left(_top_left) {
    width = _width;
    height = _height
    vx = vy = 0;
    ay = GRAVITY;
    game = _game;
}

void rocket::update() {
    top_left.x += vx;
    top_left.y += vy;
    vy += ay;
// ageee be zamin khordeh basheeeeeeeeeee?????!!!!!!!!!!!!!!!!!!!!!!!!! handelesh kon ke paiin tar nare
    // if (touches_ground()) {
    //     center.y = game->get_ground_y() - radius;
    //     vy = ay = 0;
    // }
}

void rocket::draw(Window* win) {
    win->draw_img("pngwing.com.png", Rectangle(top_left , width , height));
}

void rocket::handle_key_press(char key){
    switch (key) {
        case 'd':
            vx = 15;
            break;
        case 'a':
            vx = -15;
            break;
        case 'w':
            vy = 15;
            break;
        case 's':
            if ()
            vy = -15;
            break;
    }
}

void rocket::handle_key_release(char key) {
    switch(key) {
        case 'd':
            if (vx > 0) vx = 0;
            break;
        case 'a':
            if (vx < 0) vx = 0;
            break;
        case 's':
            if (vy < 0) vy = 0;
            break;
        case 'w':
            if (vy > 0) vy = 0;
            break;
    }
}

bool rocket::check_in_screen() {
    return true;//todo
}