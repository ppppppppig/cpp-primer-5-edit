#include <iostream>
#include <utility>
using std::cout;
using std::endl;
void f(int v1, int &v2) {
	cout << v1 << ++v2 << endl;
}
template <typename F,typename T1,typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {//T1为in&，T2为int
	f(std::forward<T2>(t2), std::forward<T1>(t1));//第一个实参类型为int&&,第二个是int& &&=int&。
}
int main() {
	int i = 42;
	flip(f, i, 42);
	cout << i << endl;
	return 0;
} 