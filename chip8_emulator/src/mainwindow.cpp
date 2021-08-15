#include "mainwindow.h"

std::vector<char> MainWindow::DEFAULT_KEY_MAPPING {
    Qt::Key_1,
    Qt::Key_2,
    Qt::Key_3,
    Qt::Key_4,
    Qt::Key_Q,
    Qt::Key_W,
    Qt::Key_E,
    Qt::Key_R,
    Qt::Key_A,
    Qt::Key_S,
    Qt::Key_D,
    Qt::Key_F,
    Qt::Key_Z,
    Qt::Key_X,
    Qt::Key_C,
    Qt::Key_V
};

std::vector<char> MainWindow::KEYBOARD_LAYOUT = {'1', '2', '3', 'C', '4', '5', '6', 'D', '7', '8', '9', 'E', 'A', '0', 'B', 'F'};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("CHIP-8 - Emulator");
    setGeometry(0, 0, 640, 320);

    centralizeWindow();
    setupConfig();

    m_EmulatorScreen = new EmulatorScreen(this, config);
    m_EmulatorScreen->setKeyboardLayout(KEYBOARD_LAYOUT);
    m_EmulatorScreen->updateKeyMapping();
    m_PreferencesDialog = new PreferencesDialog(this, KEYBOARD_LAYOUT);
    connect(m_PreferencesDialog, &PreferencesDialog::saved, this, &MainWindow::savePreferences);

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
    m_PreferencesDialog->setCycles(config->cycles());
    m_PreferencesDialog->setWrapMode(config->wrap_mode());
    m_PreferencesDialog->setKeyMapping(config->key_mapping());
    m_PreferencesDialog->show();
}

void MainWindow::savePreferences(Preferences preferences)
{
    config->cycles(preferences.cycles());
    config->wrap_mode((Chip8::WrapMode) preferences.wrap_mode());
    config->key_mapping(preferences.key_mapping());
    m_EmulatorScreen->updateKeyMapping();

    saveSettings();
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
   QSettings settings;

   config = new Chip8::Config();

   if(!settings.contains("config/cycles")) {
       config->cycles(200);
   } else {
       config->cycles(settings.value("config/cycles").toInt());
   }

   if(!settings.contains("config/wrap_mode")) {
       config->wrap_mode(Chip8::WrapMode::FULL);
   } else {
       config->wrap_mode((Chip8::WrapMode) settings.value("config/wrap_mode").toInt());
   }

   std::vector<char> keyMapping;
   for(int i = 0; i < 16; i++) {
       std::string settingsKey = "config/key_" + std::to_string(i);
       if(!settings.contains(settingsKey.c_str())) {
           keyMapping.push_back(DEFAULT_KEY_MAPPING[i]);
       } else {
           keyMapping.push_back(settings.value(settingsKey.c_str()).toInt());
       }
   }
   config->key_mapping(keyMapping);
}

void MainWindow::saveSettings()
{
    QSettings settings;

    settings.setValue("config/cycles", config->cycles());
    settings.setValue("config/wrap_mode", config->wrap_mode());

   for(int i = 0; i < 16; i++) {
       std::string settingsKey = "config/key_" + std::to_string(i);
       settings.setValue(settingsKey.c_str(), config->key_mapping()[i]);
   }
}
