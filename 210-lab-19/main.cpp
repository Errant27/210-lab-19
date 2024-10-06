#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

const int FILE_SIZE = 12;
const int PREC = 3;

struct Review {
    double rating;
    string comment;
    Review *next;
};

class Movie
{
private:
    string title;
    Review *head;
    Review *rev1;
    Review *rev2;
    Review *rev3;
    

public:
    Movie() {}
    
    Movie(string name, Review *&h, Review *&review1, Review *&review2, Review *&review3) : title{ name }, head{ h }, rev1{ review1 }, rev2{ review2 }, rev3{ review3 }
    {
        head = rev1;
        rev1->next = rev2;
        rev2->next = rev3;
        rev3->next = nullptr;
    }
    
    string getTitle() { return title; }
    
    void getList() {
        for (int i = 0; i < 3; i++) {
            cout << "Rating " << i + 1 << ": " << setprecision(PREC) << head->rating << endl;
            cout << "Comment: "<< head->comment << endl;
            head = head->next;
        }
    }
    
}; // End of class

void setRating(Review*&);
void free_pointer(Review*&);

int main()
{
    Review *rv1 =  nullptr;
    Review *rv2 = nullptr;
    Review *rv3 =  nullptr;
    Review *hd =  nullptr;
    Movie movieArray[4];
    
    ifstream reader;
    string fileName = "review_comments.txt";
    
    reader.open(fileName);
    
    if (!reader)
        cout << "Failed to opend file.\n";
    else {
        for (int i = 0; i < FILE_SIZE; i++) {
            
            rv1 = new Review;
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
            
            Movie element{"Movie Title", hd, rv1, rv2, rv3};
            movieArray[i] = element;
            
            free_pointer(rv1);
            free_pointer(rv2);
            free_pointer(rv3);
        }
    }
    
    reader.close();
    
    
        
    for (int j = 0; j < 4; j++) {
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
