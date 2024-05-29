//
//  application.cpp
//  Description: This code runs the AutocompleteList.h based on user input
//  Author: Reem Allam
//  

#include <iostream>
#include "AutocompleteList.h"

using namespace std;

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    AutocompleteList list(filename);

    string option;
    cout<< "Enter s-search or c-creative search: ";
    cin >> option;
    cin.ignore(); // ignore newline characters

    cout << "Welcome!\n";
    cout << "Type your search below, press enter for autocomplete (# to stop).\n";

    while(true){
        string query;
        string prefix;
        cout << "Search: ";

     if(option == "s"){
        getline(cin,prefix);
        cout << endl;
        AutocompleteList matches = list.allMatches(prefix);

        if(prefix == "#"){
            break;
        }
        //if what user enters has a match in the file print it out to user with the weight
        if(matches.getSize() > 0){
            for(int i = 0; i < matches.getSize(); i++){
                cout<< "        " << matches[i].query << ", "<< matches[i].weight << endl;
            }
        }
     }
    // option c searches ever letter in the line of the lists and prints out matches to that of what the user searches
     else if(option == "c"){
        getline(cin,query);
        cout<<endl;

        if(query == "#"){
            break;
        }
         
        int matches = 0; // keep track of matches
         for(int i = 0; i < list.getSize(); i++){ //iterate through each query in list
             string currQ = list[i].query;
             int currQlength = currQ.length();
             int qlength = query.length();

            for(int j = 0; j <= currQlength - qlength; j++){ //iterate through each position of current query 
                bool match = true;
                for(int k = 0; k < qlength; k++){ // checks if there is a match
                    if(currQ[j + k] != query[k]){
                        match = false;
                        break;
                    }
                }
                if(match){ // print query and weight if there is a match
                    cout<< "        " << currQ << ", " << list[i].weight<< endl;
                    matches++;
                    break;
                }
            }
         }
         if(matches == 0){
             cout<< "No matches found."<< endl;
         }
        
     }
     else if (option == "#"){
         break;
     }
 } 
    return 0;
}
