cmake_minimum_required(VERSION 3.16)
project(CS202-Project LANGUAGES CXX)

set(BUILD_SHARED_LIBS OFF)
set(TGUI_BACKEND SFML_GRAPHICS)
set(TGUI_BUILD_GUI_BUILDER ON)
set(TGUI_SHARED_LIBS OFF)
set(SFML_DIR ${CMAKE_BINARY_DIR}/_deps/sfml-build/SFMLConfig.cmake)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(TGUI
    GIT_REPOSITORY https://github.com/texus/TGUI.git
    GIT_TAG 0.10)
FetchContent_MakeAvailable(TGUI)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio TGUI::TGUI)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(${PROJECT_NAME} PROPERTIES
    XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/openal32.dll
        ${CMAKE_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME})
