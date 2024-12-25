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
    const std::string& getPlaceOfWork() const { return placeOfWork; }
    const std::string& getAcademicDegree() const { return academicDegree; }
    const std::string& getRegistrationDate() const { return registrationDate; }
    const std::string& getReturnDate() const { return returnDate; }

    void addBook(const std::string& book) {
        borrowedBooks.push_back(book);
    }

    std::string getInfo() const {
        std::string info = "User: " + userName + "\n";
        info += "Workplace: " + placeOfWork + "\n";
        info += "Degree: " + academicDegree + "\n";
        info += "Registration Date: " + registrationDate + "\n";
        info += "Return Date: " + returnDate + "\n";
        info += "Books: ";
        for (const auto& book : borrowedBooks) {
            info += book + ", ";
        }
        return info;
    }
};

#endif // LIBRARYTICKET_H
