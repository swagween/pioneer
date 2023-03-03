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
#include <sstream>

namespace automa {

inline const char* styles[canvas::NUM_STYLES];
inline std::string_view const& style_list{};
inline std::string styles_str{};

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
    virtual void handle_events(sf::Event& event, sf::RenderWindow& win) {}
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
    void handle_events(sf::Event& event, sf::RenderWindow& win) {
        
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
    
    void init(const std::string& load_path);
    
    void setTilesetTexture(sf::Texture& new_tex);
    
    void handle_events(sf::Event& event, sf::RenderWindow& win);
    
    void logic();
    
    void render(sf::RenderWindow& win);
    
    void gui_render(sf::RenderWindow& win);
    
    canvas::Canvas map{};
    std::vector<sf::Texture> tileset_textures{};
    std::vector<sf::Sprite> tileset{};
    sf::Texture tool_texture{};
    std::vector<sf::Sprite> tool_sprites{};
    
    sf::Vector2<float> mouse_clicked_position{};
    
    bool mouse_held{};
    
    bool show_grid{true};
    bool show_all_layers{true};
    bool show_overlay{false};
    
    std::string filepath{};
    
    sf::RectangleShape box{};
    sf::RectangleShape gridbox{};
    sf::RectangleShape target{};
    sf::RectangleShape backdrop{};
};



}

/* GameState_hpp */
