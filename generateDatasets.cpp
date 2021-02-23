#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//Group 6
//[A-Za-z0-9]{5}\.[A-Za-z0-9]{4}@[A-Za-z]{4}\.(com|my|org)
static const char alphanum[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789";

static const char stringArr[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

static const string domain[] = 
{"com",
"my",
"org"};

int alphanumSize = sizeof(alphanum) - 1;
int stringSize = sizeof(stringArr) - 1;

char genAlphanum()
{
    return alphanum[rand() % alphanumSize];
}

char genString()
{
    return stringArr[rand() % stringSize];
}

string genDomain()
{
    return domain[rand() % 3];
}

int main()
{
    srand(time(0));
    string emails[100];           //arrays for storing 100/100k/500k emails
    //string emails[100000];
    //string emails[500000];
    string canSearch[10];         //array for emails that can be searched
    string cannotSearch[10];      //array for emails that cannot be searched

    for(unsigned int i = 0; i < sizeof(emails)/sizeof(emails[0]); ++i)
    {
      string email;
      for(unsigned int i = 0; i < 5; ++i)
      {
        email += genAlphanum();
      }
      email += ".";
      for(unsigned int i = 0; i < 4; ++i)
      {
        email += genAlphanum();
      }
      email += "@";
      for(unsigned int i = 0; i < 4; ++i)
      {
        email += genString();
      }
      email += ".";               //append the alphabets, numbers, domain together
      email += genDomain();
      emails[i] = email;          
      cannotSearch[i] = email;
    }

    //creating 100 / 100k / 500k emails
    ofstream myfile ("setA.txt");             
    //ofstream myfile ("setB.txt"); 
    //ofstream myfile ("setC.txt"); 
    if (myfile.is_open())
    {
      for(int i = 0; i < sizeof(emails)/sizeof(emails[0]); i++){
        myfile << emails[i] << "\n" ;
      }
      myfile.close();
    }
    else cout << "Unable to open file";

    //getting 10 emails from 100/100k/500k email sets, for email that can be searched
    for(int i = 0; i < 10; i++)
    {
      canSearch[i] = emails[rand()%sizeof(emails)/sizeof(emails[0])];
    }

    ofstream myfile2 ("canSearch_setA.txt");
    //ofstream myfile2 ("canSearch_setB.txt");
    //ofstream myfile2 ("canSearch_setC.txt");
    if (myfile2.is_open())
    {
      for(int i = 0; i < 10; i++){
        myfile2 << canSearch[i] << "\n" ;
      }
      myfile2.close();
    }
    else cout << "Unable to open file";

    //creating another 10 emails randomly
    //if emails not same as in 100/100k/500k email sets, output to file
    ofstream myfile3 ("cannotSearch_setA.txt");
    //ofstream myfile3 ("cannotSearch_setB.txt");
    //ofstream myfile3 ("cannotSearch_setC.txt");
    if (myfile3.is_open())
    {
      int i;
      if(cannotSearch[i] != emails[i]){
        for(int j = 0; j < 10; j++){
          myfile3 << cannotSearch[j] << "\n" ;
        }
      }
      else{                                     //usually the emails won't be the same as in the original 100/100k/500k emails sets
        cout << "Not enough 10 emails! Please regenerate emails." << endl;
      }
      myfile3.close();
    }
    else{
      cout << "Unable to open file";
    }
    return 0;
}
