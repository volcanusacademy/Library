#include <iostream>
#include <fstream>
#include <sstream> //string stream operations 
#include <string>  //string manipulation
using namespace std;

class Library 
{
 public:
    string Title;   // Declare a string variable to store the title of the book
    int status;      // Declare an integer variable to store the status of the book
    Library() 
    {     //constractor
        cout << "\n Welcome to Volcanus Library";
    }
    Library(string title, int st) 
    {
        this->Title = title;   // Initialize Title 
        this->status = st;// Initialize status 
    }
    void AddBook()
    {
        string author;
        int year;

        cout << "\nEnter the title of the book: ";
        cin >> Title;
        cout << "Enter the author of the book: ";
        cin >> author;
        cout << "Enter the publication year of the book: ";
        cin >> year;

        // Open the file in append mode
        ofstream file("books.txt", ios::app); // create a file and ios::app is for restoring given information about book 
        if (file.is_open()) 
        {                     
            file << Title << "," << author << "," << year << "," << status << "\n";
            file.close();                              // Close the file
            cout << "Book added successfully!\n";
        } else
        {
            cout << "Unable to open file.\n";
        }
        
    }
    void SearchBook() 
    {
        string searchKey;
        cout << "Enter the title or author's name to search: ";
        cin >> searchKey;

        ifstream file("books.txt");   // Open the file for reading
        if (file.is_open()) 
        {
            string line;
            bool found = false;
            while (getline(file, line))
            {          // Read each line of the file
                if (line.find(searchKey) != string::npos) 
                {        // Check if search key is found in the line
                    cout << "Book found: " << line << "\n";
                    found = true;
                }
            }
            if (!found) 
            {
                cout << "Book not found.\n";
            }
            file.close();               // Close the file
        } else 
        {
            cout << "Unable to open file.\n";
        }
    }
    void RemoveBook() 
    {
        string removeTitle;
        cout << "Enter the title of the book to remove: ";
        cin.ignore(); // Ignore any previous newline characters
        getline(cin, removeTitle); // Allowing for titles with spaces

        ifstream file("books.txt");             // Open the file for reading
        ofstream temp("temp.txt");              // Create a temporary file for writing


        if (file.is_open() && temp.is_open()) 
        {
            string line;
            bool found = false;
            while (getline(file, line))
            {
                if (line.find(removeTitle) != string::npos) 
                {   // Check if removeTitle is found in the line
                    found = true;
                    cout << "Book removed: " << line << "\n";   // Display the removed book
                } else 
                {
                    temp << line << "\n";              // Write the line to the temporary file
                }
            }
            file.close();          // Close the original file
            temp.close();           // Close the temporary file

            remove("books.txt");              // Remove the original file
            rename("temp.txt", "books.txt");     // Rename the temporary file to the original file

            if (!found)
            {
                cout << "Book not found." << "\n";  // Display message if book is not found
            }
            
        } 
        else 
        {
            cout << "Unable to open file.\n"; // Display error message if file cannot be opened
        }
    }
    void IssueBook() 
    {
        string issueTitle;
        int days;
        cout << "Enter the title of the book to issue: ";
        cin.ignore(); // Ignore any previous newline characters
        getline(cin, issueTitle); // Allowing for titles with spaces

        cout << "Enter the number of days to issue: ";
        cin >> days;

        ifstream inFile("books.txt");
        ofstream outFile("temp.txt");       // Create a temporary file for writing

        if (inFile.is_open() && outFile.is_open()) 
        {
            string line;
            bool found = false;
            while (getline(inFile, line)) 
            {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');  // Extract the title from the line
                if (token == issueTitle) {          // Check if the title matches the issueTitle
                    found = true;
                    getline(ss, token, ',');     // Extract the author from the line
                    outFile << issueTitle << "," << token << "," << days << "\n"; // Write updated line to temporary file
                    cout << "Book '" << issueTitle << "' issued successfully for " << days << " days.\n";
                }
                else 
                {
                    outFile << line << "\n";        // Write the unchanged line to the temporary file
                }
            }
            inFile.close();
            outFile.close();

            if (!found)
            {
                cout << "Book not found." << endl;
            } else 
            {
                remove("books.txt");
                rename("temp.txt", "books.txt");
            }
        }
        else
        {
            cout << "Unable to open files.\n";
        }
    }
    void ReturnBook() 
    {
         string returnTitle;
        cout << "Enter the title of the book to return: ";
        cin.ignore(); // Ignore any previous newline characters
        getline(cin, returnTitle); // Allowing for titles with spaces

        ifstream inFile("books.txt");
        ofstream outFile("temp.txt");

        if (inFile.is_open() && outFile.is_open())
        {
            string line;
            bool found = false;
            while (getline(inFile, line))
            {
                stringstream ss(line);
                string token;
                getline(ss, token, ','); // Title
                if (token == returnTitle)
                {
                    found = true;
                    getline(ss, token, ','); // Author
                    getline(ss, token, ','); // Days
                    token = "0"; // Setting status to 0 (available)
                    outFile << returnTitle << "," << token << endl;
                    cout << "Book '" << returnTitle << "' returned successfully." << endl;
                } else 
                {
                    outFile << line << endl;
                }
            }
            inFile.close();
            outFile.close();

            if (!found) 
            {
                cout << "Book not found." << endl;
            } 
            else 
            {
                remove("books.txt");
                rename("temp.txt", "books.txt");
            }
        } 
        else
        {
            cout << "Unable to open files." << endl;
        }
    }
        // Change the status to 0
    
    void Operate()
    {
        int choice;
        do 
        {
            cout << "\nLibrary Management System Menu:\n";
            cout << "1. Add Book\n";
            cout << "2. Search Book\n";
            cout << "3. Remove Book\n";
            cout << "4. Issue Book\n";
            cout << "5. Return Book\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    AddBook();     //call the function
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

int main()
{
    Library l;   // Create a Library object
    l.Operate();   // Call Operate() method to start the library management system
    return 0;
}
