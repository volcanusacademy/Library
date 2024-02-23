#include <iostream>       //iostream used for input-output
#include <fstream>       //fstream used for read and write file
#include <vector>       //itrators resize
#include <string>       //string used for store text & characters
using namespace std;    //declarative part
class Library{          //create  library classs
private:
    string Title;       //string representing the title of a book
    int status;         //availability status of a book (0 for available, >0 for issued)
public:
//Constructor method to initialize the library management system.
    Library() {
        cout << " Welcome Library Management System\n";
 }
//Parameterized constructor to initialize book title and status.
 Library(string Title, int status) : Title(Title), status(status) {}
       void AddBook() {     //Method to add a new book to the library.
       cout << "Enter Book Title: ";   //enter the title of the book.
       cin.ignore();    //Ignore any leftover characters in the input buffer.
       getline(cin, Title);// Read the entire line of input, allowing for spaces in the title, and store it in the Title attribute.
       status = 0;                // status of the book to 0, indicating that it is available.
       ofstream outFile("books.txt", ios::app);  //Open the "books.txt" file in append mode.
        if (outFile.is_open()) {  // book title and its status to the file, separated by a comma.
            outFile << Title << "," << status << endl;
            outFile.close();   //Close the file after writing.
            cout << "Book added successfully.\n";
        } else {
            cout << " Unable to open file.\n";
        }
    }
    void searchBook() {        //Method to search for a book by title or author.
        cout << "Enter book title or author name to search: ";//user to enter the search bookname
        string search;          //string variable to store the user search bookname
        cin.ignore();
        getline(cin, search);   //Reading the entire line of input, including spaces, into the 'search' variable.
        ifstream inFile("books.txt");  //Opening the file "books.txt" for reading
        if (inFile.is_open()) {        //Checking if the file was successfully opened
            string line;
            bool found = false;        //indicate if the book was found or not
            while (getline(inFile, line)) {  //Looping through each line of the file
                if (line.find(search) != string::npos) {   //Checking if the current line contains the search book
                    cout << "Book found: " << line << endl; //search book is found in the current line, printing the line
                    found = true;                 //indicate that the book was found
                }
            }
            inFile.close();  //Closing the file after reading.
            if (!found) {
                cout << "Book not found.\n";
            }
        } else {
            cout << " Unable to open file.\n";
        }
    }
    void RemoveBook() {     //Method to remove a book from the library.
        cout << "Enter Book Title to Remove: ";
        string removeTitle;
        cin.ignore();
        getline(cin, removeTitle);
        vector<string> temp;
        ifstream inFile("books.txt");    // Opening the file "books.txt" for reading
        if (inFile.is_open()) {
            string line;
            bool found = false;
            while (getline(inFile, line)) {
                if (line.find(removeTitle) != string::npos) {
                    found = true;
                } else {
                    temp.push_back(line);
                }
            }
            inFile.close();
            if (found) {
                ofstream outFile("books.txt");
                for (const auto& book : temp) {
                    outFile << book << endl;
                }
                outFile.close();
                cout << "Book removed successfully.\n";
            } else {
                cout << "Book not found.\n";
            }
        } else {
            cout << " Unable to open file.\n";
        }
    }
    void IssueBook() {         //Method to issue a book from the library to a borrower
        cout << "Enter Book Title to Issue: ";
        string issueTitle;
        cin.ignore();
        getline(cin, issueTitle);
        ifstream inFile("books.txt");
        vector<string> lines;       //Vector to hold each line of the file
        if (inFile.is_open()) {
            string line;
            bool found = false;
            while (getline(inFile, line)) {   // Read each line of the file
                if (line.find(issueTitle) != string::npos) { //Check if the line contains the entered book title
                    int bookStatus = stoi(line.substr(line.find_last_of(',') + 1));
                    if (bookStatus == 0) {  //If the book is available (status 0)
                        int days;
                        cout << "Enter number of days until return: ";
                        cin >> days;
                        line.replace(line.find_last_of(',') + 1, string::npos, to_string(days));
                        found = true;
                    } else {
                        cout << "Book is already issued.\n";
                    }
                }
                lines.push_back(line);
            }
            inFile.close();
            ofstream outFile("books.txt");
            for (const auto& book : lines) {
                outFile << book << endl;
            }
            outFile.close();
            if (!found) {
                cout << "Book not found.\n";
            }
        } else {
            cout << " Unable to open file.\n";
        }
    }
    void ReturnBook() {     //Method to return a borrowed book to the library
        cout << "Enter Book Title to Return: ";
        string returnTitle;
        cin.ignore();
        getline(cin, returnTitle);
        ifstream inFile("books.txt");  //Open the file containing information about books
        vector<string> lines;          //Vector to hold each line of the file
        if (inFile.is_open()) {        //Check if file opened successfully
            string line;
            bool found = false;
            while (getline(inFile, line)) {
                if (line.find(returnTitle) != string::npos) {
                    //Extract the status of the book (whether it's available or already issued)
                    int bookStatus = stoi(line.substr(line.find_last_of(',') + 1));
                    if (bookStatus > 0) {
                        line.replace(line.find_last_of(',') + 1, string::npos, "0");
                        found = true;
                    } else {
                        cout << "Book is not issued.\n";
                    }
                }
                lines.push_back(line);
            }
            inFile.close();  //Close the input file
            ofstream outFile("books.txt");
            for (const auto& book : lines) {
                outFile << book << endl;
            }
            outFile.close();   //Close the output file
            if (!found) {
                cout << "Book not found.\n"; //If the book was not found in the file, inform the user
            }
        } else {
            cout << "Unable to open file.\n"; //If unable to open the file, inform the user
        }
    }
    void operate() {  //Method to operate the lib by displaying a menu and processing user input.
        int choice;
        do {        //Display menu options
            cout << "\nLibrary Management System Menu:\n";
            cout << "1. Add Book\n";
            cout << "2. Search Book\n";
            cout << "3. Remove Book\n";
            cout << "4. Issue Book\n";
            cout << "5. Return Book\n";
            cout << "6. Exit\n";
            cout << "Please select an option: ";
            cin >> choice;              // user to select an option
            switch (choice) {            // Switch statement to handle user's choice
                case 1:
                    AddBook();          //Call method to add a book
                    break;
                case 2:
                    searchBook();       //Call method to search for a book
                    break;
                case 3:
                    RemoveBook();       // Call method to remove a book
                    break;
                case 4:
                    IssueBook();        //Call method to issue a book
                    break;
                case 5:
                    ReturnBook();       //Call method to return a book
                    break;
                case 6:
                    cout << "Exiting Library Management System.\n";
                    break;
                default:
                    cout << "Please try again.\n";
            }
        } while (choice != 6);        //Repeat the loop until user chooses to exit
    }
};
int main() {
    Library lib;        //instance of the Library class
    lib.operate();      //It creates an instance of the Library class and calls its operate()
    return 0;
}