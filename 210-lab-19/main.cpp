#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

const int FILE_SIZE = 12;
const int PREC = 3;

struct Review {    // Review strcut to build the list
    double rating;
    string comment;
    Review *next;
};

class Movie
{
private:
    string title;    //Private memberd for the title and the linked list
    Review *head;
    Review *rev1;
    Review *rev2;
    Review *rev3;
    

public:
    Movie() {}    // Default constructor
    
    // Constructor with parameters
    Movie(string name, Review *&h, Review *&review1, Review *&review2, Review *&review3) : title{ name }, head{ h }, rev1{ review1 }, rev2{ review2 }, rev3{ review3 }
    {
        head = rev1;
        rev1->next = rev2;
        rev2->next = rev3;
        rev3->next = nullptr;
    }
    
    string getTitle() { return title; }   // Title getter function
    
    void getList() {    // List getter function
        for (int i = 0; i < 3; i++) {
            cout << "Rating " << i + 1 << ": " << setprecision(PREC) << head->rating << endl;
            cout << "Comment: "<< head->comment << endl;
            head = head->next;
        }
    }
    
}; // End of class

void setRating(Review*&);    // Function prototype to set the rating for a random number
void free_pointer(Review*&);    // Function prototype to free pointer

int main()
{
    Review *rv1 =  nullptr;    // main struct pointers to build the list
    Review *rv2 = nullptr;
    Review *rv3 =  nullptr;
    Review *hd =  nullptr;
    Movie movieArray[4];    // Movie class array;
    
    ifstream reader;    // File reader and file name
    string fileName = "review_comments.txt";
    
    reader.open(fileName);    // File is opened
    
    if (!reader)
        cout << "Failed to open file.\n";    // File open error message
    else {
        for (int i = 0; i < FILE_SIZE; i++) {    // For loop to build list
            
            rv1 = new Review;    // Each node in the list is dynamically allocated
            reader >> rv1->comment;
            setRating(rv1);
            hd = rv1;
            
            rv2 = new Review;
            reader >> rv2->comment;
            setRating(rv2);
            rv1->next = rv2;
            
            rv3 = new Review;
            reader >> rv3->comment;
            setRating(rv3);
            rv2->next = rv3;
            rv3->next = nullptr;
            
            Movie element{"Movie Title", hd, rv1, rv2, rv3};    // nodes and head pointer sent to Movie constructor to build Movie object
            movieArray[i] = element;    // Movie object stored in array
            
            free_pointer(rv1);    // pointers are freed to store new values in next loop iteraton
            free_pointer(rv2);
            free_pointer(rv3);
        }
    }
    
    reader.close();    // File closed
    
    
        
    for (int j = 0; j < 4; j++) {    // Loop to output the Movie details of each object in the Movie array
        cout << "---------\n";
        cout << movieArray[j].getTitle() << endl;
        movieArray[j].getList();
        cout << "---------";
    }
    
    return 0;
}

void setRating(Review *&ptr) {
    random_device randRate;
    uniform_real_distribution<double>range(1.0, 5.0);
    ptr->rating = range(randRate);
}

void free_pointer(Review *&ptr) {
    delete ptr;
    ptr = nullptr;
    
}
