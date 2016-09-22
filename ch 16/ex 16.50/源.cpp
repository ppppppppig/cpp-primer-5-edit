#include <iostream>
#include <utility>
//#include "debug_ret.h"
using std::cout;
using std::endl;
template <typename T> void f(T) {
	cout << 1 << endl;
}
template <typename T> void f(const T *) {
	cout << 2 << endl;
}
template <typename T >void g(T) {
	cout << 3 << endl;
}
template <typename T> void g(T*) {
	cout << 4 << endl;
}
int main() {
	int i = 42, *p = &i;
	const int ci = 0, *p2 = &ci;
	g(42);
	g(p);
	g(ci);
	g(p2);
	f(42);
	f(p);
	f(ci);
	f(p2);
	return 0;
} 