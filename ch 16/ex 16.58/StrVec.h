#pragma once
#include "Head.h"
class StrVec
{
public:
	StrVec() :elements(nullptr), cap(nullptr), first_free(nullptr) {}
	StrVec(std::initializer_list<string> li)
	{
		string *data = alloc.allocate(li.size());
		elements = data;
		first_free = cap = elements + li.size();
		std::uninitialized_copy(li.begin(), li.end(), data);
	}
	StrVec(const StrVec &);
	StrVec& operator=(const StrVec &);
	~StrVec();
	void push_back(const string&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin() const { return elements; }
	string* end() const { return first_free; }
	void resize(size_t);
	void reserve(size_t);
	template <typename... Args>
	void emplace_back(Args&&... rest) {
		chk_n_alloc();
		alloc.construct(first_free++, std::forward<Args>(rest)...);
	}
	//�ƶ���ֵ���ƶ�����
	StrVec(StrVec &&) noexcept;
	StrVec& operator=(StrVec &&) noexcept;
	StrVec& operator=(std::initializer_list<string> il);
private:
	std::allocator<string> alloc;
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	void free();
	void reallocate();
	std::pair<string *, string *> alloc_n_copy(const string *b, const string *e);
	string *cap;//ָ���������ڴ����һ��λ�ú����λ��
	string *first_free;
	string *elements;
};