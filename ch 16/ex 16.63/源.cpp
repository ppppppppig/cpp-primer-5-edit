#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
template <typename T1,typename T2>
size_t count(const T1 &v, const T2 &val) {
	size_t co = 0;
	for (const auto &vv : v)
		if (val == vv)
			co++;
	return co;
}
template <>
size_t count(const char * const &v, const char &c) {
	size_t co = 0;
	cout << "ÌØÀý»¯°æ±¾" << endl;
	for (size_t i = 0; *(v + i) != '\0'; ++i) {
		if (*(v + i) == c)
			++co;
	}
	return co;
		
}
int main() {
	std::vector<double> vec{ 1.2,2.4,5.1,6.2,1.2,3.1 };
	cout << count(vec, 1.2) << endl;
	const char *bm = "wo ye man fan nao";
	cout << count(bm, 'n');
	return 0;
} 