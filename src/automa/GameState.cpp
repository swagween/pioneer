//
//  GameState.cpp
//  automa
//
//  Created by Alex Frasca on 12/26/22.
//

#include "GameState.hpp"
#include "../util/Lookup.hpp"

void automa::Editor::init(const std::string &load_path) {
    map.load(load_path + "/level/DOJO");
    filepath = load_path + "/level/";
    tool_texture.loadFromFile(load_path + "/gui/tools.png");
    map.layers.at(canvas::MIDDLEGROUND).active = true;
    for(int i = 0; i < 5; i++) {
        tool_sprites.push_back(sf::Sprite());
        tool_sprites.back().setTexture(tool_texture);
        tool_sprites.back().setTextureRect(sf::IntRect({i * 32, 0}, {32, 32}));
    }
    for(int i = 0; i < canvas::NUM_STYLES; ++i) {
        const char* next = lookup::get_style_string.at(lookup::get_style.at(i));
        styles[i] = next;
    }
    for(int i = 0; i < canvas::NUM_STYLES; ++i) {
        tileset_textures.push_back(sf::Texture());
        std::string style = lookup::get_style_string.at(lookup::get_style.at(i));
        tileset_textures.back().loadFromFile(load_path + "/tile/" + style + "_tiles.png");
    }
    
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            tileset.push_back(sf::Sprite());
            //do all tilesets in this loop
            tileset.back().setTexture(tileset_textures.at(lookup::get_style_id.at(map.style)));
            tileset.back().setTextureRect(sf::IntRect({j * TILE_WIDTH, i * TILE_WIDTH}, {TILE_WIDTH, TILE_WIDTH}));
        }
    }
}

void automa::Editor::setTilesetTexture(sf::Texture& new_tex) {
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 16; ++j) {
            //do all tilesets in this loop
            tileset.at(j + i * 16).setTexture(new_tex);
            tileset.at(j + i * 16).setTextureRect(sf::IntRect({j * TILE_WIDTH, i * TILE_WIDTH}, {TILE_WIDTH, TILE_WIDTH}));
        }
    }
}


void automa::Editor::handle_events(sf::Event& event, sf::RenderWindow &win) {
    svc::current_tool.get()->ready = true;
    svc::secondary_tool.get()->ready = true;
    if(event.type == sf::Event::EventType::KeyPressed) {
        svc::current_tool.get()->ready = false;
        svc::secondary_tool.get()->ready = false;
        if (event.key.code == sf::Keyboard::W) {
            slide_up = true;
        }
        if (event.key.code == sf::Keyboard::A) {
            slide_left = true;
        }
        if (event.key.code == sf::Keyboard::S) {
            slide_down = true;
        }
        if (event.key.code == sf::Keyboard::D) {
            slide_right = true;
        }
        if (event.key.code == sf::Keyboard::C) {
            svc::current_tool.get()->handle_keyboard_events(map, event.key.code);
        }
        if (event.key.code == sf::Keyboard::V) {
            svc::current_tool.get()->handle_keyboard_events(map, event.key.code);
        }
    }
    if(event.type == sf::Event::EventType::KeyReleased) {
        svc::current_tool.get()->ready = false;
        svc::secondary_tool.get()->ready = false;
        if (event.key.code == sf::Keyboard::W) {
            slide_up = false;
        }
        if (event.key.code == sf::Keyboard::A) {
            slide_left = false;
        }
        if (event.key.code == sf::Keyboard::S) {
            slide_down = false;
        }
        if (event.key.code == sf::Keyboard::D) {
            slide_right = false;
        }
    }
    if(ImGui::IsAnyItemHovered()) { svc::current_tool.get()->ready = false; svc::secondary_tool.get()->ready = false; }
    if(ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) { svc::current_tool.get()->ready = false; svc::secondary_tool.get()->ready = false; };
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        svc::current_tool.get()->handle_events(map, event);
        svc::current_tool.get()->active = true;
    } else {
        svc::current_tool.get()->active = false;
        svc::current_tool.get()->just_clicked = true;
        svc::current_tool.get()->clicked_position = {0.0f, 0.0f};
        svc::current_tool.get()->scaled_clicked_position = {0, 0};
        svc::current_tool.get()->relative_position = {0.0f, 0.0f};
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        svc::secondary_tool.get()->handle_events(map, event);
        svc::secondary_tool.get()->active = true;
    } else {
        svc::secondary_tool.get()->active = false;
        svc::secondary_tool.get()->just_clicked = true;
        svc::secondary_tool.get()->clicked_position = {0.0f, 0.0f};
        svc::secondary_tool.get()->scaled_clicked_position = {0, 0};
        svc::secondary_tool.get()->relative_position = {0.0f, 0.0f};
    }
    //select tool gets special treatment, because it can be used without the mouse being pressed (copy/paste)
    if(svc::current_tool.get()->type == tool::TOOL_TYPE::SELECT) {
        svc::current_tool.get()->handle_events(map, event);
    }
}

