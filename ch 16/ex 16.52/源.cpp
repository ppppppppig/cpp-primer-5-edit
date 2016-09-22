#include <iostream>
#include <utility>
#include <string>
//#include "debug_ret.h"
using std::cout;
using std::endl;
template <typename T,typename... Args>
void foo(const T &,const Args&... rest) {
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
	cout << endl;
}
int main() {
	int i = 0; double d = 3.41; std::string s = "fdsfd";
	foo(i);
	foo(i, s);
	foo(i, d, i, s, i);
	foo(i, d, d, d, d, d, d, d);
	return 0;
} 