#pragma once
#include "Head.h"
//稍微有那么一点可能有内存泄漏，模块化做的不怎么好
template <typename T> class Vec {
	//仿造标准库的vector，当超过原内存重新分配原内存的双倍内存
public:
	Vec() :elements(nullptr), cap(nullptr), first_free(nullptr) {}//默认初始化
	Vec(std::initializer_list<T> il) {//列表初始化
		T *data = alloc.allocate(il.size());
		elements = data;
		for (const auto &v : il) {
			alloc.construct(data++, v);
		}
		first_free = cap = data;
	}
	//拷贝构造，移动拷贝，析构，赋值，移动赋值
	Vec(const Vec &);
	Vec<T>(Vec<T> &&v) noexcept;
	Vec& operator=(const Vec&);
	Vec& operator=(Vec&&) noexcept;
	~Vec();
	//功能性函数
	T& front();
	T& back();
	void clear();//不收回内存
	T& resize(size_t, int);
	T* begin();
	T* end();
	void push_back(T );
	void pop_back();
	size_t capacity();
	size_t size();
	void reserve(size_t n);
	template <typename... Args>
	void emplace_back(Args&&... args) {//对于右值，使用移动构造，左值使用拷贝构造。
		alloc.construct(first_free++, std::forward<Args>(args)...);
	}
private:
	std::allocator<T> alloc;
	void chk_n_alloc();//检查是否需要重新分配内存，若需要，则重新分配
	void free();//清除所有内存
	void assign(size_t sz);
	void reallocate();//重新分配内存
	void check(size_t, string &);
	T* alloc_copy(T*, T*, T *);
	T *cap;//指向所分配内存最后一个位置后面的位置
	T *first_free;
	T *elements;//首元素
};
template <typename T> inline void Vec<T>::chk_n_alloc() {//检查是否需要重新分配内存，若需要，则重新分配
	if (size() == capacity()) reallocate();
}
template <typename T> inline void Vec<T>::reallocate() {
	auto sz = size() ? size() * 2 : 1;
	assign(sz);
}
template <typename T> inline void Vec<T>::assign(size_t sz) {//将原Vec中的数据拷贝到一个能容纳sz组数据的内存中
	T *data = alloc.allocate(sz);
	auto elements_1 = data;
	data = alloc_copy(this->begin(),this->end(), data);
	free();
	elements = elements_1;
	first_free = data;
	cap = elements + sz;
}
template <typename T> inline void Vec<T>::free() {//destory所有内存
	if (elements) {
		while (first_free != elements)
			alloc.destroy(--first_free);
	}
	alloc.deallocate(elements, cap - elements);
}
template <typename T> inline void Vec<T>::check(size_t n, string &msg) {
	if (n >= size()) throw out_of_range(msg);
}
template <typename T> inline T* Vec<T>::alloc_copy(T *l, T *r, T *data) {
	for (T *beg = l; beg != r;++beg)
		alloc.construct(data++, std::move(*beg));//移动会更快。
	return data;
}
template <typename T> inline Vec<T>::Vec(const Vec &v) {
	auto data = alloc.allocate(v.size());
	elements = data;
	data = alloc_copy(v.begin(),v.end(), data);
	fist_free = cap = data;
}
template <typename T> 
inline Vec<T>::Vec(Vec &&v) noexcept :elements(v.elements),first_free(v.first_free),cap(v.cap)  {
	v.elements = v.first_free = v.cap = nullptr;
}
template <typename T> inline Vec<T>& Vec<T>::operator=(const Vec &m) {
	if (this != &m) {//自赋值检查
		reallocate();
		elements = alloc.allocate(m.size());
		auto data = alloc_copy(v.begin(), v.end(), data);
		first_free = elements = data;
	}
	return *this;
}
template <typename T> inline Vec<T>& Vec<T>::operator=(Vec &&m) noexcept {
	if (this != &m) {//自赋值检查
		reallocate();
		elements = m.elements;
		cap = m.cap;
		first_free = m.first_free;
		m.first_free = m.cap = m.elements = nullptr;
	}
	return *this;
}
template <typename T> inline Vec<T>::~Vec() {
	//销毁内存并将指针重置为nullptr
	free();
	first_free = cap = elements = nullptr;//到底要不要将这些置位nullptr
}
//功能性函数
template <typename T> inline T& Vec<T>::front() {
	check(0, "empty Vec");
	return *begin();
}
template <typename T> inline T& Vec<T>::back() {
	check(first_free - elements, "ddddddddddddddddddddddddddddddddddddddddddddd");
	return *(first_free - 1);
}
template <typename T> inline void Vec<T>::clear() {//不收回内存
	if (elements) {
		while (first_free != elements)
			alloc.destroy(--first_free);
	}
}
template <typename T> inline T& Vec<T>::resize(size_t, int);//暂时不写
template <typename T> inline T* Vec<T>::begin() {
	return elements;
}
template <typename T> inline T* Vec<T>::end() {
	return first_free;
}
template <typename T> inline void Vec<T>::push_back(T val) {
	chk_n_alloc();
	alloc.construct(first_free++, val);
}
template <typename T> inline void Vec<T>::pop_back() {
	if (first_free == elements)
		throw runtime_error("ddd");
	alloc.destroy(--first_free);
}
template <typename T> inline size_t Vec<T>::capacity() {
	return cap - elements;
}
template <typename T> inline void Vec<T>::reserve(size_t n) {
	//只有当n大于原内存，才分配
	if (n > capacity())
		assign(n);
}
template <typename T> inline size_t Vec<T>::size() {
	return first_free - elements;
}