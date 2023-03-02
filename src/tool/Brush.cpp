//
//  Brush.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"
#include "../util/ServiceLocator.hpp"
#include <imgui.h>

namespace tool {

void Brush::handle_events(canvas::Canvas& canvas, sf::Event& e) {
    if(in_bounds(canvas.real_dimensions) && ready) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                canvas.edit_tile_at(scaled_position.x - i, scaled_position.y - j, tile, svc::active_layer);
            }
        }
    }
    update();
}

void Brush::update() {
    int posx = (int)position.x/canvas::CELL_SIZE;
    int posy = (int)position.y/canvas::CELL_SIZE;
    scaled_position = sf::Vector2<int>{posx, posy};
}

void Brush::set_priority(bool prim) {
    primary = prim;
}

void Brush::store_tile(int index) {
    tile = index;
}

}
