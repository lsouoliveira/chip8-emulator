#ifndef EMULATORSCREEN_H
#define EMULATORSCREEN_H

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cmath>
#include <unordered_map>
#include <functional>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

#include <QWidget>
#include <QFrame>
#include <QPalette>
#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QtCore/Qt>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QKeyEvent>

#include <chip8_emulator.h>
#include <config.h>

class EmulatorScreen : public QFrame
{
    Q_OBJECT
public:
    explicit EmulatorScreen(QWidget *parent = nullptr, Chip8::Config* config = nullptr);

    void load(std::vector<unsigned char> data);
    void setKeyboardLayout(std::vector<char> layout);
    void updateKeyMapping();

public slots:
    void toggleDebugging();

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void setupPalette();
    void updateEmulator();
    double getTime();
    double getDeltaTime();
    void updateScreen(double deltaTime);
    void drawScreen(QPainter& painter);
    void execInstruction();

    Chip8::Config* m_Config;
    Chip8::Chip8Emulator m_Emulator;
    QTimer *m_Timer;
    QLabel *m_CpuStateLabel;
    double m_LastTimestamp;
    double m_UpdateCounter;
    bool m_IsDebbuging;
    std::unordered_map<unsigned char, std::function<void(unsigned char key, bool isPressed)>> m_KeyCallbackMapping;
    std::unordered_map<unsigned char, unsigned char> m_KeyMapping;
    std::vector<char> m_KeyboardLayout;
};

#endif // EMULATORSCREEN_H
