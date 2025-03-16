#include "ladder.h"

// g++ ladder.cpp ladder_main.cpp -o ladder_main
// ./ladder_main
int main(){
    set<string> word_list;
    load_words(word_list, "words.txt");

    string start = "marty";
    string end = "curls";

    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
    verify_word_ladder();

    return 0;
}