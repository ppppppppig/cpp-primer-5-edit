#pragma once
#include "Head.h"
#include "Shared_ptr.h"
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);//���������ҪBlob�����Ա����ڸ�����֮ǰ����Blob��
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
	//Ӧ�ö��������汾��һ��������һ���ǳ���
	T& front();
	T& back();
	const T& front() const;
	const T& back() const;
	T& operator[](size_t i);//�±������ͨ�����������汾��һ�������汾��һ���ǳ����汾
	const T& operator[](size_t i) const;
	~Blob();
private:
	//����̬�ڴ��е�vector����
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