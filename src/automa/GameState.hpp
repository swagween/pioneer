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
    
    void gui_render(sf::RenderWindow& win) {
        ImGui::Text("ImGui in Metagrid");
    }
};

// =======================================================================
//
//    Editor
//
// =======================================================================

class Editor : public GameState {
public:
    
    const int TILE_WIDTH = 32;
    
    Editor() {
        state = STATE::EDITOR;
    }
    void init(const std::string& load_path) {
        map.load(load_path);
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
    void handle_events(sf::Event event, sf::RenderWindow& win) {
        if(event.type == sf::Event::EventType::KeyPressed) {
            if (event.key.code == sf::Keyboard::H) {
            }
        }
        if(event.type == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mouse_held = true;
            mouse_clicked_position = static_cast<sf::Vector2<float>>(sf::Mouse::getPosition());
        } else {
            mouse_held = false;
        }
    }
    
    void logic() {
        if(mouse_held) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition();
            sf::Vector2<float> m_pos = {(float)mouse_pos.x, (float)mouse_pos.y};
            sf::Vector2<float> mouse_diff = m_pos - mouse_clicked_position;
            svc::cameraLocator.get().move(mouse_diff);
        }
        svc::cameraLocator.get().update();
    }
    
    void render(sf::RenderWindow& win) {
        for(auto& layer : map.layers) {
            for(auto& cell : layer.grid.cells) {
                if(layer.collidable) {
                    tileset.at(cell.value).setPosition(cell.position.x + svc::cameraLocator.get().physics.position.x, cell.position.y + svc::cameraLocator.get().physics.position.y);
                    win.draw(tileset.at(cell.value));
                }
            }
        }
    }
    
    void gui_render(sf::RenderWindow& win);
    
    canvas::Canvas map{{48, 32}};
    sf::Texture tileset_texture{};
    ImTextureID tileset_tex_id{};
    std::vector<sf::Sprite> tileset{};
    
    bool mouse_held{};
    sf::Vector2<float> mouse_clicked_position{};
    
};



}

/* GameState_hpp */
