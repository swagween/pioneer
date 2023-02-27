//
//  Clipboard.hpp
//  Pioneer Lab
//
//  Created by Alex Frasca on 12/4/22.
//

#pragma once

#include "Tile.hpp"
#include <vector>
#include <stdio.h>

namespace canvas {

class Clipboard {
    
public:
    
    Clipboard();
    
    void write_to_clipboard(std::vector<Tile>& selection);
    void clear_clipboard();
    uint16_t get_value_at(uint16_t i, uint16_t j, uint16_t idx);
    
    sf::Vector2<uint16_t> dimensions{};
    
    std::vector<Tile> cells;
    
};

}
