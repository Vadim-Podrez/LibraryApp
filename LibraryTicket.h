#ifndef LIBRARYTICKET_H
#define LIBRARYTICKET_H

#include <string>
#include <vector>

class LibraryTicket {
private:
    std::string userName;
    std::string placeOfWork;
    std::string academicDegree;
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
};

#endif // LIBRARYTICKET_H
