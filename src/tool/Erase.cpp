//
//  Erase.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"
#include "../util/ServiceLocator.hpp"
#include <imgui.h>

namespace tool {

void Erase::handle_events(canvas::Canvas& canvas, sf::Event e) {
    if(in_bounds(canvas.real_dimensions) && ready) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                canvas.edit_tile_at(scaled_position.x - i, scaled_position.y - j, 0, svc::active_layer);
            }
        }
    }
    update();
}

void Erase::update() {
    int posx = (int)position.x/canvas::CELL_SIZE;
    int posy = (int)position.y/canvas::CELL_SIZE;
    scaled_position = sf::Vector2<int>{posx, posy};
}

void Erase::set_priority(bool prim) {
    primary = prim;
}

void Erase::store_tile(int index) {
    tile = index;
}

}
