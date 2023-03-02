//
//  SelectionRectangular.cpp
//  Pioneer Lab
//
//  Created by Alex Frasca on 12/4/22.
//

#include "Tool.hpp"

namespace tool {

void SelectionRectangular::handle_events(canvas::Canvas& canvas, sf::Event& e) {
    //    if(event_type = mouse_button_down && active) {
    //get mnouse state
    //adjust
    //change selection
    //selection.adjust(posx - selection.box_x, posy - selection.box_y);
    
    //    }
    //    if(e.type == SDL_MOUSEBUTTONUP) {
    //        active = false;
    //    }
    //    if(event_type = mouse_motion && active) {
    //get mnouse state
    //adjust
    //change selection
    //selection.adjust(posx - selection.box_x, posy - selection.box_y);
    
    //    }
    //    if(e.type == SDL_KEYDOWN) {
    //        if(e.key.keysym.sym == SDLK_c) {
    //            clipboard.clear_clipboard();
    //            Tile layer_bit[MAX_DIM][MAX_DIM];
    //            for(int i = 0; i < selection.box_w; i++) {
    //                for(int j = 0; j < selection.box_h; j++) {
    //                    layer_bit[i][j] = (canvas->layers[canvas->get_active_layer()].coords[j + selection.box_y][i + selection.box_x]);
    //                }
    //            }
    //            clipboard.set_width_and_height(selection.box_w, selection.box_h);
    //            clipboard.write_to_clipboard(layer_bit);
    //            std::printf("COPIED FROM: \n");
    //            std::printf("X: ");
    //            std::printf(std::to_string(selection.box_x).c_str());
    //            std::printf("\nY: ");
    //            std::printf(std::to_string(selection.box_y).c_str());
    //            std::printf("\n");
    //
    //        }
    //        if(e.key.keysym.sym == SDLK_v) {
    //            int mousex = 0;
    //            int mousey = 0;
    //            SDL_GetMouseState(&mousex, &mousey);
    //            relativex = mousex - canvas->get_x();
    //            relativey = mousey - canvas->get_y();
    //            int posx = (int)relativex/CELL_SIZE;
    //            int posy = (int)relativey/CELL_SIZE;
    //            for(int i = 0; i < selection.box_w; i++) {
    //                for(int j = 0; j < selection.box_h; j++) {
    //                    canvas->layers[canvas->get_active_layer()].coords[posy + j][ posx + i].vals[0] = clipboard.get_value_at(i, j, index);
    //                }
    //            }
    //            int num_printed_tiles = clipboard.get_width() * clipboard.get_height();
    //            std::printf("PASTED ");
    //            std::printf(std::to_string(num_printed_tiles).c_str());
    //            std::printf(" TILES TO: \n");
    //            std::printf("X: ");
    //            std::printf(std::to_string(posx).c_str());
    //            std::printf("\nY: ");
    //            std::printf(std::to_string(posy).c_str());
    //            std::printf("\n");
    //        }
    //    }
}

void SelectionRectangular::render_with_layer_info(const canvas::Layer &layer) {
    render_selection(layer);
}

void SelectionRectangular::render_selection(const canvas::Layer& layer) {
    
}

void SelectionRectangular::update() {
    int posx = (int)position.x/canvas::CELL_SIZE;
    int posy = (int)position.y/canvas::CELL_SIZE;
    scaled_position = sf::Vector2<int>{posx, posy};
}

void SelectionRectangular::set_priority(bool prim) {
    primary = prim;
}

void SelectionRectangular::store_tile(int index) {

}

}
