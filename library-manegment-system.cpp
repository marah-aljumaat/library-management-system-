

#include <iostream>
#include <cstring>//lib to use c style string function
#include <fstream>//file lib
#include <string>

using namespace std;

//global varibles
int count=0;
fstream lib_file;
int MAX_BOOKS = 20;

struct library{
    int book_id;
    char book_author[100];
    char book_name[100];
    int pages;
    float book_price;
    char book_status[100];
};

//functions
bool lib_password(char usern_func[],char pw[]);
void displayBooks(library lib[]);
void addBook(library lib[], int& count);
void saveLibraryData(library lib[]);
void loadLibraryData(library lib[], int& count);
void deleteBook(library lib[], int& count, int book_id);
void issueBookStd(library lib[],int book_id_issue);
void returnBook(library lib[],int book_id_return);


int main(){
int input=0, lib_input=0,std_input=0,book_id_user=0;
char user_pw[10];
char user_name[10];
library lib[MAX_BOOKS];

loadLibraryData(lib,count);

cout<<"-----------------------------------------------------------"<<endl;
cout<<"\t\t\t welcome to our E-library \t\t\t"<<endl;
cout<<"chose from the following:"<<endl;
cout<<"1. Librarian"<<endl;
cout<<"2. student"<<endl;
cout<<"3. exit"<<endl;
cout<<"-----------------------------------------------------------"<<endl;
cin>>input;

if(input == 1){//librarian 
    cout<<"user name:";
    cin>>user_name;
    cout<<"passwoed:";
    cin>>user_pw;

    while(lib_password(user_name,user_pw)){
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<"chose from the following:"<<endl;
        cout<<"1. add book"<<endl;
        cout<<"2. viwe book list"<<endl;
        cout<<"3. delete book"<<endl;
        cout<<"4. return book"<<endl;
        cout<<"5. exit"<<endl;
        cout<<"-----------------------------------------------------------"<<endl;
        cin>>lib_input;

        switch (lib_input)
        {
        case 1://add book
            addBook(lib,count);
            saveLibraryData(lib);
            break;

        case 2://view book list 
        displayBooks(lib);
        break;   

        case 3://delete book
        cout<<"write the book id you want to delete it:";
        cin>>book_id_user;
        deleteBook(lib,count,book_id_user);
        saveLibraryData(lib);
        break;
    
        case 4://return book
        cout<<"write the book id you want to return:";
        cin>>book_id_user;
        returnBook(lib,book_id_user);
        saveLibraryData(lib);
        break;

        case 5:
        //saveLibraryData(lib);
        exit(0);
        break;
        
        default:
        cout<<"invalid number!";
            break;
        }
    }

}else if(input == 2){//student
while (std_input!= 4)
        {
        cout<<"-----------------------------------------------------------"<<endl;
        cout<<"chose from the following:"<<endl;
        cout<<"1. viwe book list"<<endl;
        cout<<"2. issue book"<<endl;
        cout<<"3. return book"<<endl;
        cout<<"4. exit"<<endl;//sonra
        cout<<"-----------------------------------------------------------"<<endl;
        cin>>std_input;

        switch (std_input)
        {
        case 1:// viwe book list
            displayBooks(lib);
            break;

        case 2://issue book
            cout<<"write the book id you want to issue:";
            cin>>book_id_user;
            issueBookStd(lib,book_id_user);
            saveLibraryData(lib);
            break;

        case 3://return book
            cout<<"write the book id you want to return:";
            cin>>book_id_user;
            returnBook(lib,book_id_user);
            saveLibraryData(lib);
            break;      

        case 4:
           // saveLibraryData(lib);
            exit(0);
            break;    
        
        default:
        cout<<"invalid number!";
            break;
        }
        }

}else if(input == 3){//exit
exit(0);
}else{
cout<<"invalid number!";
}
return 0;
}


bool lib_password(char usern_func[],char pw[]){//ok
const char user_name[]="user1234";
const char correct_password[]="pass";

if(strcmp(usern_func,user_name)==0 && strcmp(pw,correct_password)==0){
    return true;
}else{
    return false;
}

}


