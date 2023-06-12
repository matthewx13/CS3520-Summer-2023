#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

class Book {
public:
    Book() = default;
    Book(const std::string& name, int pubYear);
    std::string getName() const;
    int getYear() const;
    Book(const Book& other);
    Book(Book&& other) noexcept;
    Book& operator=(const Book& other);
    Book& operator=(Book&& other) noexcept;
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Book& b);

private:
    std::string name;
    int pubYear;
};

#endif  // BOOK_HPP
