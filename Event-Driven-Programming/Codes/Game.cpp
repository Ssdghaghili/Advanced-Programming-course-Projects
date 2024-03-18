#include "Game.h"
#include "./src/rsdl.hpp"
#include "rsdl.hpp"

Game::Game() : rocket(Point(50,50), 20, 20,this) {}

void Game::run(){
    game_running = true;
    while(game_running){
        process_event();
        update_object();
        draw_screen();
        delay(100);
    }
}  
void Game::process_events() {
    while(win.has_pending_event()) {
        Event event = win.poll_for_event();
        switch (event.get_type()) {
            case Event::QUIT:
                game_running = false;
                break;
            case Event::KEY_PRESS:
                rocket.handle_key_press(event.get_pressed_key());
                break;
            case Event::KEY_RELEASE:
                rocket.handle_key_release(event.get_pressed_key());
                break;
        }
    }
}
void Game::draw_screen() {
    win.clear();
    circle.draw(&win);
    win.update_screen();
}
void Game::update_objects() {
    rocket.update(); 
}