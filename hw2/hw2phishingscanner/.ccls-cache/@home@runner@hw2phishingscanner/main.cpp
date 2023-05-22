/*
HW 2 Question 2 Phishing Scanner (Matthew Xue 5/20)

The purpose of this code is to scan for phishing. The program will read a paragraph from the user and it will use a map with 30 different words and phrases commonly found in phishing emails to determine if the paragraph is a phishing or legitimate email. Each word and phrase are assigned with a value  (e.g., minus one for unlikely, zero for neutral, one point if it’s somewhat likely, two points if moderately likely, or three points if highly likely). The higher the score, the more likely that the email is fradulent and could be a possible phishing case. 

Two questions to be answered: 
Q: Does your program assign a high point total to some actual phishing emails you’ve received?

Example paragraph:
We recently noticed some unusual activity on your account and it requires immediate attention to ensure the security of your information. Our system detected that your account password has expired , and to regain access , we kindly ask you to click on the following verification link . Failure to do so may result in temporary suspension or limited access to your account .

This paragraph scored a total of 15 points which is pretty high and this paragrah was a phishing attempt. 

Q: Does it assign a high point total to some legitimate e-mails you’ve
received?

We hope this email finds you well. We want to bring your attention to some important updates regarding your account for security purposes. We kindly request your cooperation in completing the verification process to ensure the continued safety of your information. As part of our commitment to transparency, we have included a copy of your latest invoice and financial statement for your reference. Please take a moment to review these documents to ensure accuracy and address any concerns you may have.

This paragraph scored a total of 16 points, but it was actaully a legitimate email sent by the bank. So my phishing scanner cannot fully determine the difference for all cases.
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

// declaring functions
unordered_map<string, int> count_keywords(const string& paragraph, 
const unordered_map<string, int>& phishing_keywords);

int total_points(const unordered_map<string, int>& phishing_keywords, 
const unordered_map<string, int>& counts);

int points_for_keyword(const unordered_map<string, int>& phishing_keywords, 
const unordered_map<string, int>& counts, const string& keyword);

int main() {
  // created a map with 30 words commonly used for phishing
  unordered_map<string, int> phishing_keywords = {
  {"password", 2}, {"account", 1}, {"security", 2}, {"verification", 3},
  {"label", 3}, {"invoice", 3}, {"copy", 1}, {"financial", 1},
  {"notification", 2}, {"statement", 1}, {"document", 2}, {"ticket", 0},
  {"fedex", 2}, {"your account password has expired", 3}, {"don’t miss out", 3}, {"account has been locked for security reasons", 3},
  {"opt in", 2}, {"time sensitive", 1}, {"claim", 2}, {"prize", 0},
  {"verify", 1}, {"limited", -1}, {"attention", 1}, {"confirm", -1},
  {"transaction", 1}, {"urgent", 3}, {"prevent", 0}, {"expire", 2},
  {"important", 1}, {"personal information", 2}
  };

  // ask user for paragraph and store it in variable
  string paragraph; 
  cout << "Hello, please enter a paragraph that you want to be analyzed to see how likely it is a scam: ";
  getline(cin, paragraph);

  // storing count_keywords function in map
  unordered_map<string, int> counts = count_keywords(paragraph, phishing_keywords);

  // displays the counts of phishing keywords for each keyword
  for (const auto& pair : counts) {
    int points_each_keyword = points_for_keyword(phishing_keywords, counts, pair.first);
    cout << pair.first << ": " << pair.second << ", points for word is " << points_each_keyword << endl;
    }

  // disply the total points of paragraph
  int points = total_points(phishing_keywords, counts);
  cout << "Total points is: " << points << endl;
    return 0;
}

// the function counts the total amount of each keyword found in the given
// paragraph. the function stores and returns a unordered map keyword_counts
// the two variables it is using are paragraph and phishing_keywords
unordered_map<string, int> count_keywords(const string& paragraph, const unordered_map<string, int>& phishing_keywords) {
    unordered_map<string, int> keyword_counts;

    for (const auto& pair : phishing_keywords) {
        const string& keyword = pair.first;
        size_t pos = paragraph.find(keyword);
        while (pos != string::npos) {
            keyword_counts[keyword]++;
            pos = paragraph.find(keyword, pos + 1);
        }
    }

    return keyword_counts;
}

// adds up the total points for the entire paragraph. uses two unordered map variables
// phishing_keywords and counts. returns the sum of points of the words
int total_points(const unordered_map<string, int>& phishing_keywords, const unordered_map<string, int>& counts) {
    int sum = 0;
    // retrieve each key and value found in counts
    for (const auto& pair : counts) {
        const string& keyword = pair.first; 
        int count = pair.second;
        // when there is a valid keyword, multiply the amount found and the word value
        if (phishing_keywords.count(keyword) > 0) {
            sum += count * phishing_keywords.at(keyword);
        }
    }
    return sum;
}

// adds up the total points for each keyword. uses two unordered map variables
// phishing_keywords and counts and a string named keyword. returns the points
// for each keyword.
int points_for_keyword(const unordered_map<string, int>& phishing_keywords, const unordered_map<string, int>& counts, const string& keyword) {
int points = 0;
    // when the word is found in the counts and phishing_keywords map
    // find the how many times the word occurs and the value of the word
    if (counts.count(keyword) > 0 && phishing_keywords.count(keyword) > 0) {
        int count = counts.at(keyword);
        int keywordPoints = phishing_keywords.at(keyword);
        points = count * keywordPoints;
    }
    return points;
}