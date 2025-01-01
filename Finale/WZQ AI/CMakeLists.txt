cmake_minimum_required(VERSION 3.28)


project(WZQ_AI)


set(EasyX_INC D:\\storage\\EasyX\\include)
set(EasyX_LINK D:\\storage\\EasyX\\lib\\VC2015\\x64)
include_directories(${EasyX_INC})
link_directories(${EasyX_LINK})


link_libraries(EasyXa)
link_libraries(EasyXw)
set(CMAKE_CXX_STANDARD 17)

add_executable(WZQ_AI main.cpp CHESS_GAME/CHESS_GAME_SOURCE.cpp AI/Max-Min_Search/Max-Min_Search.cpp
        INSTANT_SEARCH.cpp
        AI_SEARCH.cpp
        AI/Max-Min_Search/Zorbists.cpp
        AI/Max-Min_Search/Zorbists.h
        AI/Max-Min_Search/WITHAI_SEARCH.cpp
        AI/Max-Min_Search/WITHAI_SEARCH.h
)
