#include <QApplication>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <mainwindow.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
