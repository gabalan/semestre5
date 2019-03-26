cmake_minimum_required(VERSION 3.0)

project ("demo_sdl2" LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

option(LIBGAME_TEACHER "teacher version of libgame" ON)
if(LIBGAME_TEACHER)
  add_library(game game.o game_io.o) # les fichiers objet de notre version
else()
  add_library(game game.c game_io.c) # vos fichiers source
endif()
set_target_properties(game PROPERTIES LINKER_LANGUAGE C)

# pkg-config --list-all  | grep -i sdl2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMG REQUIRED SDL2_image)
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
set(SDL2_ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set(SDL2_ALL_INC ${SDL2_INCLUDE_DIRS} ${SDL2_IMG_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

include_directories(${SDL2_ALL_INC})
add_executable(demo main.c demo.c)
target_link_libraries(demo ${SDL2_ALL_LIBS} m)
add_executable(model main.c model.c)
target_link_libraries(model ${SDL2_ALL_LIBS} m)
