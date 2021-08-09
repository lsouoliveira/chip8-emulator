#ifndef EMULATORSCREEN_H
#define EMULATORSCREEN_H

#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cmath>

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

// #include <spdlog/spdlog.h>

#include <chip8_emulator.h>
#include <utils.h>

class EmulatorScreen : public QFrame
{
    Q_OBJECT
public:
    explicit EmulatorScreen(QWidget *parent = nullptr);

    void load(QString fileName);

public slots:
    void toggleDebugging();

signals:

protected:
    void paintEvent(QPaintEvent *event);

private:
    void setupPalette();
    void updateEmulator();
    double getTime();
    double getDeltaTime();
    void updateScreen(double deltaTime);
    void drawScreen(QPainter& painter);

    Chip8::Chip8Emulator m_Emulator;
    QTimer *m_Timer;
    QLabel *m_CpuStateLabel;
    double m_LastTimestamp;
    double m_UpdateCounter;
    bool m_IsDebbuging;
};

#endif // EMULATORSCREEN_H
