#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "LibraryTicket.h"
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleAddTicket();
    void handleDisplayTickets();

private:
    QLineEdit *inputField;
    QTextEdit *outputField;
    QPushButton *addButton;
    QPushButton *displayButton;

    std::vector<LibraryTicket> tickets;
};

#endif // MAINWINDOW_H
