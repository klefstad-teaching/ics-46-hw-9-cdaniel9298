
#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return true;
    int len1 = word1.length();
    int len2 = word2.length();

    // Case 1: Words are the same length, differing by exactly one letter (substitution)
    if (len1 == len2) {
        int diff_count = 0;
        for (int i = 0; i < len1; i++) {
            if (word1[i] != word2[i]) {
                diff_count++;
                if (diff_count > 1) return false;
            }
        }
        return (diff_count == 1);
    }

    // Case 2: One word is longer by exactly one character (insertion/deletion)
    if (abs(len1 - len2) == 1) {
        const string& longer = (len1 > len2) ? word1 : word2;
        const string& shorter = (len1 > len2) ? word2 : word1;

        int i = 0, j = 0;
        bool found_difference = false;
        while (i < longer.length() && j < shorter.length()) {
            if (longer[i] != shorter[j]) {
                if (found_difference) return false;
                found_difference = true;
                i++;
            } else {
                i++; j++;
            }
        }
        return true;
    }

    return false;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    file.close();
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if(str1 == str2) return true;
    
    int len1 = str1.length(), len2 = str2.length();

    if (abs(len1 - len2) > d) return false;

    int diff_count = 0;
    if (len1 == len2) {  // Case 1: Check for a single substitution
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                diff_count++;
                if (diff_count > d) return false;
            }
        }
        return diff_count == d;
    }

    // Case 2: Check for insertion/deletion (only allow 1 edit)
    const string& longer = (len1 > len2) ? str1 : str2;
    const string& shorter = (len1 > len2) ? str2 : str1;

    int i = 0, j = 0;
    while (i < longer.length() && j < shorter.length()) {
        if (longer[i] != shorter[j]) {
            if (++diff_count > d) return false;
            i++;
        } else {
            i++; j++;
        }
    }

    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }

    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (visited.find(word) != visited.end()) continue;
            if (!edit_distance_within(last_word, word, 1)) continue;

            vector<string> new_ladder = ladder;
            new_ladder.push_back(word);

            if (word == end_word) return new_ladder;

            visited.insert(word);
            ladder_queue.push(new_ladder);
        }
    }

    return {};
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << " ";
    }
    cout << "\n";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}