void addBook(library lib[], int& count){//ok
int n_book,i;
    cout<<"how many books do you want to add: ";
            cin>>n_book;
            count+=n_book;
            cout<<"****enter the following info:****"<<endl;
            
            for(i=0;i<n_book;i++){
            cout<<"-----------------------------------------------------------"<<endl;
            cout<<"book ID: ";
            cin>>lib[i].book_id;

            cout<<"book author name: ";
            cin.ignore();// Clear the newline character from the input buffer
            gets(lib[i].book_author);

            cout<<"book name: ";
            //cin.ignore();// Clear the newline character from the input buffer
            gets(lib[i].book_name);

            cout<<"pages: ";
            cin>>lib[i].pages;

            cout<<"book price: ";
            cin>>lib[i].book_price;

            cout<<"book status (available/issued): ";
            cin>>lib[i].book_status;
            
            }
}

void displayBooks(library lib[]){//ok
    int i;
    for(i=0;i<count;i++){
    cout<<"-------------------------------"<<endl;
    cout<<"book code: "<<lib[i].book_id<<endl;
    cout<<"author: "<<lib[i].book_author<<endl;
    cout<<"book name: "<<lib[i].book_name<<endl;
    cout<<"price: "<<lib[i].pages<<endl;
    cout<<"price: "<<lib[i].book_price<<"$"<<endl;
    cout<<"book status: "<<lib[i].book_status<<endl;
    
}
}

void saveLibraryData(library lib[]){
int i;
lib_file.open("library_file.txt",ios::out);
if(lib_file.is_open()){
    for(i=0;i<count;i++){
        lib_file<<lib[i].book_id<<","<<lib[i].book_author<<","<<lib[i].book_name<<","<<lib[i].pages<<","<<lib[i].book_price<<","<<lib[i].book_status<<endl;
    }
    lib_file.close();
    cout<<"Library data saved " << endl;
}else{
    cout<<"Unable to open file. "<< endl;
}
}

void loadLibraryData(library lib[], int& count) {
    lib_file.open("library_file.txt", ios::in);
    if (lib_file.is_open()) {
        while (count < MAX_BOOKS && lib_file >> lib[count].book_id) {
            lib_file.ignore();  // ignore the comma
            lib_file.getline(lib[count].book_author, 100, ',');
            lib_file.getline(lib[count].book_name, 100, ',');
            lib_file >> lib[count].pages;
            lib_file.ignore();  // ignore the comma
            lib_file >> lib[count].book_price;
            lib_file.ignore();  // ignore the comma
            lib_file.getline(lib[count].book_status, 20);
            count++;// Update the count of books loaded
        }
        lib_file.close();
        cout << "Library data loaded" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}



void deleteBook(library lib[], int& count, int book_id) {
    int i, index = -1;
    // Find the index of the book with the given book_id
    for (int i = 0; i < count; i++) {
        if (lib[i].book_id == book_id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Shift all elements after the deleted book to the left
        for (int i = index; i < count - 1; i++) {
            lib[i] = lib[i + 1];
        }

        // Decrement the count of books
        count--;

        cout << "Book with ID " << book_id << " deleted successfully." << endl;
    } else {
        cout << "Book with ID " << book_id << " not found." << endl;
    }
}

void issueBookStd(library lib[], int book_id_issue) {
    int i, book_index = -1; // Initialize to -1 to indicate book not found

    // Find the index of the book with the given book_id
    for (int i = 0; i < count; i++) {
        if (lib[i].book_id == book_id_issue) {
            book_index = i;
            break;
        }
    }

    // Check if the book is found
    if (book_index != -1) {
        // Check if the book is already issued
        if (strcmp(lib[book_index].book_status, "issued") == 0) {
            cout << "The book is already issued." << endl;
        } else {
            // Mark the book as issued
            strcpy(lib[book_index].book_status, "issued");
            cout << "You have borrowed this book. Don't forget to return it." << endl;
        }
    } else {
        cout << "Book with ID " << book_id_issue << " not found." << endl;
    }
}

void returnBook(library lib[], int book_id_return) {
    int i, book_index = -1; // Initialize to -1 to indicate book not found

    // Find the index of the book with the given book_id
    for (int i = 0; i < count; i++) {
        if (lib[i].book_id == book_id_return) {
            book_index = i;
            break;
        }
    }

    // Check if the book is found
    if (book_index != -1) {
        // Check if the book is already available
        if (strcmp(lib[book_index].book_status, "available") == 0) {
            cout << "The book is already in the library." << endl;
        } else {
            // Mark the book as available
            strcpy(lib[book_index].book_status, "available");
            cout << "You have returned the book successfully." << endl;
        }
    } else {
        cout << "Book with ID " << book_id_return << " not found." << endl;
    }
}