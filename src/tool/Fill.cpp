//
//  Fill.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"
#include "../util/ServiceLocator.hpp"

namespace tool {

void Fill::handle_events(canvas::Canvas& canvas, sf::Event& e) {
    
}

void Fill::update() {
    int posx = (int)position.x/canvas::CELL_SIZE;
    int posy = (int)position.y/canvas::CELL_SIZE;
    scaled_position = sf::Vector2<int>{posx, posy};
}

void Fill::fill_section(int prev_val, const int new_val, int i, int j, canvas::Canvas& canvas) {
    if(i < 0 || i >= canvas.dimensions.x || j < 0 || j >= canvas.dimensions.y) {
        return;
    } else if(canvas.tile_val_at(j, i, canvas.get_active_layer()) != prev_val) {
        return;
    } else if(canvas.tile_val_at(j, i, canvas.get_active_layer()) == new_val) {
        return;
    } else {
        
        canvas.edit_tile_at(j, i, new_val, svc::active_layer);
        
        fill_section(prev_val, new_val, i + 1, j, canvas);
        fill_section(prev_val, new_val, i - 1, j, canvas);
        fill_section(prev_val, new_val, i, j + 1, canvas);
        fill_section(prev_val, new_val, i, j - 1, canvas);
        
    }
}

void Fill::set_priority(bool prim) {
    primary = prim;
}

void Fill::store_tile(int index) {
    tile = index;
}

}
