//
// Created by Happiness on 10/9/2024.
//

#include <algorithm>
#include <iostream>
#include <vector>

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
