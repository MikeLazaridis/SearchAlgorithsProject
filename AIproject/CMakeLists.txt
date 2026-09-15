cmake_minimum_required(VERSION 3.30)
project(AIproject C)

set(CMAKE_C_STANDARD 99)

add_executable(AIproject
        main.c
        node.c
        bfs.c
        dfs.c
        best_first.c
        a_star.c
)
