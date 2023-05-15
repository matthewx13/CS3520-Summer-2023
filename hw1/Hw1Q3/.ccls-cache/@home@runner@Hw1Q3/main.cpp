// This is HW question 3 (Matthew Xue - 5/12)
/*
The purpose of this question is to calculate and print the following statistics:
• Numbers of total words in the paragraph
• Number of vowels and consonants
• Number of words that use the following punctuation marks: ! . , ; “ ‘ ? $
• Number of words that use more than one vowel

It will also answer this questions (i copy and pasted the question from the pdf posted on canvas)

Now, prompt the user to enter a number (i.e., length of a word) and then calculate {and print}
the following:
• Number of words with length greater than the user provided length. Don’t count the
punctuation marks in length.
Now, update your program to automatically select a random number between [6-10] and print:
• Number of words with length smaller than the random length. Use punctuation marks in
calculating length of words. 
*/
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <random>
#include <ctime>
using namespace std;

// count_words is a function that keeps track of the number of words that
// are in the paragraph that the user inserted into the program
int count_words(const string& paragraph) {
    int count = 0;
    string word;
    istringstream iss(paragraph);
    while (iss >> word) {
        count++;
    }
    return count;
}

// is_vowel is a function that intializes the char i and it checks if 
// i is equal to any of the vowels (aeiou)
bool is_vowel(char i) {
    i = tolower(i);
    return i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u';
}

// function that reads the paragraph that the user inputs and it checks if 
// the output is found in the alphabet and then it uses the is_vowel to
// check whether if the word is a vowel or a consonant
pair<int, int> count_vowels_consonants(const string& paragraph) {
    int vowel_count = 0;
    int consonant_count = 0;
    for (char i : paragraph) { // for each word in the paragraph run the if statement
        if (isalpha(i)) {
            if (is_vowel(i)) { 
                vowel_count++; // add to counter if there is a vowel
            } else {
                consonant_count++;
            }
        }
    }
    return make_pair(vowel_count, consonant_count);
}

// function intializes paragraph and checks if there is punctuations in
// any given sentence in the given input
int count_punct_words(const string& paragraph) {
    int count = 0;
    string word;
    istringstream iss(paragraph); //splits the paragraph into words
    while (iss >> word) { // if there is a word check if there is punctuation
        if (word.find_first_of("!.,;\"\'?$") != string::npos) {
            count++;
        }
    }
    return count;
}

// function that checks if a word uses more than one vowel
int count_mul_vowels_words(const string& paragraph) {
    int count = 0;
    string word;
    istringstream iss(paragraph); // splits paragraph into separate words
    while (iss >> word) {
        int vowel_count = 0;
        for (char i : word) { // if the word is in alphabet and a vowel add1
            if (isalpha(i) && is_vowel(i)) { 
                vowel_count++; 
            }
        }
        if (vowel_count > 1) { // will increase count by 1 if vowel more than 1
            count++;
        }
    }
    return count;
}

// function finds all the words that have a greater length than the length that
// the user inputs when prompted
int words_greater_len(const string& paragraph, int length) {
    int count = 0;
    string word;
    istringstream iss(paragraph);
    while (iss >> word) { // keep on running until there are no words left
        int actual_length = 0;
        for (char i : word) {
            if (isalpha(i)) {
                actual_length++; // add to actual lenger for each letter in word
            }
        }
        if (actual_length > length) {
            count++;
        }
    }
    return count;
}

// function finds how many words have shorter length the length that was randomly
// selected from 6 to 10
int words_smaller_len(const string& paragraph, int length) {
    int count = 0;
    string word;
    istringstream iss(paragraph);
    while (iss >> word) { // while there are words left check if word length is shorter than random length
        if (word.length() < length) { 
            count++;
        }
    }
    return count;
}

int main() {
    // prompt user for paragraph
    string paragraph;
    cout << "Enter a paragraph of your choosing: ";
    getline(cin, paragraph); // storing the input into paragraph

    cout << "The users paragraph: " << endl;
    cout << paragraph << endl;

    // use the function to count how many words in paragraph
    int count_word = count_words(paragraph);
    cout << "The number of words in the paragraph you entered: " << count_word << endl;

    // use the function to count vowels and consonants in paragraph
    auto cons_vowel = count_vowels_consonants(paragraph);
    cout << "The number of vowels: " << cons_vowel.first << endl;
    cout << "The number of consonants: " << cons_vowel.second << endl;

    // use functions to find the punctuations in paragraph
    int punct_count = count_punct_words(paragraph);
    cout << "The number of words that use punctuation marks: " << punct_count << endl;

    // count the words that have more than one vowel using function
    int mul_vowels_count = count_mul_vowels_words(paragraph);
    cout << "The number of words that use more than one vowel: " << mul_vowels_count << endl;

    // prompt user to enter any length of a word
    int len_word;
    cout << "Please enter a length of a word: ";
    cin >> len_word;

    // finds all words with a length greater than the lenger inputted by user
    int greater_len = words_greater_len(paragraph, len_word);
    cout << "The number of words with length greater than " << len_word << ": " << greater_len << endl;

    // chooses a random number between 6 and 10
    mt19937 rng(time(0));
    uniform_int_distribution<int> dist(6, 10);
    int len_random = dist(rng);

    int smaller_len = words_smaller_len(paragraph, len_random);
    cout << "Number of words with a length shorter than the length of the word that was randomly selected(" << len_random << "): " << smaller_len << endl;

    return 0;
}