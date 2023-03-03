//
//  Metagrid.hpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/30/20.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "../canvas/Grid.hpp"
#include <stdio.h>

namespace meta {

struct Chunk {
    sf::Vector2<uint16_t> position{}; // in the grid, not in the window
    uint16_t chunk_id{}; // unique to the chunk
    uint16_t room_id{}; // should match an existing level
    bool vacant{};
};

class Metagrid {
    
public:
    
    Metagrid(sf::Vector2<uint16_t> dim);
    
    void add_room_at(sf::Vector2<uint16_t> pos, sf::Vector2<uint16_t> dim, uint16_t rm_id);
    
    sf::Vector2<uint16_t> dimensions{};
    std::vector<Chunk> chunks{};
    
};


}
