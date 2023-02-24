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
    SELECT
};

class Tool {
public:
    
    Tool& operator=(const Tool&) = delete;
    virtual void handle_events(canvas::Canvas& canvas) = 0;
    virtual void update(int _x, int _y) = 0;
//    virtual void render() = 0;
//    virtual void render_with_layer_info(const canvas::Layer& layer);
    virtual void set_priority(bool prim) = 0;
//    virtual ~Tool() {};
    
    void set_size(int new_size);
    int get_size();
    
    int value = 0;
    bool active;
    
    sf::Vector2<float> position{};
    sf::Vector2<float> relative_position{};
    
    int xorigin;
    int yorigin;
    int tempx;
    int tempy;
    
    int size;
    
    bool primary;
    
    TOOL_TYPE type{};
    
};

class Hand : public Tool {
    
public:
    
    Hand() { type = TOOL_TYPE::HAND; }
    void handle_events(canvas::Canvas& canvas);
    void update(int _x, int _y);
    void set_priority(bool prim);
    
};

class Brush : public Tool {
    
public:
    
    Brush() { type = TOOL_TYPE::BRUSH; }
    void handle_events(canvas::Canvas& canvas);
    void update(int _x, int _y);
    void set_priority(bool prim);
    
private:
    
};

class Fill : public Tool {

public:
    
    Fill() { type = TOOL_TYPE::FILL; };
    void handle_events(canvas::Canvas& canvas);
    void update(int _x, int _y);
    void set_priority(bool prim);
    
    void fill_section(int prev_val, const int new_val, int i, int j, canvas::Canvas& canvas);
    
};

struct SelectBox {
    
    SelectBox() = default;
    SelectBox(int x_, int y_, int w_, int h_) {
        box_x = x_; box_y = y_; box_w = w_; box_h = h_;
    }
    void clear() {
        box_x = 0; box_y = 0; box_w = 0; box_h = 0;
    }
    void adjust(int w_, int h_) {
        box_w = w_;
        box_h = h_;
    }
    int box_x;
    int box_y;
    int box_h;
    int box_w;
};

class SelectionRectangular : public Tool {
    
public:
    
    SelectionRectangular() { type = TOOL_TYPE::SELECT; }
    void handle_events(canvas::Canvas& canvas);
    void update(int _x, int _y);
    void render_with_layer_info(const canvas::Layer& layer);
    void render_selection(const canvas::Layer& layer);
    void set_priority(bool prim);
    
private:
    
    SelectBox selection;
    canvas::Clipboard clipboard;
    
};

}
