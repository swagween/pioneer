//
//  Canvas.hpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/30/20.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include "Layer.hpp"
#include <fstream>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <system_error>
#include <iostream>

namespace canvas {

const int NUM_LAYERS{8};
const int CHUNK_SIZE{16};

enum class BACKDROP {
    BG_NULL,
    BG_SUNSET,
    BG_SUNRISE,
    BG_OPEN_SKY,
    BG_RED_SKY,
    BG_BLACK
};

enum LAYER_ORDER {
    BACKGROUND = 0,
    MIDDLEGROUND = 4,
    FOREGROUND = 7,
};

enum class STYLE {
    STYLE_NULL,
    FIRSTWIND = 0,
    OVERTURNED,
    GRUB,
    TOXIC,
    BASE,
    FROZEN,
    NIGHT,
    WORM,
    SKY,
    ASH,
    GREATWING,
    ICE,
    SNOW,
    STONE,
    ABANDONED,
    ANCIENT,
    FACTORY,
    SHADOW,
    HOARDER,
    MANSION
};

const int CELL_SIZE{32};

class Canvas {
    
public:
    
    Canvas();
    Canvas(sf::Vector2<uint16_t> dim);
    void load(const std::string& path);
    void save(const std::string& path);
    int get_active_layer();
    
    void edit_tile_at(int i, int j, int new_val, int layer_index);
    int tile_val_at(int i, int j, int layer);
    void render(sf::RenderWindow& win, std::vector<sf::Sprite>& tileset, sf::Vector2<float> cam);
    canvas::Tile& tile_at(const uint8_t i, const uint8_t j);
    TILE_TYPE lookup_type(int idx);
    
    //layers
    std::vector<Layer> layers{};
    sf::Vector2<float> real_dimensions{};
    sf::Vector2<uint16_t> dimensions{};
    sf::Vector2<uint16_t> chunk_dimensions{};
    
    STYLE style{};
    BACKDROP bg{};
    
};

}
