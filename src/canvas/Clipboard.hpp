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

const int MAX_DIM = 256;
const int MIN_DIM = 8;

class Clipboard {
    
public:
    
    Clipboard();
    
    void init();
    
    void write_to_clipboard(canvas::Tile selection[MAX_DIM][MAX_DIM]);
    void clear_clipboard();
    
    void set_width_and_height(int w_, int h_);
    
    int get_value_at(int i, int j, int idx);
    
    int get_width();
    int get_height();
    
private:
    
    int width;
    int height;
    
    canvas::Tile coords[MAX_DIM][MAX_DIM];
    
};

}
