
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;
const int MAXRESULTS = 20; // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in



//---------FUNCTION 1---------------

//string temp = "/Users/dylanspencer/Desktop/Project 3/words.txt";


//helper function to read words from file
int vocabularyCreatorHelper(istream &dictfile, string dict[], int index) {
    if (index >= MAXDICTWORDS) {
        return index; } //Base case max words reached

    if (!(dictfile >> dict[index])) {
        return index; } //Base case no more words to read

    return vocabularyCreatorHelper(dictfile, dict, index + 1); //Recursive case: read next word
}


// Main vocabulary creator function
int vocabularyCreator(istream &dictfile, string dict[]) {
    return vocabularyCreatorHelper(dictfile, dict, 0);
}



//---------- FUNCTION 2 --------------

//Helper function to sort the characters in a string
string sortString(const string& input) {
    string sorted = input;
    sort(sorted.begin(), sorted.end());
    return sorted;
}

//Recursive function to traverse the dictionary and find anagrams
int findAnagrams(const string& sortedWord, const string dict[], string results[], int index, int size, int& resultCount) {
    if (index >= size || resultCount >= MAXRESULTS) {
        return resultCount;
    }

    
    //Check current word
    if (sortString(dict[index]) == sortedWord) {
        results[resultCount++] = dict[index];
    }

    //Recur for the next word in the dictionary
    return findAnagrams(sortedWord, dict, results, index + 1, size, resultCount);
}

//Function for all anagrams in the dictionary
int potentialSequences(string word, const string dict[], int size, string results[]) {
    string sortedWord = sortString(word);
    int resultCount = 0;
    findAnagrams(sortedWord, dict, results, 0, size, resultCount);
    return resultCount;
}


//--------FUNCTION 3--------

//helper function to display results
void displayResultsRecursive(const string results[], int size, int index = 0) {
    if (index >= size) return;  //Base case
    cout << results[index] << endl;
    displayResultsRecursive(results, size, index + 1);  //recursive repeat w next index
}

//displays results through recur
void outcomeDisclosure(const string results[], int size) {
    cout << "Anagram matches found:" << endl;
    displayResultsRecursive(results, size);
}


int main(){
    
    
string results[MAXRESULTS];
string dict[MAXDICTWORDS];
ifstream dictfile; // file containing the list of words
int nwords; // number of words read from dictionary
string word;
    


dictfile.open("words.txt");
if (!dictfile) {
    cout << "File not found!" << endl;
    return (1);
}
    
    
//normal input thing
nwords = vocabularyCreator(dictfile, dict);
cout << "Please enter a string for an anagram: ";
cin >> word;
int numMatches = potentialSequences(word, dict, nwords, results);
if (!numMatches) {
    cout << "No matches found" << endl;
}
else {
    outcomeDisclosure(results, numMatches);
}
   
    
    return 0;
}

