#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QContextMenuEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QSettings>

#include <emulatorscreen.h>

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

private:
    void createMenus();
    void createActions();
    void centralizeWindow();

    QMenu *fileMenu;
    QMenu *toolsMenu;
    QAction *loadAction;
    QAction *exitAction;
    QAction *enableDebugAction;
    EmulatorScreen *m_EmulatorScreen;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
