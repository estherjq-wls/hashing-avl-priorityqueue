#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;
vector<string> D;
 
template <typename T>
void printVector (T A, int n) {
for (auto i = A.begin(); i != A.end(); ++i)
    cout << *i << ' ';
  cout << endl;
}

template <typename T>
class PriorityQueue {
  vector<T> A;

  void heapify_enqueue (int index) {   // used in enqueue.
    if (index == 0)                    // if already at root.
      return;
    
    // parent index
    int parent_index = (index -1)/2;
    
    // swap if parent is smaller
    if((A[index].compare( A[parent_index]))>0){
        swap(A[index],A[parent_index]);
    }

    // recursion of the function
    heapify_enqueue(parent_index);

  }
    
  void heapify_dequeue (int index) {   // used in dequeue.
    int max;                           // max index
    // left child index
    int left = 2*index+1;
    
    // right child index
    int right = 2*index +2;
    
    // compare and find the greatest child
    if(left<A.size()&& A[left].compare(A[index])>0){
        max = left;
    } else {
       max = index; 
    }

    if(right < A.size() && A[right].compare(A[max])>0){
        max= right;
    }

    if (max != index) {
      swap (A[index], A[max]);
      heapify_dequeue (max);
    }
  }
  
 public:
 //max heap implemented in this program.
  void enqueue (T element) {
    A.push_back (element);
    heapify_enqueue (A.size()-1);  // start at last element.
  }
  
  T dequeue() {
    T removed_element = A[0];
    A[0] = A[A.size()-1];          // copy last element to root.
    A.pop_back();                  // remove last element.
    heapify_dequeue (0);           // start at root.
    //cout << removed_element << " is dequeued. \t\n" ;   //print out dequeued element
    D.push_back(removed_element);
    return removed_element;
  }
  
  int size() {
    return A.size();
  }

  void print() {
    for (int i = 0; i < 100; i++){
      cout << A[i] << " ";
    }
    cout << endl;
  }
};

int main () {
  string line;
  vector<string> A;
  int emailChoice;
  string pathEmail = "C:/Downloads/datasets/datasets/";
  string pathCanSearch = "C:/Downloads/datasets/datasets/";
  string pathCannotSearch = "C:/Downloads/datasets/datasets/";
  string choice;
  int i = 0;
  cout << "Please choose 1 out of 3 email datasets from the options. \n100 emails ---- (1)\n100000 emails ---- (2)\n500000 emails ---- (3)" << endl;
  cin >> emailChoice;
  if(emailChoice == 1){
    choice = "setA";
  } else if (emailChoice == 2){
    choice ="setB";
  } else if (emailChoice ==3){
    choice = "setC";
  }else {
    cout << "Invalid input, please choose between 100, 100000 and 500000."<< endl;
    return 0;
  }
  ifstream email(pathEmail.append(choice).append(".txt"));
  ifstream emailCanSearch(pathCanSearch.append("canSearch_").append(choice).append(".txt"));
  ifstream emailCannotSearch(pathCannotSearch.append("cannotSearch_").append(choice).append(".txt"));
  if (email.is_open()){
    while ( getline (email,line) )
    {
        //cout << line << '\n';
        A.push_back(line);
        i++;
    }
    email.close();
  } else cout << "Unable to open email";

  int n = A.size();
  cout << endl<< "Emails = ";
  //printVector(A, n);
  cout << A.size();
  cout << "\nEnqueue\t: PriorityQueue enqueueing...\n";
  PriorityQueue<string> pq;

//enqueue emails and calculate the duration of the enqueue process
  auto startEnqueue = high_resolution_clock::now(); 
  for (int i = 0; i < n; i++) {
    pq.enqueue (A[i]);
  } 

  auto endEnqueue = high_resolution_clock::now();
  auto durationEnqueue = endEnqueue - startEnqueue;
  long long milliDurationEnqueue = duration_cast<milliseconds>(durationEnqueue).count();
  cout << "Duration of enqueue: " << milliDurationEnqueue << " milliseconds\n" << endl;  
  cout << "The completed priority queue is "<<endl;
  pq.print();

//dequeue 10% of the emails and calculate the duration of the dequeue process
  auto startDequeue = high_resolution_clock::now(); 
  cout << "\nDequeue\t: PriorityQueue dequeueing 10% of the emails...\n";
  for (int i = 0; i < ceil(n*10/100); i++) {   
    //cout << endl;
    //cout<< i+1 << "\t: \t";
    pq.dequeue(); 
    //cout<< pq.size()<<endl;
    
    //pq.print(); //print dequeued vector
  }


  cout << "Total " << ceil(n*10/100) << " emails is dequeued.\t \n";
  auto endDequeue = high_resolution_clock::now();
  auto durationDequeue= endDequeue - startDequeue;
  long long milliDurationDequeue = duration_cast<milliseconds>(durationDequeue).count();
  cout << "Duration of dequeue: " << milliDurationDequeue << " milliseconds\n" <<endl << endl;

  for (int i = ceil(n*10/100); i < n; i++) {   
    pq.dequeue(); 
  }

  //   Do Searching for 10 canSearch emails and 10 cannotSearch emails
  int j = 0;
  int found = 0;
  int input;
  string line2;
  string line3;
  string target[10];
  cout<< "Search for canSearch datasets --> (1) \nSearch for cannotSearch datasets --> (2) " << endl;
  cin >> input;
  if(input == 1){
  if (emailCanSearch.is_open()){
    while ( getline (emailCanSearch,line2) )
    {
      target[j] = line2;
      j++;
    }
    emailCanSearch.close();
    } 
  else cout << "Unable to open emailCanSearch file";
  } 
  else if (input == 2){
    if (emailCannotSearch.is_open()){
      while ( getline (emailCannotSearch,line) )
      {
      target[j] = line3;
      j++;
      }
      emailCannotSearch.close();
    } 
    else cout << "Unable to open emailCannotSearch file";
  }else{ 
    cout << "Not valid input";
    return 0;
  }
  
  auto startSearch = high_resolution_clock::now(); 
  for(int i = 0 ;i < sizeof(target)/sizeof(target[0]);i++){
    auto it = find(D.begin(),D.end(),target[i]);
    if(it != D.end()){
      cout <<"Searching for --> "<< target[i] << " is found in index " << distance(D.begin(),it) << endl; 
      found++;
    }else {
      cout << "target not found." <<endl;
    }
  }
  cout << endl <<"Total " << found << " email(s) found."<<endl ; 
  auto endSearch = high_resolution_clock::now();
  auto durationSearch = endSearch - startSearch;
  long long milliDurationSearch = duration_cast<milliseconds>(durationSearch).count();
  cout << "Duration of searching: " << milliDurationSearch << " milliseconds\n" <<endl;
}

