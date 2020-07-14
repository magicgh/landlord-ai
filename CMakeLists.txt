cmake_minimum_required(VERSION 3.16)
project(Landlord_AI)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)
<<<<<<< HEAD
add_executable(Landlord_AI ${DIR_SRCS} include/shape.h src/shape.cpp include/game.h src/game.cpp include/constant.h include/scene.h src/scene.cpp)
target_link_libraries(Landlord_AI -lgraphics64 -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lgdiplus)
=======
add_executable(Landlord_AI ${DIR_SRCS})
target_link_libraries(Landlord_AI -lgraphics64 -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lgdiplus)
>>>>>>> f15c3b2 (pressed)
