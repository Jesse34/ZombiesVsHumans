cmake_minimum_required(VERSION 3.8)
project(ZombiesVsHumans)
set(CURSES_USE_NCURSES TRUE)
#find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        #Human.cpp
        #Human.h
        #Organism.cpp
        #Organism.h
        #World.cpp
        #World.h
        #Zombie.cpp
        #Zombie.h
        Human.cpp Human.h Organism.cpp Organism.h World.cpp World.h Zombie.cpp Zombie.h)
add_executable(ZombiesVsHumans ${SOURCE_FILES})

target_link_libraries(ZombiesVsHumans ${CURSES_LIBRARIES})

#cmake_minimum_required(VERSION 3.8)
#project(ZombiesVsHumans)
#
#set(CMAKE_CXX_STANDARD 11)
#
#set(SOURCE_FILES main.cpp)
#add_executable(ZombiesVsHumans ${SOURCE_FILES})