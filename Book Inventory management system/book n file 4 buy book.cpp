#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
/*Book Inventory System made by Vivek Kumar Thakur(2K20/CO/493) and
Yash Munde(2K20/CO/499)*/
using namespace std;
class book
{
private:
    char author[20], title[20], publisher[20], bookID[13];
    float price;
    int stock;

public:
    book() //Constructor
    {
        strcpy(author, "NULL");
        strcpy(title, "NULL");
        strcpy(publisher, "NULL");
        strcpy(bookID, "NULL");
        price = 0;
        stock = 0;
    }
    void feeddata();
    void feeddata(char *, char *, char *, int, int);//overloaded function
    void showdata();
    void generatebookID();
    int storebook();
    void stock_report();
    void search_title(char *);
    void search_bookID(char *);
    void delete_book(char *);
    void update_data(char *);
    void update_stocks(int);
    void buy_book(int, char *);
};

void book::feeddata(char *au, char *ti, char *pu, int pr, int st)
{
    strcpy(author, au);
    strcpy(title, ti);
    strcpy(publisher, pu);
    generatebookID();
    price = pr;
    stock = st;
}
void book::update_stocks(int noc)
{
    stock = stock - noc;
}
void book::buy_book(int noc, char *ti)
{
    fstream file;
    file.open("bookfile.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0); //brings pointer from end to beginning
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        /*if (strcmp(ti, title) != 0)
        {
            cout << "\nBook not found";
            break;
        }
        else*/
        if (strcmp(ti, title) == 0)
        {
            cout << "\nBOOK FOUND";
            if (noc < stock)
            {
                cout << "\nSUFFICIENT COPIES ARE AVAILABLE";
                /*update_stocks(noc);
                int cost = noc * price;
                cout << "\n\nYou have to pay Rs. " << cost;
                //int cost = noc * price;
                int count = (int)file.tellp() - sizeof(*this); //+ sizeof(this->author) + sizeof(this->title) + sizeof(this->publisher) + sizeof(this->bookID); //check it
                file.seekp(count);
                file.write((char *)this->stock, sizeof(this->stock)); //check it
                //cout << "You have to pay Rs. " << cost;*/
                char au[20], ti[20], pu[20];
                int pr, st;
                strcpy(au, author);
                strcpy(ti, title);
                strcpy(pu, publisher);
                pr = price;
                st = stock - noc;
                feeddata(au, ti, pu, pr, st); //this is called for collar object
                int count = (int)file.tellp() - sizeof(*this);
                file.seekp(count); //when we read a record file
                //pointer begins to point the next record, so we need to bring it back
                //by one record
                //file.tellp() tells where the file pointer is currently
                file.write((char *)this, sizeof(*this));
                cout << "\nRecord updated successfully";
                int cost = noc * price;
                cout << "\n\nYOU HAVE TO PAY Rs. " << cost;
                break;
            }
            
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
}
void book::update_data(char *ti)
{
    fstream file;
    file.open("bookfile.txt", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0); // 0 bytes ahead of beginning
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        if (strcmp(ti, title) == 0)
        {
            cout << "\nBook found";
            feeddata(); //this is called for collar object
            int count = (int)file.tellp() - sizeof(*this);
            file.seekp(count); //when we read a record file
            //pointer begins to point the next record, so we need to bring it back
            //by one record
            //file.tellp() tells where the file pointer is currently
            file.write((char *)this, sizeof(*this));
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
}
void book::delete_book(char *ti)
{
    ifstream fin;
    ofstream fout;
    fin.open("bookfile.txt", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found";
    }
    else
    {
        fout.open("newfile.txt", ios::app | ios::out | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (strcmp(ti, title) != 0)
            {
                fout.write((char *)this, sizeof(*this)); //writing to new file
            }
            fin.read((char *)this, sizeof(*this)); //pointing to next record in bookfile
        }
        fin.close();
        fout.close();
        remove("bookfile.txt");
        rename("newfile.txt", "bookfile.txt");
    }
}
void book::search_title(char *ti)
{
    int n = 0;
    ifstream fin;
    fin.open("bookfile.txt", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (strcmp(ti, title) == 0)
            {
                cout << "Book found!";
                showdata();
                n++;
                break;
            }
            fin.read((char *)this, sizeof(*this)); //internally points to the next record automatically
        }
        if (n == 0)
        {
            cout << "Book not found";
        }
        fin.close();
    }
}
void book::search_bookID(char *ID)
{
    int n = 0;
    ifstream fin;
    fin.open("bookfile.txt", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (strcmp(ID, bookID) == 0)
            {
                cout << "Book found!";
                showdata();
                n++;
                break;
            }
            fin.read((char *)this, sizeof(*this)); //internally points to the next record automatically
        }
        if (n == 0)
        {
            cout << "Book not found";
        }
        fin.close();
    }
}
void book::feeddata()
{
    cin.ignore();
    cout << "\nEnter Author Name: ";
    cin.getline(author, 20); //getline assigns data to author; 20 indicates permitted size
    cout << "Enter Title Name: ";
    cin.getline(title, 20);
    cout << "Enter Publisher Name: ";
    cin.getline(publisher, 20);
    generatebookID();
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Stock Position: ";
    cin >> stock;

    cout << "Book ID successfully generated : " << bookID;
}
void book::showdata()
{
    cout << "\nAuthor Name: " << author;
    cout << "\nTitle Name: " << title;
    cout << "\nPublisher Name: " << publisher;
    cout << "\nPrice: " << price;
    cout << "\nStock Position: " << stock;
    cout << "\nBook ID: " << bookID;
}
void book::generatebookID()
{
    for (int i = 0; i < 4; i++)
    {
        *(bookID + i) = *(author + i);
    }
    for (int i = 4; i < 8; i++)
    {
        *(bookID + i) = *(title + i - 4);
    }
    for (int i = 8; i < 13; i++)
    {
        *(bookID + i) = *(publisher + i - 8);
    }
}
void book::stock_report()
{
    ifstream fin;
    fin.open("bookfile.txt", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFile not found";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            cout << "\n";
            showdata();
            fin.read((char *)this, sizeof(*this)); //internally points to the next record automatically
        }
        fin.close();
    }
}
int book::storebook()
{
    if (strcmp(title, "NULL") == 0)
    {
        cout << "\nBook data not found";
        return (0);
    }
    else
    {
        ofstream fout;
        fout.open("bookfile.txt", ios::app | ios::binary);
        fout.write((char *)this, sizeof(*this));
        /*(address of collar object,size of collar object*/
        fout.close();
        return (1);
    }
}
/*int menu()
{
    cout << "\nBOOK MANAGEMENT";
    cout << "\n1. Insert a book";
    cout << "\n2. View stock report";
    cout << "\n3. Search a book";
    cout << "\n4. Delete a book";
    cout << "\n5. Edit a record";
    cout << "\n6. Buy a book";
    cout << "\n7. Exit";
    int choice;
    cout << "\nEnter a choice";
    return choice;
}*/
int main()
{
    book b1;
    char title[20];
    int choice;
    while (1)
    {
        cout << "\n";
        cout << "\n\t\t\t\t------------------------------";
        cout << "\n\t\t\t\t|            MENU            |"
             << "\n\t\t\t\t|  1. Entry of New Book      |"
             << "\n\t\t\t\t|  2. View stock report      |"
             << "\n\t\t\t\t|  3. Search For Book        |"
             << "\n\t\t\t\t|  4. Delete a record        |"
             << "\n\t\t\t\t|  5. Edit a record          |"
             << "\n\t\t\t\t|  6. Buy a book             |"
             << "\n\t\t\t\t|  7. Exit                   |"
             << "\n\t\t\t\t------------------------------"
             << "\n\nEnter your Choice : ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            b1.feeddata();
            b1.storebook();
            cout << "\nRecord stored";
            break;
        case 2:
            cout << "\nSTOCK REPORT\n";
            b1.stock_report();
            break;
        case 3:
            cout << "\nTo search with book's title, press 1\nTo search with Book ID, press 2\n";
            int num;
            cin >> num;
            if (num == 1)
            {
                cout << "\nEnter the title of the book : ";
                cin.ignore();
                cin.getline(title, 19);
                b1.search_title(title);
            }
            else if (num == 2)
            {
                cout << "\nEnter the Book ID : ";
                char b_ID[20];
                cin.ignore();
                cin.getline(b_ID, 19);
                b1.search_bookID(b_ID);
            }
            else
            {
                cout << "\nInvalid Choice Entered";
            }
            break;
        case 4:
            cout << "\nEnter the title of the book which is going to be deleted : ";
            cin.ignore();
            cin.getline(title, 19);
            b1.delete_book(title);
            break;
        case 5:
            cout << "\nEnter the title of book whose data you want to update : ";
            cin.ignore();
            cin.getline(title, 19);
            b1.update_data(title);
            break;
        case 6:
            cout << "\nEnter the name of the book which you want to buy : ";
            cin.ignore();
            cin.getline(title, 19);
            int noc;
            cout << "\nEnter the number of copies of the book : ";
            cin >> noc;
            b1.buy_book(noc, title);
            break;
        case 7:
            exit(0);
        default:
            cout << "\nInvalid Choice Entered";
        }
    }
    return 0;
}