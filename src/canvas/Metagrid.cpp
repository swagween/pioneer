//
//  Metagrid.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/30/20.
//

#include "Metagrid.hpp"
#include "../util/Lookup.hpp"

namespace meta {

Metagrid::Metagrid(sf::Vector2<uint16_t> dim) : dimensions(dim) {
    for(int i = 0; i < dimensions.x; ++i) {
        for(int j = 0; j < dimensions.y; ++j) {
            chunks.push_back(Chunk{ {(uint16_t)i, (uint16_t)j}, (uint16_t)(i + j * dimensions.y), 0, true });
        }
    }
}

void Metagrid::add_room_at(sf::Vector2<uint16_t> pos, sf::Vector2<uint16_t> dim, uint16_t rm_id) {
    for(int i = 0; i < dim.x; ++i) {
        for(int j = 0; j < dim.y; ++j) {
            chunks.at(pos.x + i + pos.y + j * dimensions.y).room_id = rm_id;
            chunks.at(pos.x + i + pos.y + j * dimensions.y).vacant = false;
        }
    }
}

void Metagrid::remove_room(uint16_t rm_id) {
    
}

}

