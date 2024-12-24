#ifndef LIBRARYTICKET_H
#define LIBRARYTICKET_H

#include <string>
#include <vector>
#include <iostream>

class LibraryTicket {
private:
    std::string userName;
    std::string placeOfWork;
    std::string academicDegree;
    std::vector<std::string> borrowedBooks;
    std::string registrationDate;
    std::string returnDate;

public:
    LibraryTicket(std::string name, std::string work, std::string degree,
                  std::string regDate, std::string retDate)
        : userName(name), placeOfWork(work), academicDegree(degree),
        registrationDate(regDate), returnDate(retDate) {}

    const std::string& getUserName() const { return userName; }

    void addBook(const std::string& book) {
        borrowedBooks.push_back(book);
    }

    void displayInfo() const {
        std::cout << "User: " << userName << "\n"
                  << "Workplace: " << placeOfWork << "\n"
                  << "Academic Degree: " << academicDegree << "\n"
                  << "Registration Date: " << registrationDate << "\n"
                  << "Return Date: " << returnDate << "\n"
                  << "Borrowed Books: ";
        for (const auto& book : borrowedBooks) {
            std::cout << book << ", ";
        }
        std::cout << std::endl;
    }
};

#endif // LIBRARYTICKET_H
