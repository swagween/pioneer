//
//  Canvas.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/30/20.
//

#include "Canvas.hpp"
#include "../util/ServiceLocator.hpp"
#include "../util/Lookup.hpp"

namespace canvas {

Canvas::Canvas() {
}

Canvas::Canvas(sf::Vector2<uint16_t> dim) {
    dimensions = dim;
    real_dimensions = {(float)dim.x * CELL_SIZE, (float)dim.y * CELL_SIZE};
    for(int i = 0; i < NUM_LAYERS; ++i) {
        layers.push_back(Layer( i, (i == MIDDLEGROUND), dimensions ));
        layers.back().grid.initialize();
    }
}

void Canvas::load(const std::string& path) {
    
    std::string filepath = path + "/map_data.txt";
    
    int value{};
    int counter = 0;
    std::ifstream input{};
    input.open(filepath);
    if (!input.is_open()) {
        printf("Failed to open file.\n");
        return;
    }
    
    //dimensions and layers
    input >> value; dimensions.x = value; input.ignore();
    input >> value; dimensions.y = value; input.ignore();
    input >> value; chunk_dimensions.x = value; input.ignore();
    input >> value; chunk_dimensions.y = value; input.ignore();
    if((dimensions.x / chunk_dimensions.x != CHUNK_SIZE) ||
       (dimensions.y / chunk_dimensions.y != CHUNK_SIZE)) { printf("File is corrupted: Invalid dimensions.\n"); return; }
    real_dimensions = {(float)dimensions.x * CELL_SIZE, (float)dimensions.y * CELL_SIZE};
    for(int i = 0; i < NUM_LAYERS; ++i) {
        layers.push_back(Layer( i, (i == MIDDLEGROUND), dimensions ));
        layers.back().grid.initialize();
    }
    //style
    input >> value; input.ignore();
    if(value >= lookup::get_style.size()) { printf("File is corrupted: Invalid style.\n"); return; } else {
        style = lookup::get_style.at(value);
    }
    //bg;
    input >> value; input.ignore();
    if(value >= lookup::get_backdrop.size()) { printf("File is corrupted: Invalid backdrop.\n"); return; } else {
        bg = lookup::get_backdrop.at(value);
    }
    input.close();
    
    //get map tiles from text files
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
    svc::active_layer = MIDDLEGROUND;
}

bool Canvas::save(const std::string& path) {
    
    std::string filepath = path + "/map_data.txt";
    
    int value{};
    int counter = 0;
    std::filesystem::create_directory(path);
    std::ofstream output(filepath);
    if (!output.is_open()) {
        return false;
    }
    output << dimensions.x << ", " << dimensions.y << ", "
    << chunk_dimensions.x << ", " << chunk_dimensions.y << ", "
    << lookup::get_style_id.at(style) << ", " << lookup::get_backdrop_id.at(bg);
    output.close();
    
    for(auto& layer : layers) {
        int cell_ctr{0};
        //open map_tiles_[i].txt
        std::ofstream tile_output(path + "/map_tiles_" + std::to_string(counter) + ".txt");
//        output.open(path + "/map_tiles_" + std::to_string(counter) + ".txt");
        for(auto& cell : layer.grid.cells) {
            tile_output << std::to_string(layer.grid.cells.at(cell_ctr).value) + " ";
            
            tile_output << ", ";
            
            ++cell_ctr;
        }
        layer.grid.update();
        //close the current file
        tile_output.close();
        ++counter;
    }
    return true;
}

int Canvas::get_active_layer() {
    
}

void Canvas::edit_tile_at(int i, int j, int new_val, int layer_index) {
    if(layer_index >= layers.size()) { return; }
    if((i + j * dimensions.x) >= layers.at(layer_index).grid.cells.size()) { return; };
    layers.at(layer_index).grid.cells.at(i + j * dimensions.x).value = new_val;
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
