//
//  Tool.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"

namespace tool {

bool Tool::in_bounds(sf::Vector2<uint16_t>& bounds) {
    return scaled_position.x >= 0 && scaled_position.x < bounds.x && scaled_position.y >= 0 && scaled_position.y < bounds.y;
}

void Tool::update() {
    uint16_t posx = (uint16_t)position.x/canvas::CELL_SIZE;
    uint16_t posy = (uint16_t)position.y/canvas::CELL_SIZE;
    scaled_position = sf::Vector2<uint16_t>{posx, posy};
}



}
