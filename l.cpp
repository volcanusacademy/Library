#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Library {
public:
    string Title;
    int status;
    Library() {
        cout << "\n Welcome to Volcanus Library";
    }
    Library(string title, int st) {
        this->Title = title;
        this->status = st;
    }
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
            file << Title << "," << author << "," << year << "," << status << endl;
            file.close();
            cout << "Book added successfully!" << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
        
    }
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

            remove("books.txt");
            rename("temp.txt", "books.txt");

            if (!found) {
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Unable to open file." << endl;
        }
    }
    void IssueBook() {
        string issueTitle;
        int days;
        cout << "Enter the title of the book to issue: ";
        cin.ignore(); // Ignore any previous newline characters
        getline(cin, issueTitle); // Allowing for titles with spaces

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
                    outFile << issueTitle << "," << token << "," << days << endl;
                    cout << "Book '" << issueTitle << "' issued successfully for " << days << " days." << endl;
                } else {
                    outFile << line << endl;
                }
            }
            inFile.close();
            outFile.close();

            if (!found) {
                cout << "Book not found." << endl;
            } else {
                remove("books.txt");
                rename("temp.txt", "books.txt");
            }
        } else {
            cout << "Unable to open files." << endl;
        }
    }
    void ReturnBook() {
         string returnTitle;
        cout << "Enter the title of the book to return: ";
        cin.ignore(); // Ignore any previous newline characters
        getline(cin, returnTitle); // Allowing for titles with spaces

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
                    getline(ss, token, ','); // Days
                    token = "0"; // Setting status to 0 (available)
                    outFile << returnTitle << "," << token << endl;
                    cout << "Book '" << returnTitle << "' returned successfully." << endl;
                } else {
                    outFile << line << endl;
                }
            }
            inFile.close();
            outFile.close();

            if (!found) {
                cout << "Book not found." << endl;
            } else {
                remove("books.txt");
                rename("temp.txt", "books.txt");
            }
        } else {
            cout << "Unable to open files." << endl;
        }
    }
        // Change the status to 0
    
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
    Library l;
    l.Operate();
    return 0;
}