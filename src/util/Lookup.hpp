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

inline std::unordered_map<automa::STATE, std::string> get_state_string {
    {automa::STATE::NONE,       "None"      },
    {automa::STATE::METAGRID,   "Metagrid"  },
    {automa::STATE::EDITOR,     "Editor"    }
};

inline std::unordered_map<tool::TOOL_TYPE, std::string> get_tool_string {
    {tool::TOOL_TYPE::BRUSH,      "Brush" },
    {tool::TOOL_TYPE::HAND,       "Hand"  },
    {tool::TOOL_TYPE::FILL,       "Fill"  },
    {tool::TOOL_TYPE::ERASE,       "Erase"  },
    {tool::TOOL_TYPE::SELECT,     "Select"}
};

inline std::unordered_map<tool::TOOL_TYPE, automa::TOOL_INDEX> get_tool_sprite_index {
    {tool::TOOL_TYPE::BRUSH,      automa::BRUSH },
    {tool::TOOL_TYPE::HAND,       automa::HAND  },
    {tool::TOOL_TYPE::FILL,       automa::FILL  },
    {tool::TOOL_TYPE::ERASE,      automa::ERASE },
    {tool::TOOL_TYPE::SELECT,     automa::SELECT}
};

inline std::unordered_map<int, canvas::STYLE> get_style {
    {-1,    canvas::STYLE::STYLE_NULL}  ,
    {0,     canvas::STYLE::FIRSTWIND    },
    {1,     canvas::STYLE::OVERTURNED   },
    {2,     canvas::STYLE::GRUB         },
    {3,     canvas::STYLE::TOXIC        },
    {4,     canvas::STYLE::BASE         },
    {5,     canvas::STYLE::FROZEN       },
    {6,     canvas::STYLE::NIGHT        },
    {7,     canvas::STYLE::WORM         },
    {8,     canvas::STYLE::SKY          },
    {9,     canvas::STYLE::ASH          },
    {10,    canvas::STYLE::GREATWING    },
    {11,    canvas::STYLE::ICE          },
    {12,    canvas::STYLE::SNOW         },
    {13,    canvas::STYLE::STONE        },
    {14,    canvas::STYLE::ABANDONED    },
    {15,    canvas::STYLE::ANCIENT      },
    {16,    canvas::STYLE::FACTORY      },
    {17,    canvas::STYLE::SHADOW       },
    {18,    canvas::STYLE::HOARDER      },
    {19,    canvas::STYLE::MANSION      }
};

inline std::unordered_map<int, canvas::BACKDROP> get_backdrop {
    {-1,    canvas::BACKDROP::BG_NULL       },
    {0,     canvas::BACKDROP::BG_SUNSET     },
    {1,     canvas::BACKDROP::BG_SUNRISE    },
    {2,     canvas::BACKDROP::BG_OPEN_SKY   },
    {3,     canvas::BACKDROP::BG_RED_SKY    },
    {4,     canvas::BACKDROP::BG_BLACK      }
};

}