void automa::Editor::logic() {
    svc::current_tool->update();
    svc::secondary_tool->update();
    if(slide_up)    { svc::cameraLocator.get().physics.velocity.y += 2;  }
    if(slide_down)  { svc::cameraLocator.get().physics.velocity.y += -2; }
    if(slide_left)  { svc::cameraLocator.get().physics.velocity.x += 2;  }
    if(slide_right) { svc::cameraLocator.get().physics.velocity.x += -2; }
    if(svc::current_tool.get()->type == tool::TOOL_TYPE::HAND &&
       svc::current_tool.get()->active) {
        svc::cameraLocator.get().physics.position += svc::current_tool.get()->relative_position;
        svc::cameraLocator.get().physics.velocity = {0.0f, 0.0f};
        svc::cameraLocator.get().physics.acceleration = {0.0f, 0.0f};
        svc::current_tool.get()->relative_position = {0.0f, 0.0f};
    }
    if(svc::secondary_tool.get()->type == tool::TOOL_TYPE::HAND &&
       svc::secondary_tool.get()->active) {
        svc::cameraLocator.get().physics.position += svc::secondary_tool.get()->relative_position;
        svc::cameraLocator.get().physics.velocity = {0.0f, 0.0f};
        svc::cameraLocator.get().physics.acceleration = {0.0f, 0.0f};
        svc::secondary_tool.get()->relative_position = {0.0f, 0.0f};
    }
    svc::cameraLocator.get().update();
}

void automa::Metagrid::gui_render(sf::RenderWindow& win) {
    bool* debug{};
    const float PAD = 10.0f;
    static int corner = 0;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 window_pos, window_pos_pivot;
    ImVec2 prev_window_pos{};
    ImVec2 prev_window_size{};
    window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
    window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
    window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
    window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    window_flags |= ImGuiWindowFlags_NoMove;
    
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Debug Mode", debug, window_flags)) {
        ImGui::Text("Pioneer (beta version 1.0.0) - Metagrid");
        ImGui::Separator();
        if (ImGui::IsMousePosValid()) {
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        } else {
            ImGui::Text("Mouse Position: <invalid>");
        }
        prev_window_size = ImGui::GetWindowSize();
        ImGui::End();
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    work_size = viewport->WorkSize;
    window_pos = {window_pos.x, window_pos.y + prev_window_size.y + PAD};
    window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    ImGui::SetNextWindowPos(window_pos);
    if (ImGui::Begin("Info", debug, window_flags)) {
        prev_window_size = ImGui::GetWindowSize();
        prev_window_pos = ImGui::GetWindowPos();
        
        ImGui::End();
    }
}

