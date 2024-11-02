#include <iostream>
#include <sstream>
#include <cctype>  // for std::isalpha and std::isalnum
#include "stack.h"

using namespace std;
using namespace cop4530;


bool is_operator(string input) {
    return ((input == "+") || (input == "-") || (input == "*") || (input == "/"));
}

float apply_operator(float operand1, float operand2, string operator_to_apply) {
    if (operator_to_apply == "+")
        return operand1 + operand2;
    else if (operator_to_apply == "-")
        return operand1 - operand2;
    else if (operator_to_apply == "*")
        return operand1 * operand2;
    else if (operator_to_apply == "/")
        return operand1 / operand2;
    else throw std::runtime_error("unknown operator");
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

void print_res(string expr, bool is_error, bool is_var, float eval_res = 0) {
    // expression
    std::cout << endl << "Postfix expression: ";
    std::cout << expr << " ";

    // evaluation
    std::cout << endl << "Postfix evaluation: ";
    std::cout << expr << " ";
    std::cout << " = ";

    if (is_error) {
        cout << expr;
        return;
    }

    if (!is_var) {
        cout << eval_res;
    } else {
        std::cout << expr;
    }

    return;
}

int in2post_logic(string& line) {
    cop4530::Stack<string> st = cop4530::Stack<string>();
    string input;
    string prev_input{};
    string total_input{}; // full initial expression for error output
    std::vector<string> output{};

    // read the entire line (including spaces) until enter is pressed
    // using stringstream to process each word within a line separately
    std::stringstream line_split(line);
    while (line_split >> input) {
        total_input += input + " ";

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
            string cur_el;
            while (true) {
                if (st.empty()) break;
                cur_el = st.top();

                if (cur_el == "(") break;
                // if lower-precedence operator is at the top of the stack - stop
                if ((input == "*" || input == "/") && (cur_el == "+" || cur_el == "-")) break;

                // push the input into the stack and go to the next element
                st.pop();
                output.push_back(cur_el);
            }

            // push the operator into the stack
            st.push(input);
        }

        // If input operator is ")" and the last input processed was an operator, report an error. 
        // Otherwise, repeatedly output the top of the stack and pop the stack until a "(" is at the top of the stack. 
        // Then pop the stack discarding the parenthesis. If the stack is emptied without a "(" being found, report error.
        else if (input == ")") {
            if (is_operator(prev_input)) {
                std::cout << "Error: Infix expression: ";
                std::cout << total_input;
                std::cout << "has mismatched parens!";
                return(EXIT_FAILURE);
            }

            string cur_el;
            while (true) {
                if (st.empty()) {
                    std::cout << "Error: 1" << endl;
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
    if (is_operator(prev_input)) {
        print_res(total_input, true, true);
        std::cout << endl << "Error: Missing operand in postfix string. Unable to evaluate postfix string!" << endl;
        return(EXIT_FAILURE);
    }

    if (prev_input == "(") {
        std::cout << "Error: Infix expression: ";
        std::cout << total_input;
        std::cout << "has mismatched parens!";
        return(EXIT_FAILURE);
    }

    while(!st.empty()) {
        auto el = st.top();
        if (el == "(") {
            std::cout << "Error: Infix expression: ";
            std::cout << total_input;
            std::cout << "has mismatched parens!";
            return(EXIT_FAILURE);
        }
        output.push_back(el);
        st.pop();
    }


    // // print the constructed expression
    // std::cout << endl << "Postfix expression: ";
    // for (auto& el : output)
    //     std::cout << el << " ";

 
    // Assume that the expression contains only numeric operands (no variable names). 
    // Operands are pushed into the stack as they are ready from the input. 
    // When an operator is read from the input, remove the two values on the top of the stack, apply the operator to them, and push the result onto the stack. 
    // If an operator is read and the stack has fewer than two elements in it, report an error.  
    // If end of input is reached and the stack has more than one operand left in it, report an error. 
    // If end of input is reached and the stack has exactly one operand in it, print that as the final result, or 0 if the stack is empty.


    // std::cout << endl << "Postfix evaluation: ";
    // for (auto& el : output)
    //     std::cout << el << " ";
    // std::cout << " = ";
    cop4530::Stack<float> st_eval = cop4530::Stack<float>();
    auto itr = output.begin();
    while (itr != output.end()) {
        if (is_variable(*itr)) {
            string out{};
            for (auto& el : output) out += el + " ";
            print_res(out, false, true);
            return(EXIT_SUCCESS);
        }

        else if (is_number(*itr)) 
            st_eval.push(std::stof(*itr));

        else if (is_operator(*itr)) {
            if (st_eval.size() < 2) {
                std::cout << "Error: Missing operands in the expression" << endl;
                return(EXIT_FAILURE);
            }
            float operand1 = st_eval.top(); st_eval.pop();
            float operand2 = st_eval.top(); st_eval.pop();

            float res = apply_operator(operand2, operand1, *itr);
            st_eval.push(res);

        }
        else throw std::runtime_error("unexpected case");

        itr++;
    }

    if (st_eval.size() > 1) {
        std::cout << "Error: " << endl;
        return(EXIT_FAILURE);
    } else if (st_eval.size() == 1) {
        string out{};
        for (auto& el : output) out += el + " ";
        print_res(out, false, false, st_eval.top());
    }
    return(EXIT_SUCCESS);
}

int main() {
    string line;
    std::cout << "Enter infix expression (\"exit\" to quit): ";
    while (std::getline(std::cin, line)) {
        if (line == "exit") return(EXIT_SUCCESS);
        if (line == "") {
            print_res("Empty postfix", true, false);
        }
        in2post_logic(line);
        std::cout << std::endl;
        std::cout << "Enter infix expression (\"exit\" to quit): ";
    }
}