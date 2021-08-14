#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

#include <emulatorscreen.h>
#include <preferencesdialog.h>
#include <utils.h>
#include <config.h>
#include <models/preferences.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private slots:
    void exit();
    void load();
    void openPreferences();
    void savePreferences(Preferences preferences);

private:
    void createMenus();
    void createActions();
    void centralizeWindow();
    void setupConfig();
    void saveSettings();

    QMenu *fileMenu;
    QMenu *toolsMenu;
    QAction *openPreferencesAction;
    QAction *loadAction;
    QAction *exitAction;
    QAction *enableDebugAction;
    EmulatorScreen *m_EmulatorScreen;
    PreferencesDialog *m_PreferencesDialog;
    Chip8::Config* config;
    static std::vector<char> DEFAULT_KEY_MAPPING;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static std::vector<char> KEYBOARD_LAYOUT;
};
#endif // MAINWINDOW_H