void automa::Editor::render(sf::RenderWindow &win) {
    sf::RectangleShape box{};
    sf::RectangleShape gridbox{};
    sf::RectangleShape target{};
    
    box.setOutlineColor(sf::Color{200, 200, 200, 20});
    box.setOutlineThickness(-2);
    box.setSize({canvas::CELL_SIZE, canvas::CELL_SIZE});
    
    gridbox.setFillColor(sf::Color::Transparent);
    gridbox.setOutlineColor(sf::Color{240, 230, 255, 20});
    gridbox.setOutlineThickness(-1);
    gridbox.setSize({canvas::CELL_SIZE, canvas::CELL_SIZE});
    
    target.setFillColor(sf::Color{110, 90, 200, 80});
    target.setOutlineColor(sf::Color{240, 230, 255, 100});
    target.setOutlineThickness(-2);
    target.setSize({canvas::CELL_SIZE, canvas::CELL_SIZE});
    
    for(auto& layer : map.layers) {
        box.setFillColor(sf::Color{static_cast<uint8_t>(layer.render_order * 30), 230, static_cast<uint8_t>(255 - layer.render_order * 30), 40});
        for(auto& cell : layer.grid.cells) {
            if(layer.render_order == svc::active_layer || show_all_layers) {
                tileset.at(cell.value).setPosition(cell.position.x + svc::cameraLocator.get().physics.position.x, cell.position.y + svc::cameraLocator.get().physics.position.y);
                win.draw(tileset.at(cell.value));
            } else {
                if(cell.value > 0) {
                    box.setPosition(cell.position.x + svc::cameraLocator.get().physics.position.x, cell.position.y + svc::cameraLocator.get().physics.position.y);
                    win.draw(box);
                }
            }
            if(show_grid && layer.render_order == canvas::NUM_LAYERS - 1) { //only do this once, at the end
                gridbox.setPosition(cell.position.x + svc::cameraLocator.get().physics.position.x, cell.position.y + svc::cameraLocator.get().physics.position.y);
                win.draw(gridbox);
            }
        }
    }
    if(svc::current_tool.get()->ready && svc::current_tool.get()->in_bounds(map.dimensions) &&
       (svc::current_tool.get()->type == tool::TOOL_TYPE::BRUSH ||
       svc::current_tool.get()->type == tool::TOOL_TYPE::FILL ||
       svc::current_tool.get()->type == tool::TOOL_TYPE::ERASE)) {
        for(int i = 0; i < svc::current_tool.get()->size; i++) {
            for(int j = 0; j < svc::current_tool.get()->size; j++) {
                target.setPosition((svc::current_tool.get()->scaled_position.x - i) * canvas::CELL_SIZE + svc::cameraLocator.get().physics.position.x, (svc::current_tool.get()->scaled_position.y - j) * canvas::CELL_SIZE + svc::cameraLocator.get().physics.position.y);
                win.draw(target);
            }
        }
    }
    float tool_x = svc::current_tool.get()->position.x + svc::cameraLocator.get().physics.position.x;
    float tool_y = svc::current_tool.get()->position.y + svc::cameraLocator.get().physics.position.y;
    tool_sprites.at(lookup::get_tool_sprite_index.at(svc::current_tool.get()->type)).setPosition(tool_x, tool_y);
    win.draw(tool_sprites.at(lookup::get_tool_sprite_index.at(svc::current_tool.get()->type)));
}

