#pragma once
//程序只实现了部分功能
template <typename T>
class Shared_ptr {
	//引用计数（动态内存中的int）
	//delete不是一个对象，添加一个名为Del的可调用对象，因为只有在运行时才会绑定，我们难以知道应该将可调用对象声明成什么类型，
	//由此想到模板，初始化时它的默认实参是nullptr，
	//成员函数使用前判断Del对象是否为null，从而判断使用哪一种删除器。
	void check(const string &) const;
	T *ptr;
	int *refnum;
	struct del_base {
		virtual void destory() = 0;
		virtual ~del_base() { cout << "del正在被删除" << endl; }
	};
	template <typename D>
	struct deleter :public del_base{
		D f;
		T *p;
		deleter(T *k, D v) :p(k), f(v) {}
		void destory() override {
			cout << "非默认删除器" << endl;
			f(p);
		}
	};
	del_base *del;
public:
	Shared_ptr() :ptr(nullptr), refnum(nullptr), del(nullptr) {}
	explicit Shared_ptr(T *p) :ptr(p), refnum(new int(1)), del(nullptr) {}
	template <typename D> Shared_ptr(T *p, D Del);
	explicit Shared_ptr(std::shared_ptr<T> p) {
		if (p.unique())
			*this = Shared_ptr(new T(*p));
	}
	template <typename D> Shared_ptr(std::shared_ptr<T> p,D del) {
		if (p.unique())
			*this = Shared_ptr(new T(*p),del);
	}
	Shared_ptr(const Shared_ptr &);
	Shared_ptr(Shared_ptr &&);
	Shared_ptr& operator=(const Shared_ptr &);
	Shared_ptr& operator=(Shared_ptr &&);
	void reset();
	T& operator*() const;
	T* operator->() const {
		//将实际工作委托给解引用运算符
		return &this->operator*();
	}
	~Shared_ptr();
};


template<typename T>
inline Shared_ptr<T>::Shared_ptr(const Shared_ptr &m) :ptr(m.ptr), refunm(m.refnum)
{
	*refnum++;
}

template<typename T>
inline Shared_ptr<T>::Shared_ptr(Shared_ptr &&m) :ptr(m.ptr), refnum(m.refnum)
{
	m.ptr = m.refnum = nullptr;
}

template<typename T>
inline Shared_ptr<T> & Shared_ptr<T>::operator=(const Shared_ptr &m)
{
	//被拷贝的Shared_ptr引用计数增加1，等式另外一边的Shared_ptr引用计数减1，若减1后引用计数为0，则delete ptr.
	++*m.refnum;
	if (refnum&&!--*refnum) {
		del ? del->destory(): delete ptr;
		delete refnum;
		delete del;
	}
	ptr = m.ptr;
	refnum = m.refnum;
	return *this;
}

template<typename T>
inline Shared_ptr<T> & Shared_ptr<T>::operator=(Shared_ptr &&m)
{
	if (refnum && !--(*refnum)) {
		del ? del->destory() : delete ptr;
		delete refnum;
		delete del;
	}
	ptr = m.ptr;
	refnum = m.refnum;
	del = m.del;
	m.del = nullptr;
	m.ptr = nullptr;
	m.refnum = nullptr;
	return *this;
}

template<typename T>
inline void Shared_ptr<T>::reset()
{
	del ? del->destory() : delete ptr;
	delete refnum;
	delete del;
}

template<typename T>
inline Shared_ptr<T>::~Shared_ptr()
{
	if (refnum&&!--*refnum) {
		cout << "class Shared_ptr is deleting..." << endl;
		del ? del->destory() : delete ptr;
		delete refnum;
		delete del;
	}
}

template<typename T>
inline T & Shared_ptr<T>::operator*() const
{
	check("ptr is nullptr");
	return *ptr;
	// TODO: 在此处插入 return 语句
}

template<typename T>
inline void Shared_ptr<T>::check(const string &msg) const
{
	if (!ptr) {
		throw runtime_error(msg);
	}
}

template<typename T>
template<typename D>
inline Shared_ptr<T>::Shared_ptr(T * p, D Del) :ptr(p), del(new deleter<D>(p,Del)), refnum(new int(1)) {
}
