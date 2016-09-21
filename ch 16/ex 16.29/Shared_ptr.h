#pragma once
//����ֻʵ���˲��ֹ���
template <typename T>
class Shared_ptr {
	//���ü�������̬�ڴ��е�int��
	//delete����һ���������һ����ΪDel�Ŀɵ��ö�����Ϊֻ��������ʱ�Ż�󶨣���������֪��Ӧ�ý��ɵ��ö���������ʲô���ͣ�
	//�ɴ��뵽ģ�壬��ʼ��ʱ����Ĭ��ʵ����nullptr��
	//��Ա����ʹ��ǰ�ж�Del�����Ƿ�Ϊnull���Ӷ��ж�ʹ����һ��ɾ������
	void check(const string &) const;
	T *ptr;
	int *refnum;
	struct del_base {
		virtual void destory() = 0;
		virtual ~del_base() { cout << "del���ڱ�ɾ��" << endl; }
	};
	template <typename D>
	struct deleter :public del_base{
		D f;
		T *p;
		deleter(T *k, D v) :p(k), f(v) {}
		void destory() override {
			cout << "��Ĭ��ɾ����" << endl;
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
		//��ʵ�ʹ���ί�и������������
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
	//��������Shared_ptr���ü�������1����ʽ����һ�ߵ�Shared_ptr���ü�����1������1�����ü���Ϊ0����delete ptr.
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
	// TODO: �ڴ˴����� return ���
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
