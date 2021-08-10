#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("CHIP-8 - Emulator");
    setGeometry(0, 0, 640, 320);

    centralizeWindow();

    m_EmulatorScreen = new EmulatorScreen(this);

    createActions();
    createMenus();

    setCentralWidget(m_EmulatorScreen);
}

MainWindow::~MainWindow()
{
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::exit()
{
    close();
}

void MainWindow::load()
{
    QSettings settings;

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open a ROM"), settings.value("mainwindow/romPath").toString(), "");

    if(!fileName.isEmpty()) {
        QDir dir;
        settings.setValue("mainwindow/romPath", dir.absoluteFilePath(fileName));
    }

    m_EmulatorScreen->load(fileName);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(loadAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(enableDebugAction);
}

void MainWindow::createActions()
{
    loadAction = new QAction(tr("Load"), this);
    loadAction->setStatusTip(tr("Load a ROM"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::load);

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setStatusTip(tr("Exit application"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::exit);

    enableDebugAction = new QAction(tr("Debug"), this);
    enableDebugAction->setStatusTip(tr("Enable/Disable debugging"));
    connect(enableDebugAction, &QAction::triggered, m_EmulatorScreen, &EmulatorScreen::toggleDebugging);
}

void MainWindow::centralizeWindow()
{
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();

    move(center.x() - width() * 0.5, center.y() - height() * 0.5);
}
