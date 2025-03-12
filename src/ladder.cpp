#include "ladder.h"

// use bfs
// prompts the user for two words (start word, end word)
// finds a minimum-length ladder between the words
// Check the input right away to ensure the start and end words are not the same word
// If invalid input occurs, your program should print an error message
// words.txt is the dictionary, ignore letter cases

void error(string word1, string word2, string msg) {
    cerr << "(" << word1 << ", " << word2 << "): " << msg << endl;
}

void print_table(int * dist_table, int i, int j) { // helper function for testing
    for (int n=0; n <= i; ++n) {
        for (int m=0; m <= j; ++m)
            cout << dist_table[m + n*i] << ' ';
        cout << endl;
    }
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // calculating levenshtein distance (an edit distance)
    // https://en.wikipedia.org/wiki/Levenshtein_distance
    // int dist_table[str1.length() + 1][str2.length() + 1] = {0};
    vector<vector<int>> dist_table(str1.length() + 1, vector<int>(str2.length() + 1, 0));
    for (int i=1; i <= str1.length(); ++i) { dist_table[i][0] = i; }
    for (int j=1; j <= str2.length(); ++j) { dist_table[0][j] = j; }
    int substitution_cost;
    for (int j=1; j <= str2.length(); ++j) {
        for (int i=1; i <= str1.length(); ++i) {
            if (tolower(str1[i-1]) == tolower(str2[j-1])) { substitution_cost = 0; }    // ignore letter case
            else { substitution_cost = 1; }
            dist_table[i][j] = min(min(dist_table[i-1][j] + 1,        // insertion
                          dist_table[i][j-1] + 1),                    // deletion
                          dist_table[i-1][j-1] + substitution_cost);  // substitution
        }
    }
    // print_table((int*)dist_table, str1.length(), str2.length());
    return dist_table[str1.length()][str2.length()] == d;  // d is the threshold for difference between 2 words
}

bool is_adjacent(const string& word1, const string& word2) {
    int diff = word1.length() - word2.length();
    if (diff < -1 || 1 < diff) { return false; }
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) { error(begin_word, end_word, "start and end words cannot be the same"); }
    else if (word_list.find(end_word) == word_list.end()) { error(begin_word, end_word, "invalid end word"); }
    else {
        queue<vector<string>> ladder_queue;
        ladder_queue.push({begin_word});
        set<string> visited;
        while (!ladder_queue.empty()) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();
            for (auto & word : word_list) {
                if (is_adjacent(last_word, word) && (visited.find(word) == visited.end())) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    } ladder_queue.push(new_ladder);
                }
            }
        }
    } return vector<string>();
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    for (string word; file >> word;) {
        word_list.insert(word);
    } file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (auto word : ladder) {
        cout << word << ' ';
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "./src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
