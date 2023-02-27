//
//  Clipboard.cpp
//  Pioneer Lab
//
//  Created by Alex Frasca on 12/4/22.
//

#include "Clipboard.hpp"

namespace canvas {

Clipboard::Clipboard() {
}

void Clipboard::write_to_clipboard(std::vector<Tile>& selection) {
    cells = selection;
}

void Clipboard::clear_clipboard() {
    cells.clear();
}

uint16_t Clipboard::get_value_at(uint16_t i, uint16_t j, uint16_t idx) {
    assert(i + j * dimensions.x < cells.size());
    return cells.at(i + j * dimensions.x).value;
}

}
