#include "mainwindow.h"
#include <QHeaderView>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Library Ticket System");
    setGeometry(100, 100, 700, 500);

    inputNameField = new QLineEdit(this);
    inputNameField->setPlaceholderText("Enter user name");
    inputNameField->setGeometry(10, 10, 300, 30);

    inputWorkplaceField = new QLineEdit(this);
    inputWorkplaceField->setPlaceholderText("Enter workplace");
    inputWorkplaceField->setGeometry(10, 50, 300, 30);

    inputDegreeField = new QLineEdit(this);
    inputDegreeField->setPlaceholderText("Enter degree");
    inputDegreeField->setGeometry(10, 90, 300, 30);

    inputRegDateField = new QDateEdit(this);
    inputRegDateField->setCalendarPopup(true);
    inputRegDateField->setDate(QDate::currentDate());
    inputRegDateField->setGeometry(10, 130, 150, 30);

    inputReturnDateField = new QDateEdit(this);
    inputReturnDateField->setCalendarPopup(true);
    inputReturnDateField->setDate(QDate::currentDate().addDays(30));
    inputReturnDateField->setGeometry(170, 130, 150, 30);

    outputField = new QTextEdit(this);
    outputField->setGeometry(10, 170, 680, 50);
    outputField->setReadOnly(true);

    addButton = new QPushButton("Add Ticket", this);
    addButton->setGeometry(10, 230, 100, 30);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::handleAddTicket);

    displayButton = new QPushButton("Display Tickets", this);
    displayButton->setGeometry(120, 230, 120, 30);
    connect(displayButton, &QPushButton::clicked, this, &MainWindow::handleDisplayTickets);

    editButton = new QPushButton("Edit Ticket", this);
    editButton->setGeometry(250, 230, 100, 30);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::handleEditTicket);

    removeButton = new QPushButton("Remove Ticket", this);
    removeButton->setGeometry(360, 230, 120, 30);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::handleRemoveTicket);

    tableWidget = new QTableWidget(this);
    tableWidget->setGeometry(10, 270, 680, 200);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels({"Name", "Workplace", "Degree", "Reg. Date", "Return Date"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
    // Очищення ресурсів, якщо потрібно
}

void MainWindow::handleAddTicket() {
    LibraryTicket newTicket(
        inputNameField->text().toStdString(),
        inputWorkplaceField->text().toStdString(),
        inputDegreeField->text().toStdString(),
        inputRegDateField->date().toString("yyyy-MM-dd").toStdString(),
        inputReturnDateField->date().toString("yyyy-MM-dd").toStdString()
        );
    tickets.push_back(newTicket);
    updateTable();
}

void MainWindow::handleDisplayTickets() {
    updateTable();
    outputField->setText("Displaying all tickets.");
}

void MainWindow::handleEditTicket() {
    QString userName = inputNameField->text().trimmed();
    if (userName.isEmpty()) {
        outputField->setText("Please enter a user name to edit.");
        return;
    }

    int index = findTicketIndexByName(userName);
    if (index == -1) {
        outputField->setText("Ticket not found for user: " + userName);
        return;
    }

    tickets[index] = LibraryTicket(
        userName.toStdString(),
        inputWorkplaceField->text().toStdString(),
        inputDegreeField->text().toStdString(),
        inputRegDateField->date().toString("yyyy-MM-dd").toStdString(),
        inputReturnDateField->date().toString("yyyy-MM-dd").toStdString()
        );

    outputField->setText("Ticket updated for user: " + userName);
    updateTable();
}

int MainWindow::findTicketIndexByName(const QString &name) {
    for (int i = 0; i < tickets.size(); ++i) {
        if (QString::fromStdString(tickets[i].getUserName()) == name) {
            return i;
        }
    }
    return -1; // Якщо користувача не знайдено
}



void MainWindow::handleRemoveTicket() {
    QString userName = inputNameField->text().trimmed();
    if (userName.isEmpty()) {
        outputField->setText("Please enter a user name to remove.");
        return;
    }

    if (tickets.empty()) {
        outputField->setText("No tickets available to remove.");
        return;
    }

    int index = findTicketIndexByName(userName);
    if (index == -1) {
        outputField->setText("Ticket not found for user: " + userName);
        return;
    }

    tickets.erase(tickets.begin() + index);
    outputField->setText("Ticket removed for user: " + userName);
    updateTable();
}

void MainWindow::updateTable() {
    tableWidget->setRowCount(tickets.size());
    for (int i = 0; i < tickets.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(tickets[i].getUserName())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(tickets[i].getPlaceOfWork())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(tickets[i].getAcademicDegree())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(tickets[i].getRegistrationDate())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(tickets[i].getReturnDate())));
    }
}
