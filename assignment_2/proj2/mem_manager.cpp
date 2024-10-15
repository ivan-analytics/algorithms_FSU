#include <string>
#include "MyMemory.h"

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

	// print_menu();

	MyMemory m = MyMemory(8, 20);
	m.dump();

	m.req_mem(7);
	m.req_mem(20);
	m.req_mem(14);
	m.req_mem(14);
	m.req_mem(14);
	m.req_mem(14);
	m.req_mem(14);
	m.dump();

	// m.release_mem(0, 5);
	// m.release_mem(1, 5);
	// m.release_mem(1, 20);
	// m.release_mem(1, 21);
	// m.release_mem(5, 5);
	// m.dump();
	m.merge_mem();
	m.dump();

	return 0;
}