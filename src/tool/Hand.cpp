//
//  Hand.cpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#include "Tool.hpp"
#include "../util/ServiceLocator.hpp"

namespace tool {

void Hand::handle_events(canvas::Canvas& canvas, sf::Event& e) {
    if(ready) {
        if(just_clicked) {
            clicked_position = position;
            just_clicked = false;
        }
        relative_position = position - clicked_position;
        active = true;
    } else {
        clicked_position = {0.0f, 0.0f};
        relative_position = {0.0f, 0.0f};
    }
    update();
}

void Hand::update() {
    int posx = (int)position.x/canvas::CELL_SIZE;
    int posy = (int)position.y/canvas::CELL_SIZE;
    scaled_position = sf::Vector2<int>{posx, posy};
}

void Hand::set_priority(bool prim) {
    primary = prim;
}

void Hand::store_tile(int index) {

}

}
