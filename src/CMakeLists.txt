cmake_minimum_required(VERSION 3.11)
project(pioneer)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

target_sources(${PROJECT_NAME} PRIVATE

        main.cpp
	automa/GameState.hpp
	automa/GameState.cpp
	automa/StateManager.hpp
	automa/StateManager.cpp
	canvas/Canvas.hpp
	canvas/Canvas.cpp
	canvas/Layer.hpp
	canvas/Layer.cpp
	canvas/Tile.hpp
	canvas/Tile.cpp
	canvas/Clipboard.hpp
	canvas/Clipboard.cpp
 canvas/Grid.hpp
 canvas/Grid.cpp
	tool/Tool.hpp
	tool/Tool.cpp
	tool/Brush.hpp
	tool/Brush.cpp
	tool/Hand.hpp
	tool/Hand.cpp
	tool/Fill.hpp
	tool/Fill.cpp
    tool/Erase.cpp
	tool/SelectionRectangular.hpp
	tool/SelectionRectangular.cpp
        util/Lookup.hpp
        util/Camera.hpp
        util/PhysicsComponent.hpp
        util/Service.hpp
        util/ServiceLocator.hpp

)

# Copy DLLs needed for runtime on Windows
if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  endif()
endif()
