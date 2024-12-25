#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QDateEdit>
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
    void handleEditTicket();
    void handleRemoveTicket();

private:
    QLineEdit *inputNameField;
    QLineEdit *inputWorkplaceField;
    QLineEdit *inputDegreeField;
    QDateEdit *inputRegDateField;
    QDateEdit *inputReturnDateField;

    QTextEdit *outputField;
    QTableWidget *tableWidget;

    QPushButton *addButton;
    QPushButton *displayButton;
    QPushButton *editButton;
    QPushButton *removeButton;

    std::vector<LibraryTicket> tickets;

    void updateTable();
    int findTicketIndexByName(const QString &name);

};

#endif // MAINWINDOW_H
