#include "mainwindow.h"
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

// Конструктор
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Library Ticket System");
    setGeometry(100, 100, 700, 600);

    // Поля для вводу
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

    // Поле для виводу результатів
    outputField = new QTextEdit(this);
    outputField->setGeometry(10, 170, 680, 50);
    outputField->setReadOnly(true);

    // Кнопки
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

    saveButton = new QPushButton("Save to File", this);
    saveButton->setGeometry(490, 230, 100, 30);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::handleSaveToFile);

    loadButton = new QPushButton("Load from File", this);
    loadButton->setGeometry(600, 230, 100, 30);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::handleLoadFromFile);

    // Таблиця
    tableWidget = new QTableWidget(this);
    tableWidget->setGeometry(10, 270, 680, 300);
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels({"Name", "Workplace", "Degree", "Reg. Date", "Return Date"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// Деструктор
MainWindow::~MainWindow() {}

// Додавання квитка
void MainWindow::handleAddTicket() {
    LibraryTicket newTicket(
        inputNameField->text().toStdString(),
        inputWorkplaceField->text().toStdString(),
        inputDegreeField->text().toStdString(),
        inputRegDateField->date().toString("yyyy-MM-dd").toStdString(),
        inputReturnDateField->date().toString("yyyy-MM-dd").toStdString()
        );
    tickets.push_back(newTicket);
    outputField->setText("Ticket added successfully!");
    updateTable();
}

// Відображення квитків
void MainWindow::handleDisplayTickets() {
    updateTable();
    outputField->setText("All tickets displayed.");
}

// Редагування квитка
void MainWindow::handleEditTicket() {
    QString userName = inputNameField->text().trimmed();
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

// Видалення квитка
void MainWindow::handleRemoveTicket() {
    QString userName = inputNameField->text().trimmed();
    int index = findTicketIndexByName(userName);
    if (index == -1) {
        outputField->setText("Ticket not found for user: " + userName);
        return;
    }

    tickets.erase(tickets.begin() + index);
    outputField->setText("Ticket removed for user: " + userName);
    updateTable();
}

// Збереження до файлу
void MainWindow::handleSaveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Tickets", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        outputField->setText("Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    for (const auto& ticket : tickets) {
        out << QString::fromStdString(ticket.getUserName()) << ","
            << QString::fromStdString(ticket.getPlaceOfWork()) << ","
            << QString::fromStdString(ticket.getAcademicDegree()) << ","
            << QString::fromStdString(ticket.getRegistrationDate()) << ","
            << QString::fromStdString(ticket.getReturnDate()) << "\n";
    }
    file.close();
    outputField->setText("Tickets saved to file: " + fileName);
}

// Пошук за ім'ям
int MainWindow::findTicketIndexByName(const QString &name) {
    for (int i = 0; i < tickets.size(); ++i) {
        if (QString::fromStdString(tickets[i].getUserName()) == name) {
            return i;
        }
    }
    return -1;
}

// Завантаження з файлу
void MainWindow::handleLoadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Tickets", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        outputField->setText("Failed to open file for reading.");
        return;
    }

    tickets.clear(); // Очищуємо попередні дані
    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(",");
        if (fields.size() == 5) {
            tickets.emplace_back(
                fields[0].toStdString(), // Name
                fields[1].toStdString(), // Workplace
                fields[2].toStdString(), // Degree
                fields[3].toStdString(), // Reg. Date
                fields[4].toStdString()  // Return Date
                );
        }
    }
    file.close();
    outputField->setText("Tickets loaded from file: " + fileName);
    updateTable();
}

// Оновлення таблиці
void MainWindow::updateTable() {
    tableWidget->clearContents();
    tableWidget->setRowCount(tickets.size());

    for (int i = 0; i < tickets.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(tickets[i].getUserName())));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(tickets[i].getPlaceOfWork())));
        tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(tickets[i].getAcademicDegree())));
        tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(tickets[i].getRegistrationDate())));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(tickets[i].getReturnDate())));
    }
}
