//
//  Lookup.hpp
//  Pioneer-Lab
//
//  Created by Alex Frasca on 9/28/20.
//

#pragma once

#include <stdio.h>
#include <string>
#include <unordered_map>
#include "../canvas/Tile.hpp"
#include "../automa/GameState.hpp"
#include "../util/ServiceLocator.hpp"

namespace lookup {

//inline std::unordered_map<canvas::TILE_TYPE, int> tile_type_lookup {
//    TILE_NULL,
//    TILE_BASIC,
//    TILE_RAMP,
//    TILE_LAVA,
//    TILE_CURRENT,
//    TILE_FLAMMABLE,
//    TILE_PLATFORM,
//    TILE_WATER,
//    TILE_BREAKABLE,
//    TILE_LADDER,
//    TILE_SPIKES,
//    TILE_ICY
//}

inline std::unordered_map<automa::STATE, std::string> get_state_string {
    {automa::STATE::NONE,       "None"      },
    {automa::STATE::METAGRID,   "Metagrid"  },
    {automa::STATE::EDITOR,     "Editor"    }
};

inline std::unordered_map<tool::TOOL_TYPE, std::string> get_tool_string {
    {tool::TOOL_TYPE::BRUSH,      "Brush" },
    {tool::TOOL_TYPE::HAND,       "Hand"  },
    {tool::TOOL_TYPE::FILL,       "Fill"  },
    {tool::TOOL_TYPE::SELECT,     "Select"}
};

}

