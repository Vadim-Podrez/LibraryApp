#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Library Ticket System");
    setGeometry(100, 100, 900, 650);

    // Поля вводу
    inputNameField = new QLineEdit(this);
    inputNameField->setPlaceholderText("Enter Name");
    inputNameField->setGeometry(10, 320, 200, 30);

    inputWorkplaceField = new QLineEdit(this);
    inputWorkplaceField->setPlaceholderText("Enter Workplace");
    inputWorkplaceField->setGeometry(220, 320, 200, 30);

    inputDegreeField = new QLineEdit(this);
    inputDegreeField->setPlaceholderText("Enter Degree");
    inputDegreeField->setGeometry(430, 320, 200, 30);

    inputRegDateField = new QDateEdit(this);
    inputRegDateField->setDisplayFormat("yyyy-MM-dd");
    inputRegDateField->setGeometry(10, 360, 200, 30);

    inputReturnDateField = new QDateEdit(this);
    inputReturnDateField->setDisplayFormat("yyyy-MM-dd");
    inputReturnDateField->setGeometry(220, 360, 200, 30);

    inputBorrowedBooksField = new QLineEdit(this); // Поле для позичених книжок
    inputBorrowedBooksField->setPlaceholderText("Enter Borrowed Books (comma-separated)");
    inputBorrowedBooksField->setGeometry(430, 360, 440, 30);

    // Таблиця
    tableWidget = new QTableWidget(this);
    tableWidget->setGeometry(10, 10, 870, 300);
    setupTable();

    // Кнопки CRUD
    addButton = new QPushButton("Add Ticket", this);
    addButton->setGeometry(10, 400, 100, 30);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::handleAddTicket);

    updateButton = new QPushButton("Update Ticket", this);
    updateButton->setGeometry(120, 400, 100, 30);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::handleUpdateTicket);

    deleteButton = new QPushButton("Delete Ticket", this);
    deleteButton->setGeometry(230, 400, 100, 30);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::handleDeleteTicket);

    // Автоматичне підключення до бази
    handleConnectToDatabase();
    handleSyncWithDatabase();
}
MainWindow::~MainWindow() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}

void MainWindow::handleConnectToDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("library_tickets.db");

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS LibraryTickets (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            workplace TEXT,
            degree TEXT,
            reg_date TEXT,
            return_date TEXT,
            borrowed_books TEXT
        )
    )");
}


void MainWindow::handleSyncWithDatabase() {
    if (!db.isOpen()) return;

    QSqlQuery query("SELECT * FROM LibraryTickets");
    tableWidget->setRowCount(0);

    while (query.next()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("workplace").toString()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("degree").toString()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("reg_date").toString()));
        tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("return_date").toString()));
        tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("borrowed_books").toString()));
    }
}


void MainWindow::handleAddTicket() {
    if (!db.isOpen()) return;

    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO LibraryTickets (name, workplace, degree, reg_date, return_date, borrowed_books)
        VALUES (:name, :workplace, :degree, :reg_date, :return_date, :borrowed_books)
    )");
    query.bindValue(":name", inputNameField->text());
    query.bindValue(":workplace", inputWorkplaceField->text());
    query.bindValue(":degree", inputDegreeField->text());
    query.bindValue(":reg_date", inputRegDateField->date().toString("yyyy-MM-dd"));
    query.bindValue(":return_date", inputReturnDateField->date().toString("yyyy-MM-dd"));
    query.bindValue(":borrowed_books", inputBorrowedBooksField->text());

    query.exec();
    handleSyncWithDatabase();
}


void MainWindow::handleUpdateTicket() {
    if (!db.isOpen()) return;

    QSqlQuery query;
    query.prepare(R"(
        UPDATE LibraryTickets
        SET workplace = :workplace, degree = :degree, reg_date = :reg_date, return_date = :return_date, borrowed_books = :borrowed_books
        WHERE name = :name
    )");
    query.bindValue(":name", inputNameField->text());
    query.bindValue(":workplace", inputWorkplaceField->text());
    query.bindValue(":degree", inputDegreeField->text());
    query.bindValue(":reg_date", inputRegDateField->date().toString("yyyy-MM-dd"));
    query.bindValue(":return_date", inputReturnDateField->date().toString("yyyy-MM-dd"));
    query.bindValue(":borrowed_books", inputBorrowedBooksField->text());

    query.exec();
    handleSyncWithDatabase();
}


void MainWindow::handleDeleteTicket() {
    if (!db.isOpen()) return;

    QSqlQuery query;
    query.prepare("DELETE FROM LibraryTickets WHERE name = :name");
    query.bindValue(":name", inputNameField->text());
    query.exec();
    handleSyncWithDatabase();
}

void MainWindow::setupTable() {
    tableWidget->setColumnCount(7);
    tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Workplace", "Degree", "Reg Date", "Return Date", "Borrowed Books"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
}

