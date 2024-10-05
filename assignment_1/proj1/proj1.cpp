#include <iostream>
#include <string>
#include <map>
#include <utility>  // For std::pair
#include <stdexcept> // For std::runtime_error
#include <iomanip> // For std::setw
#include <type_traits> // For is_same_v in a template funcitons
#include <vector>
#include <unordered_map>
#include <algorithm> // for std::sort
using namespace std;


enum char_type {
    LETTER,
    DIGIT,
    OTHER
};

enum str_type {
    WORD,
    NUMBER,
    NA // Non-Applicable
};

bool is_in_range(int x, int min, int max) {
    return x >= min && x <= max;
}


char_type get_char_type(char a) {
    // ascii table
    // chars:
    // [65, 90]
    // [97, 122]
    // digits:
    // [48, 57]
    if (is_in_range(static_cast<int>(a), 65, 90) || is_in_range(static_cast<int>(a), 97, 122)) {
        return LETTER;
    } else if (is_in_range(static_cast<int>(a), 48, 57)) {
        return DIGIT;
    } else {
        return OTHER;
    }
    throw std::runtime_error("custom error");
}


// add sequence to words or numbers map
// if this sequence a word or number then add it to the words/numbers map
void add_sequence_to_container(
    char_type prev_char_type_,
    std::unordered_map<std::string, std::pair<int, int> > &words_, 
    std::unordered_map<std::string, std::pair<int, int> > &numbers_,
    std::string sequence_,
    int current_iteration
    ) 
{
    if (prev_char_type_ == LETTER) {
        // words should be case insensitive according to the assignment statement
        string sequence_temp_ = sequence_;
        std::transform(sequence_temp_.begin(), sequence_temp_.end(), sequence_temp_.begin(), [](unsigned char c){ return std::tolower(c); });

        auto this_seq_in_map = words_.find(sequence_temp_);
        // if its already been in the map exists
        if (this_seq_in_map != words_.end()) {
            // increment the counter 
            this_seq_in_map->second.second++;
        } else {
            // add to the map, fixing the insertion order by adding i and setting number of occurencies (counter) to 1
            words_.insert({sequence_temp_, {current_iteration, 1}});
        }
    } else if (prev_char_type_ == DIGIT) {
        auto this_seq_in_map = numbers_.find(sequence_);
        // if its already been in the map exists
        if (this_seq_in_map != numbers_.end()) {
            // increment the counter
            this_seq_in_map->second.second++;
        } else {
            // add to the map, fixing the insertion order by adding i and setting number of occurencies (counter) to 1
            numbers_.insert({sequence_, {current_iteration, 1}});
        }
    }
}

// add sequence to characters map
void add_char_to_container(
    std::unordered_map<char, std::pair<int, int> > &characters_,
    char cur_char_,
    int current_iteration
    ) 
{
    // add cur char to characters map
    auto this_char_in_map = characters_.find(cur_char_);
    // if its already been in the map exists
    if (this_char_in_map != characters_.end()) {
        // increment the counter 
        this_char_in_map->second.second++;
    } else {
        // add to the map, fixing the insertion order by adding i and setting number of occurencies (counter) to 1
        characters_.insert({cur_char_, {current_iteration, 1}});
    }
}


// finds lenght of the longest string to be displayed
int get_length_of_longest_string_to_display(
    std::vector<pair<string, pair<int, int>>> &words_vec_, 
    std::vector<pair<string, pair<int, int>>> &numbers_vec_
    )
{

    if (words_vec_.empty() && numbers_vec_.empty()) return 0;
    int longest_str = 0;
    for (int i = 0; i < (words_vec_.size() >= 10 ? 10 : words_vec_.size()); i++) 
        if (words_vec_[i].first.size() > longest_str) longest_str = words_vec_[i].first.size();
    for (int i = 0; i < (numbers_vec_.size() >= 10 ? 10 : numbers_vec_.size()); i++) 
        if (numbers_vec_[i].first.size() > longest_str) longest_str = numbers_vec_[i].first.size();

    return longest_str;
}


// template function to print elements of all vectors
// chose to use template function just to hide the logic of the output 
// of all the containers (both with characters and words/numbers) under one function 
// (even though it does not decrease duplicate code much)
template <typename T>
void output_to_cout(const std::vector<pair<T, pair<int, int>>>& vec, int longest, str_type str_type_) {
    int num_of_iterations = vec.size() >= 10 ? 10 : vec.size();
    int OFFSET = 5;
    if constexpr (std::is_same<T, char>::value) {
        int SPECIAL_CHAR_LENGTH = 2;
        std::cout << "Total " << vec.size() << " different characters, " << num_of_iterations << " most used characters:" << std::endl;
        for (int i = 0; i < num_of_iterations; i++) {
            std::cout << "No. " << i << ": ";
            if (vec[i].first == '\n') {
                std::cout << "\\n" << std::setw(longest + OFFSET - SPECIAL_CHAR_LENGTH) << "" << vec[i].second.second << std::endl;
                continue;
            } else if (vec[i].first == '\t') {
                std::cout << "\\t" << std::setw(longest + OFFSET - SPECIAL_CHAR_LENGTH) << "" << vec[i].second.second << std::endl;
                continue;
            }

            int CHAR_LENGTH = 1;
            std::cout << vec[i].first << std::setw(longest + OFFSET - CHAR_LENGTH)  << "" << vec[i].second.second << std::endl;
        }
    } else if constexpr (std::is_same<T, std::string>::value) {
        string insert;
        if (str_type_ == WORD) insert = "words";
        else if (str_type_ == NUMBER) insert = "numbers";
        else throw std::runtime_error("custom error: output_to_cout not a word or number");
        
        std::cout << "Total " << vec.size() << " different " << insert << ", " << num_of_iterations << " most used " << insert << ":" << std::endl;

        for (int i = 0; i < num_of_iterations; i++) {
            int str_length = vec[i].first.size();
            std::cout << "No. " << i << ": ";
            std::cout << vec[i].first << std::setw(longest - str_length + OFFSET)  << "" << vec[i].second.second << std::endl;
        }
    } else {
        throw std::runtime_error("custom error: output_to_cout template does not handle this type");
    }

    return;
}




