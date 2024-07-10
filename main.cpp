#include <algorithm> // For std::transform
#include <cctype> // For std::tolower
#include <iostream>
#include <vector>
#include <string>


// Helper function to normalize titles: lowercase and remove punctuation
std::string normalizeTitle(const std::string& title) {
    std::string normalized;
    std::copy_if(title.begin(), title.end(), std::back_inserter(normalized), 
                  [](unsigned char c) { return std::isalnum(c); });
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                    [](unsigned char c) { return std::tolower(c); });
    return normalized;
}

enum class BookStatus { Available, Borrowed, Missing, Overdue };

class Book {
public:
    std::string title, author, ISBN;
    BookStatus status;

    Book(std::string title, std::string author, std::string ISBN, BookStatus status = BookStatus::Available)
        : title(title), author(author), ISBN(ISBN), status(status) {}

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN
                  << ", Status: ";
        switch (status) {
            case BookStatus::Available: std::cout << "Available"; break;
            case BookStatus::Borrowed: std::cout << "Borrowed"; break;
            case BookStatus::Missing: std::cout << "Missing"; break;
            case BookStatus::Overdue: std::cout << "Overdue"; break;
        }
        std::cout << std::endl;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayBooks() const {
        for (const auto& book : books) {
            book.display();
        }
    }

    // Function to find a book by normalized title
    std::vector<Book>::iterator findBookByNormalizedTitle(const std::string& title) {
        std::string normalizedTitle = normalizeTitle(title);
        return std::find_if(books.begin(), books.end(), [&normalizedTitle](const Book& book) {
            return book.title == normalizedTitle;
        });
    }

    void checkOutBookByISBN(const std::string& ISBN) {
        bool found = false;
        for (auto& book : books) {
            if (book.ISBN == ISBN) {
                found = true;
                if (book.status == BookStatus::Available) {
                    book.status = BookStatus::Borrowed;
                    std::cout << "Book checked out successfully." << std::endl;
                    return;
                } else {
                std::cout << "Book not available for checkout." << std::endl;
                return;
            }
        }
    }   
    if (!found) {
        std::cout << "Book does not exist at this library." << std::endl;
    }
}

    // New method to check out book by title
    void checkOutBookByTitle(const std::string& title) {
        bool found = false;
        for (auto& book : books) {
            if (book.title == title) {
                found = true;
                if (book.status == BookStatus::Available) {
                    book.status = BookStatus::Borrowed;
                    std::cout << "Book checked out successfully." << std::endl;
                    return;
                } else {
                    std::cout << "Book not available for checkout." << std::endl;
                    return;
                }
            }
        }
        if (!found) {
            std::cout << "Book does not exist at this library." << std::endl;
        }
    }

    // Renamed returnBookByISBN for clarity. formerly returnBook
    void returnBookByISBN(const std::string& ISBN) {
        bool found = false;
        for (auto& book : books) {
            if (book.ISBN == ISBN) {
                found = true;
                if (book.status == BookStatus::Borrowed) {
                    book.status = BookStatus::Available;
                    std::cout << "Book returned successfully." << std::endl;
                    return;
                } else {
                    std::cout << "Book was not borrowed." << std::endl;
                    return;
                }
            }
        }
        if (!found) {
            std::cout << "Book does not exist at this library" << std::endl;
            return;
        }
    }

    // New method to return a book by title
    void returnBookByTitle(const std::string& title) {
        bool found = false;
        for (auto& book: books) {
            if (book.title == title) {
                found = true;
                if (book.status == BookStatus::Borrowed) {
                    book.status = BookStatus::Available;
                    std::cout << "Book returned successfully." << std::endl;
                    return;
                } else {
                    std::cout << "Book was not borrowed." << std::endl;
                    return;
                }
            }
        }
        if (!found) {
            std::cout << "Book does not exist at this library." << std::endl;
        }
    }
        
    

    void searchByTitle(const std::string& title) const {
        for (const auto& book : books) {
            if (book.title.find(title) != std::string::npos) {
                book.display();
            }
        }
    }

