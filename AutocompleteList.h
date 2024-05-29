// 
// AutocompleteList.h
// Description: Autocomplete class and Term Struct to be used for search queries
// Author: Reem Allam
//
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted
    
    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    
    int firstIndexOf(string prefix) {
        int low = 0;
        int high = size -1;
        int result = -1; // first index

        while(low <= high){
            int mid = low + ((high - low)/2);
            string midQ = terms[mid].query;

            if(midQ.substr(0,prefix.length())== prefix){
                result = mid;
                high = mid - 1;
            }
            else if(prefix < midQ.substr(0,prefix.length())){
               high = mid - 1;

            }
            else{
                low = mid + 1;
            }
        }
        return result;  // TODO: update this
    }
    
    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int lastIndexOf(string prefix) {
        // TODO: Write this function (optional).
        int low = firstIndexOf(prefix);
        int high = size - 1;
        int result = -1; // last index
        
        if(low == -1){
            return -1;
        }

        while(low <= high){
            int mid = low + ((high - low) / 2);
            string midQ = terms[mid].query;
             if(prefix == midQ.substr(0,prefix.length())){
                result = mid;
                low = mid + 1;
            }
            else if(midQ.substr(0,prefix.length()) < prefix){
                low = mid + 1;

            }
            else{
                high = mid - 1;
            }
        }
        
        return result;  // TODO: update this
    }
    
    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //

    static bool letters(Term a, Term b){
        return a.query < b.query;
    }
    static bool weights(Term w1, Term w2){
        return w1.weight > w2.weight;
    }

    void sortByLexOrder() {
        // TODO: Write this function (optional).
        sort(terms, terms + size, letters);
        this -> sortType = "lex";
    }
        
    
    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    
    void sortByWeightOrder() {
        // TODO: Write this function.
        sort(terms, terms + size, weights);
        this -> sortType = "weight";
    }    
        
    
 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        // TODO: Write this constructor (required).
        terms = nullptr;
        size = 0;
        sortType = "none";        
    }
    
    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        // TODO: Write this constructor (required).
        terms = new Term[n];
        size = n;
        sortType = "none";   
    }
    
    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    AutocompleteList(string filename) { 
        // TODO: Write this constructor (required).
        ifstream infile(filename);
        string line;
        long long int weight;
        string query;
        string temp;
        int i = 0;

        if(!infile){
            cout<< "Invalid file, try again:  ";
            return;
        }
        getline(infile, line);
        stringstream sstream(line);
        sstream >> this -> size;
        this -> terms = new Term[size];


        while(!infile.eof() && i < this -> size){
        getline(infile, line);
        stringstream sstream(line);
        sstream >> weight;
        getline(sstream, temp);
        query = temp.substr(temp.find_first_not_of(" \t"));
        terms[i].weight = weight;
        terms[i].query = query;
        i++;
        }
        infile.close();
        sortByLexOrder();
        this -> sortType = "lex";
    }
    
    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        // TODO: Write this constructor (required).
        this -> terms = new Term[other.size];
        this -> size = other.size;
        this -> sortType = other.sortType;

        for(int i = 0; i < other.size; i++){
            terms[i] = other.terms[i];
        }
    }
    
    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {
        //AutocompleteList result; // TODO: remove this is here
        // so starter code compiles
        // TODO: Write this function (required).
        if(this == &other){
            return *this;
        }
            delete[] this -> terms;
            this -> terms = new Term[other.size];
            this -> size = other.size;
            this -> sortType = other.sortType;

            for(int i = 0; i < other.size; i++){
                terms[i].query = other.terms[i].query;
                terms[i].weight = other.terms[i].weight;
            }
        
        
        return *this;  // TODO: update
    }
    
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        // TODO: Write this destructor (required).
        delete[] terms;
    }
    
    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {
        // TODO: Write this function (required).
        return size;
    }
    
    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        //Term result = {};  // TODO: remove this is here so starter code compiles
        // TODO: Write this function (required).
        if(i < 0 || i >= size){
            throw out_of_range(" AutocompleterList: i out of bounds");
        }
        
        return terms[i];  // TODO: update
    }
    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        //AutocompleteList result; // TODO: remove this is here
        // so starter code compiles
        // TODO: Write this function (required).
        if(prefix.empty() || sortType != "lex"){
            return AutocompleteList();
        }
        int firstIndex = firstIndexOf(prefix);
        int lastIndex = lastIndexOf(prefix);
        
        if(firstIndex == -1 || lastIndex == -1){
            return AutocompleteList();
        }
        int matches = lastIndex - firstIndex + 1;
        AutocompleteList allMatches(matches);
        int j = 0;
        for (int i = firstIndex; i<= lastIndex; i++){
            allMatches.terms[j].query = this -> terms[i].query;
            allMatches.terms[j].weight = this -> terms[i].weight;
            j++;
        }
        allMatches.sortType = "weight";
        allMatches.sortByWeightOrder();

        return allMatches;  // TODO: update
    }
    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        // TODO: Write this function (required).
        if(prefix.empty() || sortType != "lex"){
            return 0;
        }
        
        int firstIndex = firstIndexOf(prefix);
        int lastIndex = lastIndexOf(prefix);
        
        if(firstIndex == -1 || lastIndex == -1){
            return 0;
        }
        return lastIndex - firstIndex + 1;  // TODO: update
    }
    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() {
        // TODO: Write this function (required).
        
        for(int i = 0; i < size; i++){
            cout<< "        " << terms[i].query << ", "<< terms[i].weight << endl;
        }  
    }
};
