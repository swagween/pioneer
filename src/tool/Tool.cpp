//
//  Tool.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"

namespace tool {

bool Tool::in_bounds(sf::Vector2<float>& bounds) {
    return position.x >= 0 && position.x < bounds.x && position.y >= 0 && position.y < bounds.y;
}

void Tool::set_size(int new_size) {
    size = new_size;
}

int Tool::get_size() {
    return size;
}

}
