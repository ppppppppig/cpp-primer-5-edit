#pragma once
#include <iostream>
#include <sstream>
#include <string>
using std::cout;
using std::endl;
template <typename T>
std::string debug_rep(const T &m) {
	cout << "const T &" << endl;
	std::ostringstream f;
	f << m;
	return f.str();
}
template <typename T>
std::string debug_rep(T *m) {
	cout << "T *" << endl;
	std::ostringstream f;
	f << "pointer : " << m;
	if (m) {
		f << " " << debug_rep(*m);
	}
	else
		f << " null pointer!";
	f << endl;
	return f.str();
}
std::string debug_rep(const std::string &m) {
	cout << "const string &" << endl;
	std::ostringstream f;
	f << m;
	return f.str();
}
std::string debug_rep(const char *m) {
	return debug_rep(std::string(m));
}