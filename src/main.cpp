//
//  main.cpp
//  pioneer
//

#include <SFML/Graphics.hpp>
#include "automa/StateManager.hpp"
#include "util/Lookup.hpp"
#include "util/ServiceLocator.hpp"
#include <iostream>
#include <chrono>

#include <imgui-SFML.h>
#include <imgui.h>
#include <random>

#include <filesystem>

namespace fs = std::filesystem;

fs::path find_resources(fs::path exe) {
    auto check = [](fs::path const& prefix) {
        auto path = prefix / "resources";
        if (fs::is_directory(path)) { return path; }
        return fs::path{};
    };
    while (!exe.empty()) {
        if (auto ret = check(exe); !ret.empty()) { return ret; }
        auto parent = exe.parent_path();
        if (exe == parent) { break; }
        exe = std::move(parent);
    }
    return {};
}

namespace {

auto SM = automa::StateManager{};
auto window = sf::RenderWindow();

sf::Color PIONEER_BLUE = sf::Color(85, 173, 232);

std::string state{};

static void show_overlay(bool* debug) {
    
    SM.get_current_state().gui_render(window);
    
    
}

const int TIME_STEP_MILLI = 100;

float G = 0.8f;

void run(char** argv) {
    
    //load textures
    std::string resource_path = find_resources(argv[0]);
    const int TILE_WIDTH = 32;
    
    //load the tilesets!
    sf::Texture t_tiles_provisional{};
    sf::Texture t_tiles_overturned{};
    sf::Texture t_tiles_ash{};
    sf::Texture t_tiles_shadow{};
    sf::Texture t_tiles_hoarder{};
    sf::Texture t_tiles_abandoned{};
    t_tiles_provisional.loadFromFile(resource_path + "/tile/provisional_tiles.png");
    t_tiles_shadow.loadFromFile(resource_path + "/tile/shadow_tiles.png");
    t_tiles_ash.loadFromFile(resource_path + "/tile/ash_tiles.png");
    t_tiles_hoarder.loadFromFile(resource_path + "/tile/hoarder_tiles.png");
    
    std::vector<sf::Sprite> sp_tileset_provisional{};
    std::vector<sf::Sprite> sp_tileset_shadow{};
    std::vector<sf::Sprite> sp_tileset_abandoned{};
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            sp_tileset_provisional.push_back(sf::Sprite());
            sp_tileset_shadow.push_back(sf::Sprite());
            //do all tilesets in this loop
            sp_tileset_provisional.back().setTexture(t_tiles_provisional);
            sp_tileset_shadow.back().setTexture(t_tiles_shadow);
            sp_tileset_provisional.back().setTextureRect(sf::IntRect({j * TILE_WIDTH, i * TILE_WIDTH}, {TILE_WIDTH, TILE_WIDTH}));
            sp_tileset_shadow.back().setTextureRect(sf::IntRect({j * TILE_WIDTH, i * TILE_WIDTH}, {TILE_WIDTH, TILE_WIDTH}));
        }
    }
    
    SM.set_current_state(std::make_unique<automa::Metagrid>());
    
    
    bool debug_mode = false;
    //init clock
    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::duration<float>;
    auto elapsed_time = Time{};
    auto time_step = Time{std::chrono::milliseconds(TIME_STEP_MILLI)}; //FPS
    //some SFML variables for drawing a basic window + background
    window.create(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "Pioneer (beta v1.0)");
    ImGui::SFML::Init(window);
    
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape background{};
    background.setSize(static_cast<sf::Vector2<float> >(screen_dimensions));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(40, 60, 80));
    
    
    //game loop
    sf::Clock deltaClock{};
    auto start = Clock::now();
    int frame{};
    while (window.isOpen()) {
        frame++;
        auto now = Clock::now();
        auto dt = Time{now - start};
        start = now;
        elapsed_time += dt;
        
        //SFML event variable
        auto event = sf::Event{};
        //check window events
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            switch(event.type) {
                case sf::Event::Closed:
                    lookup::get_state_string.clear();
                    return;
                case sf::Event::KeyPressed:
                    //player can refresh grid by pressing 'Z'
                    if(event.key.code == sf::Keyboard::Escape) {
                        return;
                    }
                    if(event.key.code == sf::Keyboard::D) {
                        debug_mode = !debug_mode;
                    }
                    if(event.key.code == sf::Keyboard::Num1) {
                        svc::current_tool = std::move(std::make_unique<tool::Hand>());
                    }
                    if(event.key.code == sf::Keyboard::Num2) {
                        svc::current_tool = std::move(std::make_unique<tool::Brush>());
                    }
                    if(event.key.code == sf::Keyboard::Num3) {
                        svc::current_tool = std::move(std::make_unique<tool::Fill>());
                    }
                    if(event.key.code == sf::Keyboard::Num4) {
                        svc::current_tool = std::move(std::make_unique<tool::SelectionRectangular>());
                    }
                    if(event.key.code == sf::Keyboard::Enter) {
                        SM.set_current_state(std::make_unique<automa::Editor>());
                        SM.get_current_state().init(resource_path);
                        SM.get_current_state().setTilesetTexture(t_tiles_shadow);
                    }
                    if(event.key.code == sf::Keyboard::Equal) {
                        SM.set_current_state(std::make_unique<automa::Metagrid>());
                    }
                    break;
                default:
                    break;
            }
            SM.get_current_state().handle_events(event, window);
        }
        
        //game logic and rendering
        if(elapsed_time > time_step) {
            SM.get_current_state().logic();
        }
        
        //ImGui update
        ImGui::SFML::Update(window, deltaClock.restart());
        
        //ImGui stuff
        show_overlay(&debug_mode);
        ImGui::ShowDemoWindow();
        
        //my renders
        window.clear();
        window.draw(background);
        
        SM.get_current_state().render(window);
//        sp_tileset_provisional.at(1).setPosition(100, 100);
//        window.draw(sp_tileset_provisional.at(1));
        
        //draw canvas here
        
        
        ImGui::SFML::Render(window);
        window.display();
    }
    
}

} //end namespace

int main(int argc, char** argv) {
    assert(argc > 0);
    run(argv);
    ImGui::SFML::Shutdown();
    return 0;
}