int main() {
    // maps that count number of occurencies
    // using hash maps intead of tree maps, since there gonna be a lot of insertion operations that has map does for O(1) instead of 0(logn) of classic tree map, 
    // but sorting should be done separately anyway, since trees are sorted by keys, not by values (number of occurecies) that we need
    
    // pair: 1st int is to keep which el was inserted to map earlier, 2nd int is for counting
    std::unordered_map<char, std::pair<int, int> > characters;
    std::unordered_map<std::string, std::pair<int, int> > words;
    std::unordered_map<std::string, std::pair<int, int> > numbers;


    // support varuables:
    std::string row; // to handle row that getline extracts

    // to keep the count of each symbol 
    // it will be used to determine which elements were added to the container earlier (we gonna need to sort output accounting for that)
    int i = 0;

    int endl_count = -1; // since i use getline and not read char by char, need to count \n separately (getline does not include it in row)
    char_type prev_char_type, cur_char_type; // for identifying switch of type of sequences
    char cur_char; // current char
    std::string sequence = ""; // word or number

    // read until the End Of File
    while (std::cin.eof() != true) {
        std::getline(std::cin, row);

        if (sequence.size() != 0) {
            add_sequence_to_container(prev_char_type, words, numbers, sequence, i);
            sequence.clear();  
        }
        
        for (int j = 0; j < row.size(); j++) {
            cur_char = row[j];
            cur_char_type = get_char_type(cur_char);

            // check if it is a new or continuing sequence
            if (j == 0) {
                // do nothing
            } else if (cur_char_type != prev_char_type) {
                add_sequence_to_container(prev_char_type, words, numbers, sequence, i);
                sequence.clear();
            }

            add_char_to_container(characters, cur_char, i);

            // add cur char to new sequence unless its an OTHER char
            if (cur_char_type != OTHER) {
                sequence.push_back(cur_char);
            }
            prev_char_type = cur_char_type;
            i++;
        }
        endl_count++;
    }

    // add sequence if there was any before EOF
    if (sequence.size() != 0) {
        add_sequence_to_container(prev_char_type, words, numbers, sequence, i);
        sequence.clear();  
    }

    // prepare to sort (map -> vect)
    std::vector<pair<char, pair<int, int>>> characters_vec(characters.begin(), characters.end());
    std::vector<pair<string, pair<int, int>>> words_vec(words.begin(), words.end());
    std::vector<pair<string, pair<int, int>>> numbers_vec(numbers.begin(), numbers.end());

    // adding "\n" manually since getline ignores it unless there wasn't any end lines
    if (endl_count > 0) characters_vec.push_back(make_pair('\n', make_pair(-1, endl_count)));

    // comparators to define how to sort elements
    // sort by count, then by key (characters) or order (words, numbers)
    auto comparator_for_characters = [](const std::pair<char, std::pair<int, int>>& a, const std::pair<char, std::pair<int, int>>& b) {
        // higher count at the top
        if (a.second.second > b.second.second) {
            return true;
        } else if (a.second.second < b.second.second) {
            return false;
        } else {
            // if counts are the same - smaller ascii at the top
            return static_cast<int>(a.first) < static_cast<int>(b.first);
        }
    };  
    auto comparator_for_words_and_numbers = [](const std::pair<string, std::pair<int, int>>& a, const std::pair<string, std::pair<int, int>>& b) {
        // higher count at the top
        if (a.second.second > b.second.second) {
            return true;
        } else if (a.second.second < b.second.second) {
            return false;
        } else {
            // if counts are the same - smaller ascii at the top
            return a.second.first < b.second.first;
        }
        throw std::runtime_error("custom error");
    };  

    // stable to preserve initial order of equal elemets ()
    std::sort(characters_vec.begin(), characters_vec.end(), comparator_for_characters);
    std::sort(words_vec.begin(), words_vec.end(), comparator_for_words_and_numbers);
    std::sort(numbers_vec.begin(), numbers_vec.end(), comparator_for_words_and_numbers);

    // display the result
    int longest_str = get_length_of_longest_string_to_display(words_vec, numbers_vec);
    output_to_cout(characters_vec, longest_str, NA);
    std::cout << std::endl;
    output_to_cout(words_vec, longest_str, WORD);
    std::cout << std::endl;
    output_to_cout(numbers_vec, longest_str, NUMBER);
    
    return 0;
}