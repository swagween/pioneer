//
//  AssetManager.hpp
//
//  Created by Alex Frasca on 12/26/22.
//

#pragma once


#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include "Service.hpp"

#include "Camera.hpp"
#include "../tool/Tool.hpp"

namespace svc {

inline auto cameraLocator = Service<Camera>::Instance{};
inline std::unique_ptr<tool::Tool> current_tool = std::make_unique<tool::Hand>();

}

/* ServiceLocator_hpp */
