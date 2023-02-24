//
//  Layer.hpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/30/20.
//

#pragma once

#include <stdio.h>
#include "Grid.hpp"
#include <fstream>

namespace canvas {

class Layer {
    
public:
    
    Layer() = default;
    Layer(uint8_t o, bool c, sf::Vector2<uint16_t> dim) : render_order(o), collidable(c), dimensions(dim) {
        grid = Grid({dim.x, dim.y});
    }
    Grid grid{};
    uint8_t render_order{};
    bool collidable{};
    sf::Vector2<uint16_t> dimensions{};
    
};

}
