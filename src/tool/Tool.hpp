//
//  Tool.hpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 10/3/20.
//

#pragma once

#include <stdio.h>
#include "../canvas/Canvas.hpp"
#include "../canvas/Clipboard.hpp"

namespace tool {

enum class TOOL_TYPE {
    BRUSH,
    HAND,
    FILL,
    SELECT,
    ERASE
};

class Tool {
public:
    
    Tool& operator=(const Tool&) = delete;
    virtual void handle_events(canvas::Canvas& canvas, sf::Event e) = 0;
    virtual void update() = 0;
//    virtual void render() = 0;
//    virtual void render_with_layer_info(const canvas::Layer& layer);
    virtual void set_priority(bool prim) = 0;
    virtual void store_tile(int index) = 0;
    
    bool in_bounds(sf::Vector2<float>& bounds);
    
    void set_size(int new_size);
    int get_size();
    
    int value = 0;
    bool active{};
    bool ready{};
    bool just_clicked = true;
    
    sf::Vector2<float> position{};
    sf::Vector2<float> clicked_position{};
    sf::Vector2<float> relative_position{};
    sf::Vector2<int> scaled_position{};
    
    int xorigin;
    int yorigin;
    int tempx;
    int tempy;
    
    int size = 1;
    
    bool primary{};
    uint16_t tile{};
    
    TOOL_TYPE type{};
    
};

class Hand : public Tool {
public:
    Hand() { type = TOOL_TYPE::HAND; }
    void handle_events(canvas::Canvas& canvas, sf::Event e);
    void update();
    void set_priority(bool prim);
    void store_tile(int index);
};

class Brush : public Tool {
public:
    Brush() { type = TOOL_TYPE::BRUSH; }
    void handle_events(canvas::Canvas& canvas, sf::Event e);
    void update();
    void set_priority(bool prim);
    void store_tile(int index);
    
private:
};

class Erase : public Tool {
public:
    Erase() { type = TOOL_TYPE::ERASE; }
    void handle_events(canvas::Canvas& canvas, sf::Event e);
    void update();
    void set_priority(bool prim);
    void store_tile(int index);
    
private:
};

class Fill : public Tool {
public:
    Fill() { type = TOOL_TYPE::FILL; };
    void handle_events(canvas::Canvas& canvas, sf::Event e);
    void update();
    void set_priority(bool prim);
    void store_tile(int index);
    
    void fill_section(int prev_val, const int new_val, int i, int j, canvas::Canvas& canvas);
    uint16_t tile{};
};

struct SelectBox {
    SelectBox() = default;
    SelectBox(sf::Vector2<uint16_t> pos, sf::Vector2<uint16_t> dim) : position(pos), dimensions(dim) {}
    void clear() { position = {0, 0}; dimensions = {0, 0}; }
    void adjust(sf::Vector2<uint16_t> adjustment) { dimensions += adjustment; }
    sf::Vector2<uint16_t> position{};
    sf::Vector2<uint16_t> dimensions{};
};

class SelectionRectangular : public Tool {
public:
    
    SelectionRectangular() { type = TOOL_TYPE::SELECT; }
    void handle_events(canvas::Canvas& canvas, sf::Event e);
    void update();
    void render_with_layer_info(const canvas::Layer& layer);
    void render_selection(const canvas::Layer& layer);
    void set_priority(bool prim);
    void store_tile(int index);
    
private:
    
    SelectBox selection{};
    canvas::Clipboard clipboard{};
    
};

}
