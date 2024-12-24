#include "mainwindow.h"
#include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }

#include "mainwindow.h"
#include <QApplication>
#include "LibraryTicket.h"

int main(int argc, char *argv[]) {

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

    // Створення об'єкта на стеку
    LibraryTicket ticket1("Alice Smith", "Library Dept.", "PhD", "2024-06-01", "2024-06-30");
    ticket1.addBook("The Great Gatsby");
    ticket1.addBook("1984");

    std::cout << "Ticket created on stack:\n";
    ticket1.displayInfo();

    // Створення об'єкта на купі
    LibraryTicket* ticket2 = new LibraryTicket("Bob Johnson", "Research Dept.", "MSc", "2024-06-05", "2024-06-25");
    ticket2->addBook("To Kill a Mockingbird");

    std::cout << "\nTicket created on heap:\n";
    ticket2->displayInfo();

    // Звільнення пам'яті
    delete ticket2;

    return 0;
}
