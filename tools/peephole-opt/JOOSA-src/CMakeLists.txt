cmake_minimum_required(VERSION 3.7)
project(JOOSA_src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        code.c
        code.h
        defasn.c
        defasn.h
        emit.c
        emit.h
        error.c
        error.h
        lex.yy.c
        main.c
        memory.c
        memory.h
        optimize.c
        optimize.h
        patterns.h
        resource.c
        resource.h
        symbol.c
        symbol.h
        tree.c
        tree.h
        type.c
        type.h
        weed.c
        weed.h
        y.tab.c
        y.tab.h)

add_executable(JOOSA_src ${SOURCE_FILES})