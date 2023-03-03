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

void Clipboard::write_to_clipboard(std::vector<uint8_t>& selection) {
    cell_values = selection;
}

void Clipboard::clear_clipboard() {
    cell_values.clear();
}

uint8_t Clipboard::get_value_at(uint16_t i, uint16_t j) {
    assert(i + j * dimensions.x < cell_values.size());
    return cell_values.at(i + j * dimensions.x);
}

}
