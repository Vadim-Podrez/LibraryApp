//
// Created by Happiness on 10/9/2024.
//

#include "mainwindow.h"
#include <QApplication>
#include "LibraryTicket.h"

#include <algorithm>
#include <iostream>
#include <vector>

// Function prototypes
void addTicket(std::vector<LibraryTicket>& tickets);
void removeTicket(std::vector<LibraryTicket>& tickets);
void displayAllTickets(const std::vector<LibraryTicket>& tickets);

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    std::vector<LibraryTicket> tickets;

    while (true) {
        std::cout << "\n--- Library Ticket System ---\n";
        std::cout << "1. Add Ticket\n";
        std::cout << "2. Remove Ticket\n";
        std::cout << "3. Display All Tickets\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            addTicket(tickets);
            break;
        case 2:
            removeTicket(tickets);
            break;
        case 3:
            displayAllTickets(tickets);
            break;
        case 4:
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void addTicket(std::vector<LibraryTicket>& tickets) {
    std::string name, work, degree, regDate, retDate;

    std::cout << "Enter user name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter place of work: ";
    std::getline(std::cin, work);
    std::cout << "Enter academic degree: ";
    std::getline(std::cin, degree);
    std::cout << "Enter registration date: ";
    std::getline(std::cin, regDate);
    std::cout << "Enter return date: ";
    std::getline(std::cin, retDate);

    LibraryTicket newTicket(name, work, degree, regDate, retDate);

    int numBooks;
    std::cout << "Enter number of borrowed books: ";
    std::cin >> numBooks;

    std::cin.ignore(); // Clear newline character from buffer
    for (int i = 0; i < numBooks; ++i) {
        std::string book;
        std::cout << "Enter book #" << (i + 1) << ": ";
        std::getline(std::cin, book);
        newTicket.addBook(book);
    }

    tickets.push_back(newTicket);
    std::cout << "Ticket added successfully!\n";
}

void removeTicket(std::vector<LibraryTicket>& tickets) {
    std::string name;
    std::cout << "Enter user name to remove: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    auto it = std::remove_if(tickets.begin(), tickets.end(), [&name](const LibraryTicket& ticket) {
        return ticket.getUserName() == name;
    });

    if (it != tickets.end()) {
        tickets.erase(it, tickets.end());
        std::cout << "Ticket removed successfully!\n";
    } else {
        std::cout << "No ticket found for user: " << name << "\n";
    }
}

void displayAllTickets(const std::vector<LibraryTicket>& tickets) {
    if (tickets.empty()) {
        std::cout << "No tickets to display.\n";
        return;
    }

    for (const auto& ticket : tickets) {
        ticket.displayInfo();
        std::cout << "----------------------\n";
    }
}
