#include <iostream>
#include <string>

using namespace std;

int main() {
    string paragraph, word_search, word_replace;
    
    // Read and interpret the users paragraph
    cout << "Hello, please enter a paragraph: ";
    getline(cin, paragraph);
    
    // Read and find the word for the program to find
    cout << "Please enter a word or sentence to search: ";
    getline(cin, word_search);
    
    // Read and replace the searched word with a replacement word
    cout << "Please, enter the word that will be used to replace: ";
    getline(cin, word_replace
  );
    
    // Counting how many times that word is found and the position of the word
    size_t pos = 0;
    int count = 0;
    while ((pos = paragraph.find(word_search, pos)) != string::npos) {
        cout << "Word or sentence is found at position " << pos << endl;
        count++;
        pos += word_search.length();
    }
    
    // Replace all occurrences of the search word with the replace word
    pos = 0;
    while ((pos = paragraph.find(word_search, pos)) != string::npos) {
        paragraph.replace(pos, word_search.length(), word_replace
      );
        pos += word_replace.length();
    }
    
    // Give the user the new paragraph
    cout << "Amount of times found: " << count << endl;
    cout << "The new paragraph: " << paragraph << endl;
    
    return 0;
}