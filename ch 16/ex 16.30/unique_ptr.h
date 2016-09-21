#pragma once
#include <iostream>
#include <memory>
template <typename T,typename D=std::default_delete<T>>
class unique_ptr {
	T *ptr;
	D del;
public:
	unique_ptr() :ptr(nullptr), del(nullptr) {}
	unique_ptr(T *p, D d) :ptr(new T()), del(d) {}
	T& operator*() {
		return *ptr;
	}
	~unique_ptr() {
		del(ptr);
	}
};