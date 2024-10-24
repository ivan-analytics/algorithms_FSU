#include <iostream>
#include <sstream>
#include <cctype>  // for std::isalpha and std::isalnum
#include "stack.h"

using namespace std;
using namespace cop4530;


bool is_operator(string input) {
    return ((input == "+") || (input == "-") || (input == "*") || (input == "/"));
}

bool is_number(const std::string& input) {
    try {
        std::stof(input); // tries to convert string to float
        // success
        return true;
    } catch (...) {
        return false;
    }
}

bool is_variable(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    // the first character must be an English letter (a-z, A-Z)
    if (!std::isalpha(str[0])) {
        return false;
    }

    // the rest of the characters must be alphanumeric or underscores
    for (size_t i = 1; i < str.length(); ++i) {
        if (!std::isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }

    return true;
}

int main() {
    cop4530::Stack<string> st = cop4530::Stack<string>();
    string line;
    string input;
    string prev_input{};
    std::vector<string> output{};

    // read the entire line (including spaces) until enter is pressed
    // using stringstream to process each word within a line separately
    std::getline(std::cin, line);
    std::stringstream line_split(line);
    while (line_split >> input) {
        // If input symbol is "(", push it into stack.
        if (input == "(") {
            st.push(input);
        } 

        // TODO: handle variables
        else if (is_number(input) || is_variable(input)) {
            st.push(input);
        }

        // If input operator is "+", "-", "*", or "/", repeatedly output the top of the stack and pop the stack until the stack is either (i) empty ; 
        // (ii) a "(" is at the top of the stack; or (iii) a lower-precedence operator is at the top of the stack. 
        // Then push the input operator into the stack.
        // "+", "-", "*", or "/"
        else if (is_operator(input)) {
            string prev_el{};
            string cur_el;
            while (true) {
                if (st.empty()) break;
                cur_el = st.top();

                if (cur_el == "(") break;
                // if lower-precedence operator is at the top of the stack - stop
                if ((prev_el == "*" || prev_el == "/") && (cur_el == "+" || cur_el == "-")) break;

                // push the input into the stack and go to the next element
                st.pop();
                output.push_back(cur_el);
                prev_el = cur_el;
            }

            // push the input operator into the stack
            st.push(input);
        }

        // If input operator is ")" and the last input processed was an operator, report an error. 
        // Otherwise, repeatedly output the top of the stack and pop the stack until a "(" is at the top of the stack. 
        // Then pop the stack discarding the parenthesis. If the stack is emptied without a "(" being found, report error.
        else if (input == ")") {
            if (is_operator(prev_input)) {
                std::cout << "Error: Missing operand in postfix string. Unable to evaluate postfix string!" << endl;
                return(EXIT_FAILURE);
            }

            string cur_el;
            while (true) {
                if (st.empty()) {
                    std::cout << "Error: *description*" << endl;
                    return(EXIT_FAILURE);
                }

                // push the input into the stack and go to the next element
                cur_el = st.top();
                if (cur_el == "(") break;
                st.pop();
                output.push_back(cur_el);
            }

            // making sure program goes as expected
            if (cur_el != "(") throw std::runtime_error("while ended but last el of the stack is not '('");
            st.pop();
        }

        else std::runtime_error("unexpected case");


        prev_input = input;
    }

    // If end of input is reached and the last input processed was an operator or "(", report an error. 
    // Otherwise output the top of the stack and pop the stack until the stack is empty.  
    // If an "(" is found in the stack during this process, report error.
    if (is_operator(prev_input) || prev_input == "(") {
        std::cout << "Error: *description*" << endl;
        return(EXIT_FAILURE);
    }
    while(!st.empty()) {
        auto el = st.top();
        if (el == "(") {
            std::cout << "Error: *description*" << endl;
            return(EXIT_FAILURE);
        }
        output.push_back(el);
        st.pop();
    }


    // print the constructed expression
    for (auto& el : output)
        std::cout << el << " ";
    

    return(EXIT_SUCCESS);
}