//
//  GameState.hpp
//  automa
//
//  Created by Alex Frasca on 12/26/22.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>
#include <memory>
#include <chrono>
#include <imgui.h>
#include "../canvas/Canvas.hpp"
#include "../util/ServiceLocator.hpp"
#include "../tool/Tool.hpp"
#include <SFML/OpenGL.hpp>
#include <imgui-SFML.h>

namespace automa {

//globals

enum class STATE {
    NONE,
    METAGRID,
    EDITOR
};

enum TOOL_INDEX {
    BRUSH = 0,
    FILL,
    SELECT,
    ERASE,
    HAND
};

class GameState {
    
public:
    
    using Time = std::chrono::duration<float>;
    
    GameState() = default;
    GameState(int id) {
        
    }
    GameState& operator=(GameState&&) = delete;
    
    template<typename T> class StateID;
    
    virtual void init(const std::string& load_path) {}
    virtual void setTilesetTexture(sf::Texture tile_texture) {}
    virtual void handle_events(sf::Event event, sf::RenderWindow& win) {}
    virtual void logic() {}
    virtual void render(sf::RenderWindow& win) {}
    virtual void gui_render(sf::RenderWindow& win) {}
    
    STATE state = STATE::NONE;
};

// =======================================================================
//
//    Metagrid
//
// =======================================================================

class Metagrid : public GameState {
public:
    
    
    Metagrid() {
        state = automa::STATE::METAGRID;
    };
    void init(const std::string& load_path) {
    }
    void setTilesetTexture(sf::Texture tile_texture) {
    }
    void handle_events(sf::Event event, sf::RenderWindow& win) {
        
        if (event.type == sf::Event::EventType::KeyPressed) {
        }
        
    }
    
    void logic() {}
    
    void render(sf::RenderWindow& win) {}
    
    void gui_render(sf::RenderWindow& win);
};

// =======================================================================
//
//    Editor
//
// =======================================================================

class Editor : public GameState {
public:
    
    const int TILE_WIDTH{32};
    const int NUM_TOOLS{5};
    
    Editor() {
        state = STATE::EDITOR;
    }
    void init(const std::string& load_path) {
        map.load(load_path + "/level/DOJO");
        tool_texture.loadFromFile(load_path + "/gui/tools.png");
        map.layers.at(canvas::MIDDLEGROUND).active = true;
        for(int i = 0; i < 5; i++) {
            tool_sprites.push_back(sf::Sprite());
            tool_sprites.back().setTexture(tool_texture);
            tool_sprites.back().setTextureRect(sf::IntRect({i * 32, 0}, {32, 32}));
        }
    }
    void setTilesetTexture(sf::Texture tile_texture) {
        tileset_texture = tile_texture;
        
        for(int i = 0; i < 16; ++i) {
            for(int j = 0; j < 16; ++j) {
                tileset.push_back(sf::Sprite());
                //do all tilesets in this loop
                tileset.back().setTexture(tileset_texture);
                tileset.back().setTextureRect(sf::IntRect({j * TILE_WIDTH, i * TILE_WIDTH}, {TILE_WIDTH, TILE_WIDTH}));
            }
        }
    }
    void handle_events(sf::Event event, sf::RenderWindow& win);
    
    void logic();
    
    void render(sf::RenderWindow& win);
    
    void gui_render(sf::RenderWindow& win);
    
    canvas::Canvas map{};
    sf::Texture tileset_texture{};
    std::vector<sf::Sprite> tileset{};
    
    sf::Texture tool_texture{};
    std::vector<sf::Sprite> tool_sprites{};
    
    bool mouse_held{};
    sf::Vector2<float> mouse_clicked_position{};
    
    bool slide_left{};
    bool slide_right{};
    bool slide_up{};
    bool slide_down{};
    
    bool show_grid{true};
    bool show_all_layers{true};
};



}

/* GameState_hpp */
