include(gtest_dependency.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt

LIBS += -lfmt -lspdlog

INCLUDEPATH += ../chip8_emulator/includes

SOURCES += \
    ../chip8_emulator/includes/emulatorscreen.cpp \
    ../chip8_emulator/src/chip8_emulator.cpp \
    ../chip8_emulator/src/cpu.cpp \
    ../chip8_emulator/src/instructions/clear_screen_instruction.cpp \
    ../chip8_emulator/src/instructions/draw_sprite.cpp \
    ../chip8_emulator/src/instructions/instruction.cpp \
    ../chip8_emulator/src/instructions/instruction_map.cpp \
    ../chip8_emulator/src/instructions/load_index_register.cpp \
    ../chip8_emulator/src/instructions/move_constant_instruction.cpp \
    ../chip8_emulator/src/mainwindow.cpp \
    ../chip8_emulator/src/utils.cpp \
    ../chip8_emulator/src/video.cpp \
    clear_screen_instruction_test.cpp \
    draw_sprite_test.cpp \
    load_index_register_test.cpp \
    main.cpp \
    move_constant_instruction_test.cpp

HEADERS += \
    ../chip8_emulator/includes/chip8_emulator.h \
    ../chip8_emulator/includes/constants.h \
    ../chip8_emulator/includes/cpu.h \
    ../chip8_emulator/includes/cpu_state.h \
    ../chip8_emulator/includes/emulatorscreen.h \
    ../chip8_emulator/includes/instructions/clear_screen_instruction.h \
    ../chip8_emulator/includes/instructions/draw_sprite.h \
    ../chip8_emulator/includes/instructions/instruction.h \
    ../chip8_emulator/includes/instructions/instruction_map.h \
    ../chip8_emulator/includes/instructions/load_index_register.h \
    ../chip8_emulator/includes/instructions/load_register_with_constant.h \
    ../chip8_emulator/includes/instructions/move_constant_instruction.h \
    ../chip8_emulator/includes/mainwindow.h \
    ../chip8_emulator/includes/utils.h \
    ../chip8_emulator/includes/video.h
