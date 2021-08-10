#include "emulatorscreen.h"

EmulatorScreen::EmulatorScreen(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);

    setupPalette();

    m_Timer = new QTimer(this);
    connect(m_Timer, &QTimer::timeout, [this]{ updateEmulator(); });

    m_Timer->start(1);
    m_LastTimestamp = -1;

    m_CpuStateLabel = new QLabel(this);
    m_CpuStateLabel->setWordWrap(true);
    m_CpuStateLabel->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
    m_CpuStateLabel->setVisible(false);
    m_CpuStateLabel->setStyleSheet("QLabel { color: yellow; } ");

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(m_CpuStateLabel);
    setLayout(layout);

    m_Emulator.Init();
    m_IsDebbuging = false;

    toggleDebugging();
}

void EmulatorScreen::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    painter.fillRect(0, 0, size().width(), size().height(), QColor(0, 0, 0));
    drawScreen(painter);
}

void EmulatorScreen::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_N:
            execInstruction();
            break;
    }
}

void EmulatorScreen::setupPalette()
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);

    setAutoFillBackground(true);
    setPalette(pal);
}

void EmulatorScreen::load(QString fileName)
{
    std::vector<unsigned char> data = Chip8::ReadData(fileName.toStdString());

    m_Emulator.cpu()->Reset();
    m_Emulator.cpu()->Start();
    m_Emulator.video()->ClearBuffer();

    m_Emulator.Load(data);
}

void EmulatorScreen::updateEmulator()
{
    if(m_LastTimestamp < 0) {
        m_LastTimestamp = getTime();
        m_UpdateCounter = 0;
    }

    double deltaTime = getDeltaTime();

    m_Emulator.Update(deltaTime);
    updateScreen(deltaTime);

    m_Timer->start(1);
}

double EmulatorScreen::getTime()
{
   return std::chrono::duration<double, std::milli>(system_clock::now().time_since_epoch()).count();
}

void EmulatorScreen::updateScreen(double deltaTime)
{
    m_UpdateCounter += deltaTime;

    if(m_UpdateCounter >= 16) {
        this->update();
        m_CpuStateLabel->setText(m_Emulator.cpu()->state().ToString().c_str());
        m_UpdateCounter = 0;
    }
}

void EmulatorScreen::drawScreen(QPainter& painter)
{

    int rectWidth = size().width() / 64.0;
    int rectHeight = size().height() / 32.0;

    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < 64; j++) {
            if(m_Emulator.video()->GetBuffer()[i * 64 + j] == 1) {
            painter.fillRect(j * rectWidth, i * rectHeight, rectWidth, rectHeight, 0x00FF00);
            }
        }
    }
}

double EmulatorScreen::getDeltaTime()
{
    double currTime = getTime();
    double deltaTime = currTime - m_LastTimestamp;

    m_LastTimestamp = currTime;

    return deltaTime;
}

void EmulatorScreen::toggleDebugging()
{
    m_IsDebbuging = !m_IsDebbuging;
    m_Emulator.cpu()->SetDebug(m_IsDebbuging);
    m_CpuStateLabel->setVisible(m_IsDebbuging);
}

void EmulatorScreen::execInstruction()
{
    if(!m_Emulator.cpu()->is_paused() && m_Emulator.cpu()->is_debugging()) {
        m_Emulator.cpu()->Step();
    }
}
