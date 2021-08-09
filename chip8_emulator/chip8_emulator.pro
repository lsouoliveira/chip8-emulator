QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += \
    chip8_emulator_pt_BR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lfmt -lspdlog

INCLUDEPATH += includes/

SOURCES += \
    includes/emulatorscreen.cpp \
    src/chip8_emulator.cpp \
    src/cpu.cpp \
    src/instructions/clear_screen_instruction.cpp \
    src/instructions/draw_sprite.cpp \
    src/instructions/instruction.cpp \
    src/instructions/instruction_map.cpp \
    src/instructions/load_index_register.cpp \
    src/instructions/move_constant_instruction.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/utils.cpp \
    src/video.cpp \

HEADERS += \
    includes/chip8_emulator.h \
    includes/constants.h \
    includes/cpu.h \
    includes/cpu_state.h \
    includes/emulatorscreen.h \
    includes/instructions/clear_screen_instruction.h \
    includes/instructions/draw_sprite.h \
    includes/instructions/instruction.h \
    includes/instructions/instruction_map.h \
    includes/instructions/load_index_register.h \
    includes/instructions/load_register_with_constant.h \
    includes/instructions/move_constant_instruction.h \
    includes/mainwindow.h \
    includes/utils.h \
    includes/video.h
