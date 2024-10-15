#include <string>
#include <iostream>
#include "List.h"

using namespace std;


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

	int a = int{};
	auto b = cop4530::List<int>();
	cout << "res: " << b << ".";

	return 0;
}