//
//  Clipboard.cpp
//  Pioneer Lab
//
//  Created by Alex Frasca on 12/4/22.
//

#include "Clipboard.hpp"

namespace canvas {

Clipboard::Clipboard() {
    width = 0;
    height = 0;
    for (int i = 0; i < MAX_DIM; i++) {
        for (int j = 0; j < MAX_DIM; j++) {
//            coords[i][j] = Tile(i, j);
        }
    }
}

void Clipboard::init() {
    width = 0;
    height = 0;
    for (int i = 0; i < MAX_DIM; i++) {
        for (int j = 0; j < MAX_DIM; j++) {
//            coords[i][j] = Tile(i, j);
        }
    }
}

void Clipboard::write_to_clipboard(Tile selection[MAX_DIM][MAX_DIM]) {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
//            coords[i][j].vals[0] = selection[i][j].vals[0];
        }
    }
}

void Clipboard::clear_clipboard() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
//            coords[i][j].clear();
        }
    }
}

int Clipboard::get_value_at(int i, int j, int idx) {
//    return coords[i][j].vals[0];
}

void Clipboard::set_width_and_height(int w_, int h_) {
    width = w_;
    height = h_;
}

int Clipboard::get_width() {
    return width;
}

int Clipboard::get_height() {
    return height;
}

}
