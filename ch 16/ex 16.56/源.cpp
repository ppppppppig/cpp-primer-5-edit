#include <iostream>
#include <utility>
#include <string>
//#include "debug_ret.h"
using std::cout;
using std::endl;
template <typename T>
void print(std::ostream &, const T &);
template <typename T,typename ...Args>
void print(std::ostream &os, const T &t, Args ...args) {
	os << t << ", ";
	print(os, args...);
}
template <typename... Args>
void print(std::ostream &os, const T &t) {
	os << t;
}
int main() {
	int i = 0; double d = 3.41; std::string s = "fdsfd";
	struct C {
		C() = default;
		int a = 0;
	}a;
	print(cout, i, d, s);
	cout << "gaogaogao" << endl;
	return 0;
} 
