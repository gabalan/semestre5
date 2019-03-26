cmake_minimum_required(VERSION 3.0)

project ("undead_sdl2" LANGUAGES C)
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
add_executable(undead_sdl2 main.c undead_sdl2.c game.o game_io.o)
target_link_libraries(undead_sdl2 ${SDL2_ALL_LIBS} m)


#LES EXECUTABLES
SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE C)
add_executable(testAM testAM.c game.c  game_io.c)
add_executable(foo foo.c game.c  game_io.c)
add_executable(undead_solve solver.c game.c game_io.c)
add_executable(testSAM testSAM.c game.c game_io.c)
add_executable(testSEY testSEY.c game.c game_io.c)
add_executable(test_DIAK test_DIAK.c game.c game_io.c)

target_link_libraries(testAM game)
target_link_libraries(testSAM game)
target_link_libraries(testSEY game)
target_link_libraries(test_DIAK game)
target_link_libraries(undead_solve game)

enable_testing()
include(CTest)

add_test(test1 ./testAM)
add_test(test2 ./testSAM)
add_test(test3 ./testSEY)
add_test(test4 ./test_DIAK)

cmake_minimum_required(VERSION 2.6)
