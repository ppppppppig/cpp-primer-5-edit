#pragma once
#include "Head.h"
//��΢����ôһ��������ڴ�й©��ģ�黯���Ĳ���ô��
template <typename T> class Vec {
	//�����׼���vector��������ԭ�ڴ����·���ԭ�ڴ��˫���ڴ�
public:
	Vec() :elements(nullptr), cap(nullptr), first_free(nullptr) {}//Ĭ�ϳ�ʼ��
	Vec(std::initializer_list<T> il) {//�б��ʼ��
		T *data = alloc.allocate(il.size());
		elements = data;
		for (const auto &v : il) {
			alloc.construct(data++, v);
		}
		first_free = cap = data;
	}
	//�������죬�ƶ���������������ֵ���ƶ���ֵ
	Vec(const Vec &);
	Vec<T>(Vec<T> &&v) noexcept;
	Vec& operator=(const Vec&);
	Vec& operator=(Vec&&) noexcept;
	~Vec();
	//�����Ժ���
	T& front();
	T& back();
	void clear();//���ջ��ڴ�
	T& resize(size_t, int);
	T* begin();
	T* end();
	void push_back(T );
	void pop_back();
	size_t capacity();
	size_t size();
	void reserve(size_t n);
	template <typename... Args>
	void emplace_back(Args&&... args) {//������ֵ��ʹ���ƶ����죬��ֵʹ�ÿ������졣
		alloc.construct(first_free++, std::forward<Args>(args)...);
	}
private:
	std::allocator<T> alloc;
	void chk_n_alloc();//����Ƿ���Ҫ���·����ڴ棬����Ҫ�������·���
	void free();//��������ڴ�
	void assign(size_t sz);
	void reallocate();//���·����ڴ�
	void check(size_t, string &);
	T* alloc_copy(T*, T*, T *);
	T *cap;//ָ���������ڴ����һ��λ�ú����λ��
	T *first_free;
	T *elements;//��Ԫ��
};
template <typename T> inline void Vec<T>::chk_n_alloc() {//����Ƿ���Ҫ���·����ڴ棬����Ҫ�������·���
	if (size() == capacity()) reallocate();
}
template <typename T> inline void Vec<T>::reallocate() {
	auto sz = size() ? size() * 2 : 1;
	assign(sz);
}
template <typename T> inline void Vec<T>::assign(size_t sz) {//��ԭVec�е����ݿ�����һ��������sz�����ݵ��ڴ���
	T *data = alloc.allocate(sz);
	auto elements_1 = data;
	data = alloc_copy(this->begin(),this->end(), data);
	free();
	elements = elements_1;
	first_free = data;
	cap = elements + sz;
}
template <typename T> inline void Vec<T>::free() {//destory�����ڴ�
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
		alloc.construct(data++, std::move(*beg));//�ƶ�����졣
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
	if (this != &m) {//�Ը�ֵ���
		reallocate();
		elements = alloc.allocate(m.size());
		auto data = alloc_copy(v.begin(), v.end(), data);
		first_free = elements = data;
	}
	return *this;
}
template <typename T> inline Vec<T>& Vec<T>::operator=(Vec &&m) noexcept {
	if (this != &m) {//�Ը�ֵ���
		reallocate();
		elements = m.elements;
		cap = m.cap;
		first_free = m.first_free;
		m.first_free = m.cap = m.elements = nullptr;
	}
	return *this;
}
template <typename T> inline Vec<T>::~Vec() {
	//�����ڴ沢��ָ������Ϊnullptr
	free();
	first_free = cap = elements = nullptr;//����Ҫ��Ҫ����Щ��λnullptr
}
//�����Ժ���
template <typename T> inline T& Vec<T>::front() {
	check(0, "empty Vec");
	return *begin();
}
template <typename T> inline T& Vec<T>::back() {
	check(first_free - elements, "ddddddddddddddddddddddddddddddddddddddddddddd");
	return *(first_free - 1);
}
template <typename T> inline void Vec<T>::clear() {//���ջ��ڴ�
	if (elements) {
		while (first_free != elements)
			alloc.destroy(--first_free);
	}
}
template <typename T> inline T& Vec<T>::resize(size_t, int);//��ʱ��д
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
	//ֻ�е�n����ԭ�ڴ棬�ŷ���
	if (n > capacity())
		assign(n);
}
template <typename T> inline size_t Vec<T>::size() {
	return first_free - elements;
}