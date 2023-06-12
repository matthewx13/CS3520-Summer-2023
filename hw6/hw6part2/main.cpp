#include "repository.hpp"
#include "book.hpp"
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> ints = {78, 86, 45, 23, 83, 19, 104};
    Repository<int> repoInts(ints);

    repoInts.printList();
    std::cout << "Number of items: " << repoInts.count() << std::endl;

    repoInts.add(999);
    repoInts.printList();

    std::cout << "Order of item 83: " << repoInts.findOrder(83) << std::endl;
    std::cout << "Order of item 100: " << repoInts.findOrder(100) << std::endl;

    repoInts.remove(86);
    repoInts.printList();

    std::vector<std::string> words = {"apple", "bottom", "jeans", "boots", "with"};
    Repository<std::string> repoWords(words);

    repoWords.printList();
    std::cout << "Number of items: " << repoWords.count() << std::endl;

    repoWords.add("999");
    repoWords.printList();

    std::cout << "Order of item 'boots': " << repoWords.findOrder("boots") << std::endl;
    std::cout << "Order of item 'sunburn': " << repoWords.findOrder("sunburn") << std::endl;

    repoWords.remove("bottom");
    repoWords.printList();

    // Create some books
    Book b1("Catcher in the Rye", 1951);
    Book b2("To Kill a Mockingbird", 1960);
    Book b3("1984", 1949);

    std::vector<Book> books = {b1, b2, b3};
    Repository<Book> repoBooks(books);

    repoBooks.printList();
    std::cout << "Number of items: " << repoBooks.count() << std::endl;

    std::string bookTitle;
    int bookYear;

    // Add a book
    std::cout << "Enter the title of the book to add: ";
    std::getline(std::cin, bookTitle);
    std::cout << "Enter the publication year of the book to add: ";
    std::cin >> bookYear;
    std::cin.ignore(); // Ignore the remaining newline character

    Book newBook(bookTitle, bookYear);
    repoBooks.add(newBook);
    repoBooks.printList();

    // Remove a book
    std::cout << "Enter the title of the book to remove: ";
    std::getline(std::cin, bookTitle);
    std::cout << "Enter the publication year of the book to remove: ";
    std::cin >> bookYear;
    std::cin.ignore(); // Ignore the remaining newline character

    Book bookToRemove(bookTitle, bookYear);
    repoBooks.remove(bookToRemove);
    repoBooks.printList();

    return 0;
}

