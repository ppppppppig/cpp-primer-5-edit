#include <iostream>
#include "StrVec.h"
#include "Vec.h"
using std::cout;
using std::endl;
int main() {
	Vec<StrVec> s;
	StrVec ss{ "fdsf","vcxcvcx" };
	s.emplace_back(ss);
	return 0;
} 