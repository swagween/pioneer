//
//  main.cpp
//  pioneer
//

#include <SFML/Graphics.hpp>
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

sf::Color PIONEER_BLUE = sf::Color(85, 173, 232);

static void show_overlay(bool* debug) {
    const float PAD = 10.0f;
    static int corner = 0;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (corner != -1) {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Debug Mode", debug, window_flags)) {
        ImGui::Text("Debug Window\n" "(right-click to change position)");
        ImGui::Separator();
        if (ImGui::IsMousePosValid()) {
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        } else {
            ImGui::Text("Mouse Position: <invalid>");
        }
    }
    ImGui::End();
}

const sf::Vector2<uint32_t> aspect_ratio { 3840, 2160 };
const sf::Vector2<uint32_t> screen_dimensions { aspect_ratio.x / 4, aspect_ratio.y / 4 };
const int TIME_STEP_MILLI = 100;

float G = 0.8f;

void run(char** argv) {
    
    //load textures
    std::string resource_path = find_resources(argv[0]);
    
    
    bool debug_mode = false;
    //init clock
    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::duration<float>;
    auto elapsed_time = Time{};
    auto time_step = Time{std::chrono::milliseconds(TIME_STEP_MILLI)}; //FPS
    //some SFML variables for drawing a basic window + background
    auto window = sf::RenderWindow{sf::VideoMode{screen_dimensions.x, screen_dimensions.y}, "Pioneer v1.0"};
    ImGui::SFML::Init(window);
    
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape background{};
    background.setSize(static_cast<sf::Vector2<float> >(screen_dimensions));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(20, 20, 30));
    
    
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
                    return;
                case sf::Event::KeyPressed:
                    //player can refresh grid by pressing 'Z'
                    if(event.key.code == sf::Keyboard::Escape) {
                        return;
                    }
                    if(event.key.code == sf::Keyboard::D) {
                        debug_mode = !debug_mode;
                    }
                    break;
                default:
                    break;
            }
        }
        
        //game logic and rendering
        if(elapsed_time > time_step) {
            
        }
        
        //ImGui update
        ImGui::SFML::Update(window, deltaClock.restart());
        
        //ImGui stuff
        show_overlay(&debug_mode);
        
        //my renders
        window.clear();
        window.draw(background);
        
        
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


