//
//  Canvas.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/30/20.
//

#include "Canvas.hpp"

namespace canvas {

Canvas::Canvas() {
    for(int i = 0; i < NUM_LAYERS; ++i) {
        layers.push_back(Layer( i, (i == MIDDLEGROUND), dimensions ));
        layers.back().grid.initialize();
    }
    dimensions = {32, 48};
}

Canvas::Canvas(sf::Vector2<uint16_t> dim) {
    dimensions = dim;
    for(int i = 0; i < NUM_LAYERS; ++i) {
        layers.push_back(Layer( i, (i == MIDDLEGROUND), dimensions ));
        layers.back().grid.initialize();
    }
}

void Canvas::load(const std::string& path) {
    
    //get data from text files
    int value{};
    int counter = 0;
    std::ifstream input{};
    for(auto& layer : layers) {
        //open map_tiles_[i].txt
        input.open(path + "/map_tiles_" + std::to_string(counter) + ".txt");
        for(auto& cell : layer.grid.cells) {
            input >> value;
            canvas::TILE_TYPE typ = lookup_type(value);
            cell.value = value;
            cell.type = typ;
            
            input.ignore(); //ignore the delimiter
            input.ignore();
            input.ignore();
        }
        layer.grid.update();
        //close the current file
        input.close();
        ++counter;
    }
}

void Canvas::save(const std::string& path) {
    
    std::string filepath = path + "/map_data.txt";
    
    int value{};
    int counter = 0;
    std::ofstream output{};
    output.open(path);
    if (!output.is_open()) {
        printf("Failed to open file.");
        return;
    }
    output << dimensions.x << ", " << dimensions.y << ", "
    << chunk_dimensions.x << ", " << chunk_dimensions.y << ", "
    << (int)style << ", " << (int)bg;
    output.close();
    
    
    
    for(auto& layer : layers) {
        int cell_ctr{};
        //open map_tiles_[i].txt
        output.open(path + "/map_tiles_" + std::to_string(counter) + ".txt");
        for(auto& cell : layer.grid.cells) {
            output << std::to_string(layer.grid.cells.at(cell_ctr).value) + " ";
            
            output << ", ";
            
            ++cell_ctr;
        }
        layer.grid.update();
        //close the current file
        output.close();
        ++counter;
    }
}

int Canvas::get_active_layer() {
    
}

void Canvas::edit_tile_at(int i, int j, int index, int new_val) {
    
}

int Canvas::tile_val_at(int i, int j, int layer) {
    
}

TILE_TYPE Canvas::lookup_type(int idx) {
    if(idx < 1) {
        return TILE_NULL;
    }
    if(idx < 192) {
        return TILE_BASIC;
    }
    if(idx <= 223) {
        return TILE_RAMP;
    }
    if(idx <= 227) {
        return TILE_LAVA;
    }
    if(idx <= 231) {
        return TILE_CURRENT;
    }
    if(idx <= 235) {
        return TILE_FLAMMABLE;
    }
    if(idx <= 239) {
        return TILE_PLATFORM;
    }
    if(idx <= 243) {
        return TILE_WATER;
    }
    if(idx <= 247) {
        return TILE_BREAKABLE;
    }
    if(idx <= 251) {
        return TILE_LADDER;
    }
    if(idx <= 255) {
        return TILE_SPIKES;
    }
    return TILE_NULL;
}


}