void automa::Editor::gui_render(sf::RenderWindow& win) {
    bool* debug{};
    const float PAD = 10.0f;
    static int corner = 0;
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 2.0;
    
    svc::current_tool.get()->position = sf::Vector2<float>{io.MousePos.x, io.MousePos.y} - svc::cameraLocator.get().physics.position;
    svc::secondary_tool.get()->position = sf::Vector2<float>{io.MousePos.x, io.MousePos.y} - svc::cameraLocator.get().physics.position;
    
    //Main Menu
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if(ImGui::Button("New")) {
                ImGui::OpenPopup("New File");
            }
            // Always center this window when appearing
            ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("New File", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Choose a region:");
                // Testing behavior of widgets stacking their own regular popups over the modal.
                static int item = 1;;
                ImGui::Combo("Region", &item, styles, IM_ARRAYSIZE(styles));
                ImGui::Text("Please enter a file name:");
                char buffer{};
                ImGui::InputTextWithHint("File Name", "level_01", &buffer, (size_t)32);
                ImGui::Separator();
               
                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::SameLine();
                if (ImGui::Button("Create")) {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
            if(ImGui::Button("Open")) {}
            if(ImGui::Button("Save")) {
                ImGui::OpenPopup("Save");
            }
            if (ImGui::BeginPopupModal("Save", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Please enter a folder name:");
                static char buffer[128] = "";
                
                ImGui::InputTextWithHint("Folder Name", "level_01", buffer, IM_ARRAYSIZE(buffer));
                ImGui::Separator();
               
                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::SameLine();
                if (ImGui::Button("Create")) {
                    std::string savepath = filepath + buffer;
                    map.save(savepath);
                    ImGui::CloseCurrentPopup();
                }
                
                ImGui::TextUnformatted(buffer);
                
                ImGui::EndPopup();
            }
            if (ImGui::BeginPopupModal("Notice", NULL, ImGuiWindowFlags_Modal)) {
                ImGui::Text("File saved successfully.");
                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
            if (ImGui::BeginPopupModal("Notice: Error", NULL, ImGuiWindowFlags_Modal)) {
                ImGui::Text("ERROR: File failed to save.");
                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
            ImGui::EndMenu();
        }
        //none of the below have been implemented and will likely be removed
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 window_pos, window_pos_pivot;
    ImVec2 prev_window_pos{};
    ImVec2 prev_window_size{};
    window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
    window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
    window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
    window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    window_flags |= ImGuiWindowFlags_NoMove;
    
    
    
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Debug Mode", debug, window_flags)) {
        ImGui::Text("Pioneer (beta version 1.0.0) - Level Editor");
        ImGui::Separator();
        if (ImGui::IsMousePosValid()) {
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        } else {
            ImGui::Text("Mouse Position: <invalid>");
        }
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("General"))
            {
                ImGui::Text("Camera Position: (%.1f,%.1f)", svc::cameraLocator.get().physics.position.x, svc::cameraLocator.get().physics.position.y);
                ImGui::Text("Active Layer: %i", svc::active_layer);
                ImGui::Text("Num Layers: %lu", map.layers.size());
                ImGui::Text("Stored Tile Value: %u", svc::current_tool.get()->tile);
                if(svc::current_tool.get()->in_bounds(map.dimensions)) {
                    ImGui::Text("Tile Value at Mouse Pos: %u", map.tile_val_at(svc::current_tool.get()->scaled_position.x, svc::current_tool.get()->scaled_position.y, svc::active_layer));
                }
                ImGui::Separator();
                ImGui::Text("Current State: %s", lookup::get_state_string.at(state).c_str());
                ImGui::Text("Current Style: %s", lookup::get_style_string.at(map.style));
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Tool"))
            {
                ImGui::Text("Tool Position: (%.1f,%.1f)", svc::current_tool.get()->position.x, svc::current_tool.get()->position.y);
                ImGui::Text("Clicked Position: (%.1f,%.1f)", svc::current_tool.get()->clicked_position.x, svc::current_tool.get()->clicked_position.y);
                ImGui::Text("Relative Position: (%.1f,%.1f)", svc::current_tool.get()->relative_position.x, svc::current_tool.get()->relative_position.y);
                ImGui::Text("Tool Position (scaled): (%i,%i)", svc::current_tool.get()->scaled_position.x, svc::current_tool.get()->scaled_position.y);
                ImGui::Text("Tool Clicked Position (scaled): (%i,%i)", svc::current_tool.get()->scaled_clicked_position.x, svc::current_tool.get()->scaled_clicked_position.y);
                ImGui::Text("Tool in Bounds: "); ImGui::SameLine();
                if(svc::current_tool.get()->in_bounds(map.dimensions)) { ImGui::Text("Yes"); } else { ImGui::Text("No"); };
                ImGui::Text("Tool Ready: "); ImGui::SameLine();
                if(svc::current_tool.get()->ready) { ImGui::Text("Yes"); } else { ImGui::Text("No"); };
                ImGui::Text("Tool Active: "); ImGui::SameLine();
                if(svc::current_tool.get()->active) { ImGui::Text("Yes"); } else { ImGui::Text("No"); };
                
                ImGui::Text("Current Tool: %s", lookup::get_tool_string.at(svc::current_tool->type).c_str());
                ImGui::Text("Secondary Tool: %s", lookup::get_tool_string.at(svc::secondary_tool->type).c_str());
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Resources"))
            {
                ImGui::Text("Size of Canvas (Bytes): %lu", sizeof(map));
                ImGui::Text("Size of Tileset (Bytes): %lu", sizeof(tileset_textures));
                ImGui::Text("Size of Tileset Spritesheet (Bytes): %lu", sizeof(tileset));
                ImGui::Text("Size of Filepath (Bytes): %lu", sizeof(filepath));
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        
        prev_window_size = ImGui::GetWindowSize();
        ImGui::End();
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    work_size = viewport->WorkSize;
    window_pos = {window_pos.x, window_pos.y + prev_window_size.y + PAD};
    window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
    ImGui::SetNextWindowPos(window_pos);
    if (ImGui::Begin("Tile Palette", debug, window_flags)) {
        prev_window_size = ImGui::GetWindowSize();
        prev_window_pos = ImGui::GetWindowPos();
        for(int i = 0; i < 64; i++) {
            for(int j = 0; j < 4; j++) {
                ImGui::PushID(j + i * 4);
                if(ImGui::ImageButton(tileset.at(j + i * 4), 2)) {
                    svc::current_tool.get()->store_tile(j + i * 4);
                }
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }
        ImGui::End();
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    work_size = viewport->WorkSize;
    window_pos.x = work_pos.x + work_size.x - PAD;
    window_pos.y = work_pos.y + PAD;
    window_pos_pivot.x = 1.0f;
    window_pos_pivot.y = 0.0f;
    window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    if (ImGui::Begin("Settings", debug, window_flags)) {
        ImGui::Text("Toolbar");
        ImGui::Separator();
        ImGui::Text("Tools");
        for(int i = 0; i < NUM_TOOLS; i++) {
            ImGui::PushID(i);
            if(ImGui::ImageButton(tool_sprites.at(i), 2)) {
                switch(i) {
                    case BRUSH:
                        svc::current_tool = std::move(std::make_unique<tool::Brush>());
                        break;
                    case FILL:
                        svc::current_tool = std::move(std::make_unique<tool::Fill>());
                        break;
                    case SELECT:
                        svc::current_tool = std::move(std::make_unique<tool::SelectionRectangular>());
                        break;
                    case ERASE:
                        svc::current_tool = std::move(std::make_unique<tool::Erase>());
                        break;
                    case HAND:
                        svc::current_tool = std::move(std::make_unique<tool::Hand>());
                        break;
                    default:
                        svc::current_tool = std::move(std::make_unique<tool::Hand>());
                        break;
                }
            }
            ImGui::PopID();
            ImGui::SameLine();
        }
        ImGui::Separator();
        ImGui::Text("Brush Size");
        ImGui::SliderInt("##brushsz", &svc::current_tool.get()->size, 1, 16);
        ImGui::Separator();
        ImGui::Text("Settings");
        ImGui::Checkbox("Show Grid", &show_grid);
        ImGui::Checkbox("Show All Layers", &show_all_layers);
        ImGui::Text("Active Layer: ");
        ImGui::SliderInt("##activelr", &svc::active_layer, 0, 7);
        ImGui::Text("Scene Style: ");
        static int style_current = lookup::get_style_id.at(map.style);
        if(ImGui::Combo("##scenestyle", &style_current, styles, IM_ARRAYSIZE(styles))) {
            map.style = lookup::get_style.at(style_current);
            setTilesetTexture(tileset_textures.at(style_current));
        }
        prev_window_size = ImGui::GetWindowSize();
        prev_window_pos = ImGui::GetWindowPos();
        ImGui::End();
    }
    
}
