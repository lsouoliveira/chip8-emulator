#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("CHIP-8 - Emulator");
    setGeometry(0, 0, 640, 320);

    centralizeWindow();

    m_EmulatorScreen = new EmulatorScreen(this);
    m_PreferencesDialog = new PreferencesDialog(this);

    createActions();
    createMenus();
    setupConfig();

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

        try {
            std::vector<unsigned char> data = Chip8::ReadData(fileName.toStdString());

            m_EmulatorScreen->load(data);
        } catch(const std::exception& e) {
            QMessageBox messageBox;
            messageBox.critical(0, "Error", tr("Invalid file"));
            messageBox.show();
        }
    }
}

void MainWindow::openPreferences()
{
    m_PreferencesDialog->show();
}

void MainWindow::savePreferences()
{
    connect(m_PreferencesDialog, &PreferencesDialog::saved, this, &MainWindow::savePreferences);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(loadAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(enableDebugAction);
    toolsMenu->addAction(openPreferencesAction);
}

void MainWindow::createActions()
{
    openPreferencesAction = new QAction(tr("Preferences"), this);
    openPreferencesAction->setStatusTip(tr("Open preferences"));
    connect(openPreferencesAction, &QAction::triggered, this, &MainWindow::openPreferences);

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

void MainWindow::setupConfig()
{
   config = new Chip8::Config();
}
