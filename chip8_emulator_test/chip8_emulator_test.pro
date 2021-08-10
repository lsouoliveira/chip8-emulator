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
    ../chip8_emulator/src/instructions/call_addr.cpp \
    ../chip8_emulator/src/instructions/bcd.cpp \
    ../chip8_emulator/src/instructions/read_sequence.cpp \
    ../chip8_emulator/src/instructions/sprite_location.cpp \
    ../chip8_emulator/src/instructions/add_constant.cpp \
    ../chip8_emulator/src/instructions/ret.cpp \
    ../chip8_emulator/src/instructions/set_delay_timer.cpp \
    ../chip8_emulator/src/instructions/move_delay_timer.cpp \
    ../chip8_emulator/src/instructions/skip_if_equal.cpp \
    ../chip8_emulator/src/instructions/jump.cpp \
    ../chip8_emulator/src/instructions/random_number.cpp \
    ../chip8_emulator/src/mainwindow.cpp \
    ../chip8_emulator/src/utils.cpp \
    ../chip8_emulator/src/video.cpp \
    add_constant_test.cpp \
    bcd_test.cpp \
    call_addr_test.cpp \
    clear_screen_instruction_test.cpp \
    draw_sprite_test.cpp \
    load_index_register_test.cpp \
    main.cpp \
    move_constant_instruction_test.cpp \
    move_delay_timer_test.cpp \
    read_sequence_test.cpp \
    set_delay_timer_test.cpp \
    skip_if_equal_test.cpp \
    sprite_location_test.cpp

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
    ../chip8_emulator/includes/instructions/call_addr.h \
    ../chip8_emulator/includes/instructions/bcd.h \
    ../chip8_emulator/includes/instructions/read_sequence.h \
    ../chip8_emulator/includes/instructions/sprite_location.h \
    ../chip8_emulator/includes/instructions/add_constant.h \
    ../chip8_emulator/includes/instructions/ret.h \
    ../chip8_emulator/includes/instructions/set_delay_timer.h \
    ../chip8_emulator/includes/instructions/move_delay_timer.h \
    ../chip8_emulator/includes/instructions/skip_if_equal.h \
    ../chip8_emulator/includes/instructions/random_number.h \
    ../chip8_emulator/includes/mainwindow.h \
    ../chip8_emulator/includes/utils.h \
    ../chip8_emulator/includes/video.h
