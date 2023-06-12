#include "book.hpp"

Book::Book(const std::string& name, int pubYear)
    : name(name), pubYear(pubYear) {}

std::string Book::getName() const {
    return name;
}

int Book::getYear() const {
    return pubYear;
}

Book::Book(const Book& other)
    : name(other.getName()), pubYear(other.getYear()) {}

Book::Book(Book&& other) noexcept
    : name(std::move(other.getName())), pubYear(other.getYear()) {}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        name = other.getName();
        pubYear = other.getYear();
    }
    return *this;
}

Book& Book::operator=(Book&& other) noexcept {
    if (this != &other) {
        name = std::move(other.getName());
        pubYear = other.getYear();
    }
    return *this;
}

bool Book::operator==(const Book& other) const {
    return this->name == other.getName() && this->pubYear == other.getYear();
}

bool Book::operator!=(const Book& other) const {
    return this->name != other.getName() || this->pubYear != other.getYear();
}

std::ostream& operator<<(std::ostream& out, const Book& b) {
    out << b.getName() << ", " << b.getYear();
    return out;
}
