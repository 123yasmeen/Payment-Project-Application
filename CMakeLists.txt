cmake_minimum_required(VERSION 3.21)
project(Payment_Project_Application_main C)

set(CMAKE_C_STANDARD 11)

include_directories(app)
include_directories(card)
include_directories(server)
include_directories(terminal)

add_executable(Payment_Project_Application_main
        app/app.c
        app/app.h
        card/card.c
        card/card.h
        server/server.c
        server/server.h
        terminal/terminal.c
        terminal/terminal.h
        main.c)
