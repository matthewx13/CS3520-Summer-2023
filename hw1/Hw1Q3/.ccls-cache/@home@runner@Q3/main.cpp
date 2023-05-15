#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <random>
#include <ctime>

int count_words(const std::string& paragraph) {
    int count = 0;
    std::string word;
    std::istringstream iss(paragraph);
    while (iss >> word) {
        count++;
    }
    return count;
}

bool is_vowel(char c) {
    c = std::tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

std::pair<int, int> count_vowels_consonants(const std::string& paragraph) {
    int vowel_count = 0;
    int consonant_count = 0;
    for (char c : paragraph) {
        if (std::isalpha(c)) {
            if (is_vowel(c)) {
                vowel_count++;
            } else {
                consonant_count++;
            }
        }
    }
    return std::make_pair(vowel_count, consonant_count);
}

int count_punctuation_words(const std::string& paragraph) {
    int count = 0;
    std::string word;
    std::istringstream iss(paragraph);
    while (iss >> word) {
        if (word.find_first_of("!.,;\"\'?$") != std::string::npos) {
            count++;
        }
    }
    return count;
}

int count_mul_vowels_words(const std::string& paragraph) {
    int count = 0;
    std::string word;
    std::istringstream iss(paragraph);
    while (iss >> word) {
        int vowel_count = 0;
        for (char c : word) {
            if (std::isalpha(c) && is_vowel(c)) {
                vowel_count++;
            }
        }
        if (vowel_count > 1) {
            count++;
        }
    }
    return count;
}

int words_greater_len(const std::string& paragraph, int length) {
    int count = 0;
    std::string word;
    std::istringstream iss(paragraph);
    while (iss >> word) {
        int actual_length = 0;
        for (char c : word) {
            if (std::isalpha(c)) {
                actual_length++;
            }
        }
        if (actual_length > length) {
            count++;
        }
    }
    return count;
}

int words_smaller_len(const std::string& paragraph, int length) {
    int count = 0;
    std::string word;
    std::istringstream iss(paragraph);
    while (iss >> word) {
        if (word.length() < length) {
            count++;
        }
    }
    return count;
}

int main() {
    std::string paragraph;
    std::cout << "Enter a paragraph: ";
    std::getline(std::cin, paragraph);

    std::cout << "Neatly printed paragraph: " << std::endl;
    std::cout << paragraph << std::endl;

    int wordCount = count_words(paragraph);
    std::cout << "Number of words in the paragraph: " << wordCount << std::endl;

    auto vowelsConsonants = count_vowels_consonants(paragraph);
    std::cout << "Number of vowels: " << vowelsConsonants.first << std::endl;
    std::cout << "Number of consonants: " << vowelsConsonants.second << std::endl;

    int punctuationWordCount = count_punctuation_words(paragraph);
    std::cout << "Number of words that use punctuation marks: " << punctuationWordCount << std::endl;

    int multipleVowelsWordCount = countMultipleVowelsWords(paragraph);
    std::cout << "Number of words that use more than one vowel: " << multipleVowelsWordCount << std::endl;

    int userLength;
    std::cout << "Enter a length of a word: ";
    std::cin >> userLength;

    int wordsWithLengthGreaterThan = countWordsWithLengthGreaterThan(paragraph, userLength);
    std::cout << "Number of words with length greater than " << userLength << ": " << wordsWithLengthGreaterThan << std::endl;

    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<int> dist(6, 10);
    int randomLength = dist(rng);

    int wordsWithLengthSmallerThan = countWordsWithLengthSmallerThan(paragraph, randomLength);
    std::cout << "Number of words with length smaller than randomly selected length (" << randomLength << "): " << wordsWithLengthSmallerThan << std::endl;

    return 0;
}