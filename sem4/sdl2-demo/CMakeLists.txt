cmake_minimum_required(VERSION 3.0)
#NOM DU PROJET
project ("demo_sdl2" LANGUAGES C)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
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

 set(HEADERS
          game.h
           game_io.h
         )
   set(SRCS

          solver.c

         )


#LES EXECUTABLES
add_library(game game.c game_io.c )
SET_TARGET_PROPERTIES(game PROPERTIES LINKER_LANGUAGE C)
add_executable(testAM testAM.c game.c  game_io.c)
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

