#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Library Ticket System");
    setGeometry(100, 100, 400, 300);

    outputField = new QTextEdit(this);
    outputField->setGeometry(10, 10, 380, 200);
    outputField->setReadOnly(true);

    inputField = new QLineEdit(this);
    inputField->setGeometry(10, 220, 280, 30);

    addButton = new QPushButton("Add Ticket", this);
    addButton->setGeometry(300, 220, 90, 30);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::handleAddTicket);

    displayButton = new QPushButton("Display Tickets", this);
    displayButton->setGeometry(150, 260, 120, 30);
    connect(displayButton, &QPushButton::clicked, this, &MainWindow::handleDisplayTickets);
}

MainWindow::~MainWindow() {}

void MainWindow::handleAddTicket() {
    QString userName = inputField->text();
    if (userName.isEmpty()) {
        outputField->setText("User name cannot be empty!");
        return;
    }

    LibraryTicket newTicket(userName.toStdString(), "Workplace", "PhD", "2024-06-01", "2024-06-30");
    newTicket.addBook("Book1");
    tickets.push_back(newTicket);

    outputField->setText("Ticket added for user: " + userName);
    inputField->clear();
}

void MainWindow::handleDisplayTickets() {
    outputField->clear();
    if (tickets.empty()) {
        outputField->setText("No tickets available.");
        return;
    }

    for (const auto& ticket : tickets) {
        outputField->append(QString::fromStdString(ticket.getInfo()));
        outputField->append("-----------------------");
    }
}
