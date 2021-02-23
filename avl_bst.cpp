#include "AVL.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

int static numberOfEmails = 0;
AVL tree;

void searchEmailOfFile(ifstream &file)
{
    const int SIZE = 10;
    string emailsToSearch[SIZE];
    if (file.is_open())
    {
        for (int i = 0; i < SIZE; ++i)
        {
            file >> emailsToSearch[i];
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
        exit(10);
    }

    bool isFound = false;
    int numberOfEmailsNotFound = 0;
    cout << "Number of emails to search = " << SIZE << endl;
    cout << "Searching AVL tree.." << endl;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++)
    {
        isFound = tree.search(emailsToSearch[i]);
        if (!isFound)
        {
            numberOfEmailsNotFound++;
        }
    }
    auto duration = high_resolution_clock::now() - start;
    cout << "Done!\n";
    if (numberOfEmailsNotFound == 0)
        cout << "All emails are found!\n";
    else
    {
        cout << "Number of emails not found = " << numberOfEmailsNotFound << endl;
    }
    long long milliDuration = duration_cast<milliseconds>(duration).count();
    cout << "Duration of search: " << milliDuration << " milliseconds\n";
}

// void displaySomeTree(string *emails)
// {
//     AVL someTree;
//     int n = 30;
//     for (int i = 0; i < n; ++i)
//     {
//         someTree.push(emails[i]);
//     }
//     someTree.display();
// }

int main()
{
    while (numberOfEmails != 100 && numberOfEmails != 100000 && numberOfEmails != 500000)
    {
        cout << "How many emails do you want to insert into the AVL tree? (choose 100/100000/500000)" << endl;
        cin >> numberOfEmails;
    }
    cout << endl;

    string emailFileStr = "";
    if (numberOfEmails == 100)
        emailFileStr = "setA";
    else if (numberOfEmails == 100000)
        emailFileStr = "setB";
    else
        emailFileStr = "setC";

    //change the path according to your own file location
    ifstream emailFile("C:/Downloads/TT4V_Group6_Assignment1/datasets/" + emailFileStr + ".txt");

    string *emails = new string[numberOfEmails]; // store emails read from file
    if (emailFile.is_open())
    {
        for (int i = 0; i < numberOfEmails; ++i)
        {
            emailFile >> emails[i];
        }
        emailFile.close();
    }
    else
    {
        cout << "Unable to open file";
        return 0;
    }
    cout << "Number of emails = ";
    cout << numberOfEmails;
    cout << "\nInserting into AVL tree...\n";
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numberOfEmails; ++i)
    {
        tree.push(emails[i]);
    }
    auto duration = high_resolution_clock::now() - start;
    long long milliDuration = duration_cast<milliseconds>(duration).count();
    cout << "Done!\nDuration of insertion: " << milliDuration << " milliseconds\n\n\n";
    //displaySomeTree(emails); // create graph of tree using first 20 emails of the tree
    //tree.display(); // create graph of tree

    //cout << "Preorder traversal of the constructed AVL tree is \n";
    //tree.printPreOrder();

    //change the path according to your own file location
    cout << "Searching emails that could be found: \n";
    ifstream searchableEmailFile("C:/Downloads/TT4V_Group6_Assignment1/datasets/canSearch_" + emailFileStr + ".txt"); // this file contains email that could be search
    searchEmailOfFile(searchableEmailFile);                                                                           // search the tree for the emails in the file
    cout << "\n\nSearching emails that could not be found: \n";
    ifstream unsearchableEmailFile("C:/Downloads/TT4V_Group6_Assignment1/datasets/cannotSearch_" + emailFileStr + ".txt"); // this file contains email that could not be search
    searchEmailOfFile(unsearchableEmailFile);                                                                              // search the tree for the emails in the file

    delete[] emails;

    return 0;
}