#include <string>
#include <limits>
#include "MyMemory.h"

using namespace std;


pair<int, int> init_prompt() {
	int num_input, len_input;
	cout << "Memory configuration: " << endl;
	cout << "Number of memory blocks (integer): ";
	cin >> num_input;
	cout << endl;
	
	// validation
	while (cin.fail()) {
		// clearing the trails of invalid input
        std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Number of memory blocks (integer): ";
		cin >> num_input;
		cout << endl;
	}

	cout << "Memory block size (integer): ";
	cin >> len_input;

	// validation
	if (cin.fail()) {
		// clearing the trails of invalid input
        std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return init_prompt();
	}

	return make_pair(num_input, len_input);
}

void print_menu() {
	cout << string(20, '=') << endl;
	cout << "d: memory dump" << endl;
	cout << "r: request memory" << endl;
	cout << "l: release memory" << endl;
	cout << "m: merge memory" << endl;
	cout << "x: quit program" << endl;
	cout << "Your choice: ";	
}


int main() {
	auto res = init_prompt();
	int num = res.first;
	int len = res.second;

	// create a memory object
	MyMemory memory = MyMemory(num, len);

	string command_input_str;
	char command_input;
	int ind_, len_;
	while (true) {
		print_menu();
		cin >> command_input_str;
		command_input = command_input_str[0];
		cout << "choice: " << command_input << endl;

		switch (command_input) {
			case 'd':
				// d: memory dump
				memory.dump();
				break;
			case 'r':
				// r: request memory
				cout << "Requested memory size (integer): ";
				cin >> len_;
				memory.req_mem(len_);
				break;
			case 'l':
				// l: release memory
				cout << "Release memory index (integer): ";
				cin >> ind_;
				cout << "Release memory length (integer): ";
				cin >> len_;
				memory.release_mem(ind_, len_);
				break;
			case 'm':
				// m: merge memory
				memory.merge_mem();
				break;
			case 'x':
				// x: quit program
				return 1;
			default:
				cout << endl << "*****Error: Invalid entry.  Try again." << endl;
		}
	}
	
	return 1;
}