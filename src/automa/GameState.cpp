//
//  GameState.cpp
//  automa
//
//  Created by Alex Frasca on 12/26/22.
//

#include "GameState.hpp"
#include "../util/Lookup.hpp"


void automa::Editor::gui_render(sf::RenderWindow& win) {
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
        ImGui::Text("Pioneer (beta version 1.0.0) - A fornani level editor");
        ImGui::Separator();
        if (ImGui::IsMousePosValid()) {
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        } else {
            ImGui::Text("Mouse Position: <invalid>");
        }
        ImGui::Separator();
        ImGui::Text("Current State: ");
        ImGui::SameLine();
        ImGui::TextUnformatted(lookup::get_state_string.at(state).c_str());
        ImGui::Text("Current Tool: ");
        ImGui::SameLine();
        ImGui::TextUnformatted(lookup::get_tool_string.at(svc::current_tool->type).c_str());
        prev_window_size = ImGui::GetWindowSize();
        ImGui::End();
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    work_size = viewport->WorkSize;
    window_pos = {window_pos.x, window_pos.y + prev_window_size.y + PAD};
    window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
    ImGui::SetNextWindowPos(window_pos);
    if (ImGui::Begin("Tile Palette", debug, window_flags)) {
        ImGui::Separator(); ImGui::Separator();
        prev_window_size = ImGui::GetWindowSize();
        prev_window_pos = ImGui::GetWindowPos();
        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                ImGui::ImageButton(tileset.at(j + i * 16), 2);
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }
        ImGui::End();
    }
    
    for(auto& sprite : tileset) {
        sprite.setPosition(window_pos.x, window_pos.y);
        win.draw(sprite);
    }
    
}
