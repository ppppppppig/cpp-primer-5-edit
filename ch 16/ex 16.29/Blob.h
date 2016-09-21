#pragma once
#include "Head.h"
#include "Shared_ptr.h"
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);//运算符中需要Blob，所以必须在该声明之前声明Blob。
template <typename T> class Blob {
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
public:
	Blob();
	Blob(std::initializer_list<T> il);
	template <typename It> Blob(It b, It e);
	size_t size() const {
		return data->size;
	}
	bool empty() const {
		return data->empty();
	} 
	void push_back(const T &val) {
		data->push_back(val);
	}
	void push_back(T &&val) {
		data->push_back(std::move(val));
	}
	void pop_back() {
		check(0, "out of range.");
		data->pop_back();
	}
	//应该定义两个版本，一个常量，一个非常量
	T& front();
	T& back();
	const T& front() const;
	const T& back() const;
	T& operator[](size_t i);//下标运算符通常包含两个版本，一个常量版本，一个非常量版本
	const T& operator[](size_t i) const;
	~Blob();
private:
	//管理动态内存中的vector容器
	Shared_ptr<vector<T>> data;
	void check(size_t i, const string &msg) const;
};
template <typename T> inline Blob<T>::Blob() :data(std::make_shared<vector<T>>()) {}
template <typename T> inline Blob<T>::Blob(std::initializer_list<T> il):
	data(make_shared<vector<T>>(il)){}
template <typename T> inline T& Blob<T>::front(){
	check(0, "out of range.");
	return data->front();
}
template <typename T> inline T& Blob<T>::back(){
	check(0, "out of range.");
	return data->back();
}
template <typename T> inline const T& Blob<T>::front() const {
	check(0, "out of range.");
	return data->front();
}
template <typename T> inline const T& Blob<T>::back() const {
	check(0, "out of range.");
	return data->back();
}
template <typename T> inline void Blob<T>::check(size_t i, const string &msg) const {
	if (i >= (data->size()))
		throw out_of_range(msg);
}
template <typename T> inline T& Blob<T>::operator[](size_t i) {
	return (*data)[i];
}
template <typename T> inline const T& Blob<T>::operator[](size_t i) const{
	return (*data)[i];
}
template<typename T>
inline Blob<T>::~Blob()
{
	data.reset();
	cout << "deleting..." << endl;
}
template <typename T>
template <typename It> Blob<T>::Blob(It b, It e) :data(make_shared<vector<T>>(b, e)) {}