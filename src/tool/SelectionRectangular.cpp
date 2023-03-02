//
//  SelectionRectangular.cpp
//  Pioneer Lab
//
//  Created by Alex Frasca on 12/4/22.
//

#include "Tool.hpp"
#include "../util/ServiceLocator.hpp"

namespace tool {

void SelectionRectangular::handle_events(canvas::Canvas& canvas, sf::Event& e) {
    if(in_bounds(canvas.dimensions) && ready) {
        if(active) {
            if(just_clicked) {
                clicked_position = position;
                scaled_clicked_position.x = clicked_position.x/canvas::CELL_SIZE;
                scaled_clicked_position.y = clicked_position.y/canvas::CELL_SIZE;
                selection = SelectBox(scaled_clicked_position, {0, 0});
                just_clicked = false;
            }
            selection.adjust(scaled_position - selection.position);
        } else {
        }
    }
    update();
}

void SelectionRectangular::handle_keyboard_events(canvas::Canvas& canvas, sf::Keyboard::Key& key) {
    if(key == sf::Keyboard::C) {
        copy(canvas);
    }
    if(key == sf::Keyboard::V) {
        paste(canvas);
    }
}

void SelectionRectangular::update() {
    tool::Tool::update();
}

void SelectionRectangular::render_with_layer_info(const canvas::Layer &layer) {
    render_selection(layer);
}

void SelectionRectangular::render_selection(const canvas::Layer& layer) {
    
}

void SelectionRectangular::set_priority(bool prim) {
    primary = prim;
}

void SelectionRectangular::store_tile(int index) {

}

void SelectionRectangular::copy(canvas::Canvas& canvas) {
    printf("Copied %u Cells.\n", selection.dimensions.x * selection.dimensions.y);
    printf("Select Box X Position: %u \n", selection.position.x);
    printf("Select Box Y Position: %u \n", selection.position.y);
    clipboard.clear_clipboard();
    for(int i = 0; i < selection.dimensions.x; ++i) {
        for(int j = 0; j < selection.dimensions.y; ++j) {
            clipboard.cell_values.push_back(canvas.tile_val_at(selection.position.x + i, selection.position.y + j, svc::active_layer));
        }
    }
}

void SelectionRectangular::paste(canvas::Canvas& canvas) {
    printf("Pasted %u Cells.\n", selection.dimensions.x * selection.dimensions.y);
    for(int i = 0; i < selection.dimensions.x; ++i) {
        for(int j = 0; j < selection.dimensions.y; ++j) {
            canvas.edit_tile_at(scaled_position.x + i, scaled_position.y + j, clipboard.cell_values.at(j + i * selection.dimensions.y), svc::active_layer);
        }
    }
}

}
