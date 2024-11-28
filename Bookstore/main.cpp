#include<iostream>
#include<fstream>
#include<string>
#include <limits>

using namespace std;

// Book
struct Book {
    string title;
    string author;
    int quantity;
    double price;
};

// Sales
struct Sale {
    string title;
    int quantitySold;
    double totalPrice;
};

// User credentials
struct User {
    string username;
    string password;
};

// Company
struct Company {
    string name;
    string address;
    string contact;
};

// Function
void displayMenu();
void viewBookDetails();
void addBook();
void updateBook();
void deleteBook();
void manageSales();
void userLogin();
void viewCompanyDetails();

// Main function
int main() {
    userLogin();

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewBookDetails();
                break;
            case 2:
                addBook();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                manageSales();
                break;
            case 6:
                viewCompanyDetails();
                break;
            case 7:
                cout << "Logging out...\n";
                cout << "\n";
                userLogin();
                break;
            case 8:
                cout << "Exiting the application...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}

// Main menu
void displayMenu() {
    cout << "\n========== GENIUS BOOKS MANAGEMENT SYSTEM ==========\n";
    cout << "1. View available book details\n";
    cout << "2. Add a new book\n";
    cout << "3. Update book details\n";
    cout << "4. Delete a book\n";
    cout << "5. Manage sales\n";
    cout << "6. View company details\n";
    cout << "7. Logout\n";
    cout << "8. Exit\n";
}

// View book
void viewBookDetails() {
    ifstream inFile("book_details.txt");

    if (!inFile) {
        cout << "Book not found.\n";
        return;
    }

    cout << "========== Available Book Details ==========\n";
    cout << "Title\t\tAuthor\t\tQuantity\tPrice\n";

    while (!inFile.eof()) {
        Book book;
        getline(inFile, book.title, ',');
        if (inFile.eof()) break;  // Stop if end of file is reached after title
        getline(inFile, book.author, ',');
        inFile >> book.quantity;
        inFile.ignore();  // Ignore the comma
        inFile >> book.price;
        inFile.ignore();  // Ignore the newline

        // Display book details
        cout << book.title << "\t\t" << book.author << "\t\t" << book.quantity << "\t\t" << book.price << "\n";
    }

    inFile.close();
}

// Add a new book
void addBook() {
    ofstream outFile("book_details.txt", ios::app);

    if (!outFile) {
        cout << "Error opening file.\n";
        return;
    }

    Book newBook;

    cin.ignore();

    cout << "Enter book title: ";
    getline(cin, newBook.title);

    cout << "Enter book author: ";
    getline(cin, newBook.author);

    cout << "Enter quantity: ";
    cin >> newBook.quantity;

    cout << "Enter price: ";
    cin >> newBook.price;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    outFile << newBook.title << ',' << newBook.author << ',' << newBook.quantity << ',' << newBook.price << '\n';

    cout << "New book added successfully.\n";

    outFile.close();
}

// Update book
void updateBook() {
    ifstream inFile("book_details.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "Error opening files.\n";
        return;
    }

    string searchTitle;
    cout << "Enter the title of the book to update: ";
    cin.ignore();
    getline(cin, searchTitle);

    bool found = false;

    while (!inFile.eof()) {
        Book book;
        getline(inFile, book.title, ',');
        if (inFile.eof()) break;
        getline(inFile, book.author, ',');
        inFile >> book.quantity;
        inFile.ignore();
        inFile >> book.price;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (book.title == searchTitle) {
            cout << "Enter new quantity: ";
            cin >> book.quantity;

            cout << "Enter new price: ";
            cin >> book.price;

            found = true;
        }

        tempFile << book.title << ',' << book.author << ',' << book.quantity << ',' << book.price << '\n';
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("book_details.txt");
        rename("temp.txt", "book_details.txt");
        cout << "Book details updated successfully.\n";
    } else {
        cout << "Book not found.\n";
        remove("temp.txt");
    }
}

// Delete a book
void deleteBook() {
    ifstream inFile("book_details.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "Error opening files.\n";
        return;
    }

    string deleteTitle;
    cout << "Enter the title of the book to delete: ";
    cin.ignore();
    getline(cin, deleteTitle);

    bool found = false;

    while (!inFile.eof()) {
        Book book;
        getline(inFile, book.title, ',');
        if (inFile.eof()) break;
        getline(inFile, book.author, ',');
        inFile >> book.quantity;
        inFile.ignore();
        inFile >> book.price;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (book.title == deleteTitle) {
            found = true;
        } else {
            tempFile << book.title << ',' << book.author << ',' << book.quantity << ',' << book.price << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("book_details.txt");
        rename("temp.txt", "book_details.txt");
        cout << "Book deleted successfully.\n";
    } else {
        cout << "Book not found.\n";
        remove("temp.txt");
    }
}

// Manage sales
void manageSales() {
    ifstream inFile("book_details.txt");
    ofstream tempFile("temp.txt");

    if (!inFile || !tempFile) {
        cout << "Error opening files.\n";
        return;
    }

    string saleTitle;
    int soldQuantity;

    cout << "Enter the title of the book for sale: ";
    cin.ignore();
    getline(cin, saleTitle);

    cout << "Enter the quantity sold: ";
    cin >> soldQuantity;

    bool found = false;

    while (!inFile.eof()) {
        Book book;
        getline(inFile, book.title, ',');
        if (inFile.eof()) break;
        getline(inFile, book.author, ',');
        inFile >> book.quantity;
        inFile.ignore();
        inFile >> book.price;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (book.title == saleTitle) {
            if (book.quantity >= soldQuantity) {
                book.quantity -= soldQuantity;
                found = true;
            } else {
                cout << "Error: Not enough quantity available for sale.\n";
            }
        }

        tempFile << book.title << ',' << book.author << ',' << book.quantity << ',' << book.price << '\n';
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("book_details.txt");
        rename("temp.txt", "book_details.txt");
        cout << "Sale processed successfully.\n";
    } else {
        cout << "Book not found.\n";
        remove("temp.txt");
    }
}

// User login
void userLogin() {
    string enteredUsername, enteredPassword;

    cout << "Enter username: ";
    cin >> enteredUsername;

    cout << "Enter password: ";
    cin >> enteredPassword;

    if (enteredUsername == "admin" && enteredPassword == "1234") {
        cout << "Default login successful.\n";
    } else {
        cout << "Invalid username or password. Try again.\n";
        cout << "\n";
        userLogin();
    }
}

// Company details
void viewCompanyDetails() {
    Company defaultCompany;
    defaultCompany.name = "Genius Books";
    defaultCompany.address = "Colombo, Srilanka";
    defaultCompany.contact = "Contact: 0777123456";

    cout << "========== Company Details ==========\n";
    cout << "Name: " << defaultCompany.name << "\n";
    cout << "Address: " << defaultCompany.address << "\n";
    cout << defaultCompany.contact << "\n";
}