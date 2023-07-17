cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(testSimulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(hitsTest hitsTest.cpp ${sources} ${headers})
target_link_libraries(hitsTest ${Geant4_LIBRARIES})
add_custom_target(testSimulation DEPENDS hitsTest)
