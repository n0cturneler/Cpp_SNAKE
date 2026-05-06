# CMakeList.txt : CMake project for CMAKE_THREE, include source and define
# project specific logic here.

# Add source to this project's executable.
add_executable (main  "main.cpp"  )

# Link SFML
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(main PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)

# Link IMGUI-SFML
find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)

# Link RMlUi
find_package(RmlUi CONFIG REQUIRED)
target_link_libraries(main PRIVATE RmlUi::RmlUi)

# SOL2 Lua Wrapper, this is heuristically generated, and may not be correct, sol2 lib
find_package(sol2 CONFIG REQUIRED)
target_link_libraries(main PRIVATE sol2::sol2)

# Include headers from libs/lib
target_include_directories (main PRIVATE
	${CMAKE_SOURCE_DIR}/libs/include
)

# Include libraries from libs/lib
# target_link_directories (main PRIVATE
#	${CMAKE_SOURCE_DIR}/libs/lib
# )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 23)
endif()

