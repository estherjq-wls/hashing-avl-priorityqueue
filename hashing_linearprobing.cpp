#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;
 
//****HASH NODE CLASS****//
class HashNode{
    public:
        string key;
        HashNode *next = nullptr;
        HashNode *prev = nullptr;

        HashNode(string key){
            this->key = key;
        }
};
//end HashNode Class

//****HASH TABLE CLASS****//
class HashTable{
    private:
        int maxBuckets;         //max size of array (static)
        HashNode **hashTable;   //array of pointers to Nodes

    public:
        //contructor
        HashTable(int _maxBuckets = 1000000){           
            maxBuckets = _maxBuckets;
            hashTable = new HashNode* [maxBuckets];     //dynamic allocation of our hashTable of size maxBuckets pointers to nodes
            for (int i=0; i<maxBuckets; i++){
                hashTable[i] = nullptr;                 //initialize all table pointers to null
            }
        }
        
        //destructor
        ~HashTable(){
            for (int i=0; i<maxBuckets; i++){
                if (hashTable[i] != nullptr)
                    delete hashTable[i];    //delete the current node
            }
            delete[] hashTable;             //free the hashTable when program ends
        }

        //****HASH FUNCTION****//
        int hashIndex(string key, int tableSize){
            unsigned int sum = 0;
            for (int i = 0; key[i] != '\0'; i++){           //convert string to ascii code
                unsigned int asciiCodes = (int)key[i];
                sum += asciiCodes;                          //sum all the ascii codes
            }
            return (sum % tableSize);                       //sum mod hash table size
        }

        //****INSERT KEY****//
        void insertKey(string key, int tableSize)
        {
            int bucket_id = hashIndex(key, tableSize);      //to find the initial position of the key
            int h = 1;
            while(hashTable[bucket_id] != nullptr &&
                    hashTable[bucket_id]->key != key){      //if the bucket is not empty
                bucket_id = (bucket_id + h) % tableSize;    //find the next bucket that is empty
                h++;                                        //by adding 1 to the bucket_id at once
            }
            hashTable[bucket_id] = new HashNode(key);       //if the bucket is empty, insert the key
        }

        //****SEARCH KEY****//
        bool searchKey(string key, int tableSize)
        {
            int bucket_id = hashIndex(key, tableSize);
            int h = 1;
            for(int i=0;i<=tableSize;i++){
                if(hashTable[bucket_id] == nullptr){        //the initial position of the key should be in is empty
                    return false;                           //return false
                }
                else if(hashTable[bucket_id] != nullptr && hashTable[bucket_id]->key == key){   //the position of the key is not empty & have the key
                    //cout << key << " is found at Bucket# " << bucket_id << endl;
                    return true;
                }
                while(hashTable[bucket_id] != nullptr && hashTable[bucket_id]->key != key){
                    bucket_id = (bucket_id + h) % tableSize;    //find the next bucket
                    h++;
                    if (bucket_id == (tableSize-1))
                    {
                        return false;
                    }
                }
            }
            return false;
        }

        //****PRINT HASH TABLE****//
        void display(int tableSize) {
            for(int i=0; i<tableSize; i++){                 //whole hash table
                cout << "Bucket #" << i << " | ";
                for(HashNode *temp = hashTable[i]; temp!=nullptr; temp=temp->next){
                    cout << ' ' <<temp->key;                //for each node in this bucket
                }     
            cout << endl; 
            }
        }
};
//end HashTable Class