    void searchByAuthor(const std::string& author) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                book.display();
                found = true;
                break; // Remove this if you want to find all books by the author
            }
        }
        if (!found) {
            std::cout << "No books found by author: " << author << std::endl;
        }
    }

    void searchByISBN(const std::string& ISBN) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.ISBN == ISBN) {
                book.display();
                found = true;
                break; // Assuming ISBNs are unique
            }
        }
        if (!found) {
            std::cout << "No book found with ISBN: " << ISBN << std::endl;
        }
    }
};

int main() {
    Library library;

    // Predefined list of 10 books
    library.addBook(Book("Trout Fishing", "Sam Smith", "ISBN001"));
    library.addBook(Book("Miami", "Joan Didion", "ISBN002"));
    library.addBook(Book("Water", "Dr. Herbert Gruber", "ISBN003"));
    library.addBook(Book("Winning", "Charlie Sheen", "ISBN004"));
    library.addBook(Book("Tempering Chocolate", "Joy Almond", "ISBN005"));
    library.addBook(Book("Ancient Civilizations", "Edward Norton", "ISBN006"));
    library.addBook(Book("Easy Household Projects", "James Genera", "ISBN007"));
    library.addBook(Book("Neil Young: Waging Heavy Peace", "Bill Bullok", "ISBN008"));
    library.addBook(Book("Dog Breeds of the World", "Isabelle Young", "ISBN009"));
    library.addBook(Book("Earth: A History", "Jude McCartney", "ISBN010"));


    int choice;
    std::string input; // Declare input here
    bool running = true;

    while (running) {
        std::cout << "\nLibrary System Menu:\n";
        std::cout << "1. Check Out Book\n";
        std::cout << "2. Return Book\n";
        std::cout << "3. Search for Book by Title\n";
        std::cout << "4. Search for Book by Author\n";
        std::cout << "5. Search for Book by ISBN\n";
        std::cout << "6. Display All Books\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next newline 
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer after reading choice 



        switch (choice) {
            case 1: {
                int checkoutChoice;
                std::cout << "Check out by:\n1. ISBN\n2. Title\nEnter choice: ";
                std::cin >> checkoutChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                
                if (checkoutChoice ==1) {
                    std::string ISBN;
                    std::cout << "Enter ISBN to check out: "; 
                    std::getline(std::cin, ISBN); // Use getline to allow for ISBNs with hyphens
                    library.checkOutBookByISBN(ISBN);
                } else if (checkoutChoice == 2) {
                    std::string title;
                    std::cout << "Enter title to check out: ";
                    std::getline(std::cin,title);
                    library.checkOutBookByTitle(title);
                } else {
                    std::cout << "Invalid choice.\n";
                }
                break;
            }
            case 2: {
                int returnChoice;
                std::cout << "Return book by:\n1. ISBN\n2. Title\nEnter choice: ";
                std::cin >> returnChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Clear the input
                
                if (returnChoice == 1) {
                    std::cout << "Enter ISBN to return: ";
                    std::getline(std::cin, input); // Use getline to allow for ISBNs w/ hyphens
                    library.returnBookByISBN(input);
                } else if (returnChoice == 2) {
                    std::cout << "Enter title to return: ";
                    std::getline(std::cin, input);
                    library.returnBookByTitle(input);
                } else {
                    std::cout << "Invalid choice.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Enter title to search: ";
                std::cin.ignore(); // Ignore newline left in the input stream
                std::getline(std::cin, input);
                library.searchByTitle(input);
                break;
            }
            case 4: {
                std::cout << "Enter author to search: ";
                std::cin.ignore(); // Ignore newline left in the input stream
                std::getline(std::cin, input);
                library.searchByAuthor(input);
                break;
            }
            case 5: {
                std::cout << "Enter ISBN to search: ";
                std::cin >> input;
                library.searchByISBN(input);
                break;
            }
            case 6: {
                library.displayBooks();
                break;
            }
            case 0: {
                std::cout << "Exiting...\n";
                exit(0);
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
     }   while (choice != 0);

        return 0;   
    }