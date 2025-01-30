cmake_minimum_required(VERSION 3.14)

# Project Name and Version
project(Frodo VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)

# Define source files for the executable
set(EXECUTABLE_SOURCES src/main.cpp)

# Include FetchContent for SFML
# include(FetchContent)
# FetchContent_Declare(SFML
#     GIT_REPOSITORY https://github.com/SFML/SFML.git
#     # GIT_TAG 3.0.0  # Ensure you're using SFML 3.0.0
#     GIT_TAG 2.0.0  # Ensure you're using SFML 3.0.0
#     GIT_SHALLOW ON
#     SYSTEM)
# FetchContent_MakeAvailable(SFML)

find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${EXECUTABLE_SOURCES})

# Include project directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

# Link SFML libraries
target_link_libraries(GameLib PUBLIC sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE GameLib sfml-system sfml-window sfml-graphics sfml-audio)
# target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio SFML::Network GameLib)

# Enable debug symbols
target_compile_options(${PROJECT_NAME} PRIVATE -g)

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
