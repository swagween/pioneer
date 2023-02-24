//
//  Brush.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"

namespace tool {

void Brush::handle_events(canvas::Canvas& canvas) {
//    if(e.type == SDL_MOUSEBUTTONDOWN) {
//        active = true;
//        int mousex = 0;
//        int mousey = 0;
//        SDL_GetMouseState(&mousex, &mousey);
//        relativex = mousex - canvas->get_x();
//        relativey = mousey - canvas->get_y();
//        int posx = (int)relativex/CELL_SIZE;
//        int posy = (int)relativey/CELL_SIZE;
//        for(int i = 0; i < size; i++) {
//            for(int j = 0; j < size; j++) {
//                canvas->edit_tile_at(posy - i, posx - j, index, value);
//            }
//        }
//    }
//    if(e.type == SDL_MOUSEBUTTONUP) {
//        active = false;
//    }
//    if(e.type == SDL_MOUSEMOTION && active) {
//        int mousex = 0;
//        int mousey = 0;
//        SDL_GetMouseState(&mousex, &mousey);
//        relativex = mousex - canvas->get_x();
//        relativey = mousey - canvas->get_y();
//        int posx = (int)relativex/CELL_SIZE;
//        int posy = (int)relativey/CELL_SIZE;
//        for(int i = 0; i < size; i++) {
//            for(int j = 0; j < size; j++) {
//                canvas->edit_tile_at(posy - i, posx - j, index, value);
//            }
//        }
//    }
}

void Brush::update(int _x, int _y) {
}

void Brush::set_priority(bool prim) {
    primary = prim;
}

}
