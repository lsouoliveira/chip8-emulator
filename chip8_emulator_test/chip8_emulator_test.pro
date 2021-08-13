include(gtest_dependency.pri)

QT += core gui

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
    ../chip8_emulator/src/preferencesdialog.cpp \
    ../chip8_emulator/src/keypresslineedit.cpp \
    ../chip8_emulator/src/chip8_emulator.cpp \
    ../chip8_emulator/src/cpu.cpp \
    ../chip8_emulator/src/instructions/instructions.cpp \
    ../chip8_emulator/src/instructions/instruction_map.cpp \
    ../chip8_emulator/src/mainwindow.cpp \
    ../chip8_emulator/src/utils.cpp \
    ../chip8_emulator/src/video.cpp \
    instructions_test.cpp \
    main.cpp \

HEADERS += \
    ../chip8_emulator/includes/chip8_emulator.h \
    ../chip8_emulator/includes/constants.h \
    ../chip8_emulator/includes/cpu.h \
    ../chip8_emulator/includes/cpu_state.h \
    ../chip8_emulator/includes/emulatorscreen.h \
    ../chip8_emulator/includes/preferencesdialog.h \
    ../chip8_emulator/models/preferences.h \
    ../chip8_emulator/includes/keypresslineedit.h \
    ../chip8_emulator/includes/instructions/instructions.h \
    ../chip8_emulator/includes/instructions/instruction_map.h \
    ../chip8_emulator/includes/mainwindow.h \
    ../chip8_emulator/includes/utils.h \
    ../chip8_emulator/includes/video.h
