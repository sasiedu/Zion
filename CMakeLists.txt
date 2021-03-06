cmake_minimum_required(VERSION 3.8)
project(game)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# Adding dependencies
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLFW3 REQUIRED glfw3)
pkg_search_module(ASSIMP REQUIRED assimp)
pkg_search_module(GLM REQUIRED glm)

include_directories(
        ${PROJECT_SOURCE_DIR}/Core/includes
        ${GLEW_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/Bomberman/include
)
link_directories(
        ${GLEW_LIBRARY_DIRS}
        ${GLFW3_LIBRARY_DIRS}
        ${ASSIMP_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
)

set(LIB_SOURCE_FILES Core/entities/window.cpp Core/entities/input.cpp Core/entities/shader.cpp Core/utils/file.cpp Core/sprite/squareSprite.cpp Core/entities/material.cpp Core/sprite/cubeSprite.cpp Core/entities/camera.cpp Core/render/renderer.cpp Core/models/gltf.cpp)

add_library(zion STATIC ${LIB_SOURCE_FILES})
if (APPLE)
    set(OPENGL_FLAGS "-framework OpenGL -framework GLUT -framework Cocoa -framework IOKit -framework CoreVideo")
endif()

set(SOURCE_FILES Game/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        ${GLM_LIBRARIES}
        zion
)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_FLAGS})
endif()

set(B_SOURCE_FILES Bomberman/main.cpp Bomberman/src/MainGame.cpp Bomberman/src/scene.cpp Bomberman/src/player.cpp)
add_executable(Bomberman ${B_SOURCE_FILES})
target_link_libraries(Bomberman
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        ${GLM_LIBRARIES}
        zion
        )
if (APPLE)
    target_link_libraries(Bomberman ${OPENGL_FLAGS})
endif()