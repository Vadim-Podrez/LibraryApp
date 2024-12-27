#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QDateEdit>
#include <QtSql/QSqlDatabase>
#include <vector>
#include "LibraryTicket.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleConnectToDatabase();
    void handleSyncWithDatabase();
    void handleAddTicket();
    void handleUpdateTicket();
    void handleDeleteTicket();

private:
    QLineEdit *inputNameField;
    QLineEdit *inputWorkplaceField;
    QLineEdit *inputDegreeField;
    QDateEdit *inputRegDateField;
    QDateEdit *inputReturnDateField;
    QLineEdit *inputBorrowedBooksField;
    QTableWidget *tableWidget;

    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteButton;

    QSqlDatabase db;

    void setupTable();
    void updateTable();
};

#endif // MAINWINDOW_H
