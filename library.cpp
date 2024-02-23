#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Class definition for Library
class Library {
public:
    string Title;   // Member variable to store the title of a book
    int status;     // Member variable to store the status of a book (e.g., available or issued)

    // Default constructor for Library
    Library() {
        cout << "\n Welcome to Volcanus Library";
    }

    // Parameterized constructor for Library
    Library(string title, int st) {
        this->Title = title;
        this->status = st;
    }

    // Function to add a book to the library
    void AddBook() {
        string author;
        int year;

        cout << "\nEnter the title of the book: ";
        cin >> Title;
        cout << "Enter the author of the book: ";
        cin >> author;
        cout << "Enter the publication year of the book: ";
        cin >> year;

        // Open the file in append mode
        ofstream file("books.txt", ios::app);
        if (file.is_open()) {
            // Write book information to the file in CSV format
            file << Title << "," << author << "," << year << "," << status << endl;
            file.close();
            cout << "Book added successfully!" << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to search for a book by title or author's name
    void SearchBook() {
        string searchKey;
        cout << "Enter the title or author's name to search: ";
        cin >> searchKey;

        ifstream file("books.txt");
        if (file.is_open()) {
            string line;
            bool found = false;
            while (getline(file, line)) {
                if (line.find(searchKey) != string::npos) {
                    cout << "Book found: " << line << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Book not found." << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to remove a book from the library
    void RemoveBook() {
        string removeTitle;
        cout << "Enter the title of the book to remove: ";
        cin.ignore(); // Ignore any previous newline characters
        getline(cin, removeTitle); // Allowing for titles with spaces

        ifstream file("books.txt");
        ofstream temp("temp.txt");
        if (file.is_open() && temp.is_open()) {
            string line;
            bool found = false;
            while (getline(file, line)) {
                if (line.find(removeTitle) != string::npos) {
                    found = true;
                    cout << "Book removed: " << line << endl;
                } else {
                    temp << line << endl;
                }
            }
            file.close();
            temp.close();

            // Remove the original file and rename the temporary file
            remove("books.txt");
            rename("temp.txt", "books.txt");

            if (!found) {
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    // Function to issue a book from the library
    void IssueBook() {
        string issueTitle;
        int days;

        cout << "Enter the title of the book to issue: ";
        cin.ignore();
        getline(cin, issueTitle);

        // Check if the book is already issued
        ifstream checkFile("books.txt");
        if (checkFile.is_open()) {
            string line;
            while (getline(checkFile, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ','); // Title
                if (token == issueTitle) {
                    getline(ss, token, ','); // Author
                    int bookStatus;
                    ss >> bookStatus; // Read the status
                    if (bookStatus != 0) {
                        cout << "Sorry, the book '" << issueTitle << "' is already issued and not available for further issuance.\n";
                        checkFile.close();
                        return;
                    }
                }
            }
            checkFile.close();
        } else {
            cout << "Unable to open file.\n";
            return;
        }

        cout << "Enter the number of days to issue: ";
        cin >> days;

        ifstream inFile("books.txt");
        ofstream outFile("temp.txt");

        if (inFile.is_open() && outFile.is_open()) {
            string line;
            bool found = false;

            while (getline(inFile, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ','); // Title

                if (token == issueTitle) {
                    found = true;
                    getline(ss, token, ','); // Author
                    // Update status to indicate that the book is issued
                    outFile << issueTitle << "," << token << "," << days << endl;
                    cout << "Book '" << issueTitle << "' issued successfully for " << days << " days.\n";
                } else {
                    outFile << line << endl;
                }
            }

            inFile.close();
            outFile.close();

            remove("books.txt");
            rename("temp.txt", "books.txt");

            if (!found) {
                cout << "Book not found.\n";
            }
        } else {
            cout << "Unable to open files.\n";
        }
    }

    // Function to return a book to the library (placeholder, not implemented in this code)
     void ReturnBook() {
        string returnTitle;
        cout << "Enter the title of the book to return: ";
        cin.ignore();
        getline(cin, returnTitle);

        ifstream inFile("books.txt");
        ofstream outFile("temp.txt");

        if (inFile.is_open() && outFile.is_open()) {
            string line;
            bool found = false;

            while (getline(inFile, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ','); // Title

                if (token == returnTitle) {
                    found = true;
                    getline(ss, token, ','); // Author
                    int days;
                    ss >> days; // Read the remaining part as an integer (assumes days is the last part)
                    
                    // Update status to indicate that the book is available
                    outFile << returnTitle << "," << token << "," << 0 << endl;
                    cout << "Book '" << returnTitle << "' returned successfully.\n";
                } else {
                    outFile << line << endl;
                }
            }

            inFile.close();
            outFile.close();

            remove("books.txt");
            rename("temp.txt", "books.txt");

            if (!found) {
                cout << "Book not found.\n";
            }
        } else {
            cout << "Unable to open files.\n";
        }
    }

    // Function to operate the Library Management System menu
    void Operate() {
        int choice;
        do {
            cout << "\nLibrary Management System Menu:\n";
            cout << "1. Add Book\n";
            cout << "2. Search Book\n";
            cout << "3. Remove Book\n";
            cout << "4. Issue Book\n";
            cout << "5. Return Book\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    AddBook();
                    break;
                case 2:
                    SearchBook();
                    break;
                case 3:
                    RemoveBook();
                    break;
                case 4:
                    IssueBook();
                    break;
                case 5:
                    ReturnBook();
                    break;
                case 6:
                    cout << "Exiting... Thank you!\n";
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option.\n";
                    break;
            }
        } while (choice != 6);
    }
};

int main() {
    Library l; // Create an object of the Library class
    l.Operate(); // Call the Operate function to start the Library Management System
}