//driver code 
int main(){
    cout << "<<<Hash Table with Linear Probing>>>\n\n";
    
    string key;
    vector <string> emails;
    string emailFileStr = "";
    int choice = 0;

    while (choice != 1 && choice != 2 && choice != 3)
    {
        cout << "Choose your input data set.\n1. Set A (100 emails)\n2. Set B (100,000 emails)\n3. Set C (500,000 emails)" << endl;
        cout << "Number ";
        cin >> choice;
    }
    cout << endl;
        
    //change the path according to your own file location
    if (choice == 1){
        emailFileStr = "setA";
    }
    else if (choice == 2){
        emailFileStr = "setB";
    }
    else{
        emailFileStr = "setC";
    }

    //change the path according to your own file location
    ifstream inputEmailFile("C:/Users/User/OneDrive/Desktop/Algorithm Design & Analysis/Assignment 1/datasets/" + emailFileStr + ".txt");

    if (inputEmailFile.is_open()){
        while (getline(inputEmailFile, key)){
            emails.push_back(key);                //add the email to the end of the vector
        }
        inputEmailFile.close();
    }
    else{
        cout << "Access Denied! Unable to open file.";
        return 0;
    }

    int n = emails.size();
    int tableSize;
    cout << "Number of Emails: " << n << endl;

    //the most suitable table size: not close to power of 2, prime number
    //50% more than the size of data sets
    if(n == 100){
      tableSize = 151;
    }
    else if(n == 100000){
      tableSize = 150001;
    }
    else if(n == 500000){
      tableSize = 749993;
    }
    else{
      return 0;
    }

    cout << "Hash Table Size: " << tableSize << endl;
    cout << "Inserting into hash table..." << endl;

    HashTable ht(tableSize);                    //create the hash table
    
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++){
      ht.insertKey(emails[i],tableSize);        //inserting data into hash table
    }
    auto duration = high_resolution_clock::now() - start;
    long long milliDuration = duration_cast<milliseconds>(duration).count();
    cout << "Duration of insertion: " << milliDuration << " milliseconds\n" << endl;
    //ht.display(tableSize);                      //print hash table
    
    int choice_2 = 0;

    while (choice_2 != 1 && choice_2 != 2)
    {
        cout << "Choose your searching data set.\n1. Searchable emails\n2. Unsearchable emails" << endl;
        cout << "Number ";
        cin >> choice_2;
    }
    cout << endl;

    if (choice_2 == 1){
        cout << "Searching emails that could be found: \n";
        //change the path according to your own file location
        ifstream searchableEmailFile("C:/Users/User/OneDrive/Desktop/Algorithm Design & Analysis/Assignment 1/datasets/canSearch_" + emailFileStr + ".txt"); // this file contains email that could be search

        string emailsSearchable[10];
        int i = 0;
        if (searchableEmailFile.is_open()){
            while (getline(searchableEmailFile, key)){
                emailsSearchable[i] = key;            //add the emails for searching to the end of the array
                i++;
            }
            searchableEmailFile.close();
        }
        else{
            cout << "Access Denied! Unable to open file" << endl;
            return 0;
        }

        int n2 = end(emailsSearchable) - begin(emailsSearchable);
        bool isFound = false;
        int numberOfEmailNotFound = 0;
        cout << "\nNumber of Emails to Search: " << n2 << endl;
        cout << "Searching in hash table..." << endl;

        auto start2 = high_resolution_clock::now();
        for (int i = 0; i < n2; i++){
            isFound = ht.searchKey(emailsSearchable[i],tableSize);      //email found: isFound == true
            if (!isFound){          
                numberOfEmailNotFound++;                            //email not found
            }
        }
        auto duration2 = high_resolution_clock::now() - start2;
        long long milliDuration2 = duration_cast<milliseconds>(duration2).count();
        cout << "Duration of searching: " << milliDuration2 << " milliseconds" << endl;
        if (numberOfEmailNotFound == 0){
            cout << "Successful in searching all emails!" << endl;
        }
        else{
            cout << "Failing in searching all emails!\n" << numberOfEmailNotFound << " emails are not found." << endl;
        }
    }

    else if (choice_2 == 2){
        cout << "Searching emails that could not be found: \n";
        //change the path according to your own file location
        ifstream unsearchableEmailFile("C:/Users/User/OneDrive/Desktop/Algorithm Design & Analysis/Assignment 1/datasets/cannotSearch_" + emailFileStr + ".txt"); // this file contains email that could not be search

        vector <string> emailsUnsearchable;
        if (unsearchableEmailFile.is_open()){
            while (getline(unsearchableEmailFile, key)){
                emailsUnsearchable.push_back(key);            //add the emails for searching to the end of the array
            }
            unsearchableEmailFile.close();
        }
        else{
            cout << "Access Denied! Unable to open file" << endl;
            return 0;
        }

        int n3 = end(emailsUnsearchable) - begin(emailsUnsearchable);
        bool isFound_2 = false;
        int numberOfEmailNotFound_2 = 0;
        cout << "\nNumber of Emails to Search: " << n3 << endl;
        cout << "Searching in hash table..." << endl;

        auto start3 = high_resolution_clock::now();
        for (int i = 0; i < n3; i++){
            isFound_2 = ht.searchKey(emailsUnsearchable[i],tableSize);      //email found: isFound == true
            if (!isFound_2){          
                numberOfEmailNotFound_2++;                            //email not found
            }
        }
        auto duration3 = high_resolution_clock::now() - start3;
        long long milliDuration3 = duration_cast<milliseconds>(duration3).count();
        cout << "Duration of searching: " << milliDuration3 << " milliseconds" << endl;
        if (numberOfEmailNotFound_2 == 0){
            cout << "Successful in searching all emails!" << endl;
        }
        else{
            cout << "Failing in searching all emails!\n" << numberOfEmailNotFound_2 << " emails are not found." << endl;
        }
    }
    return 0;
}