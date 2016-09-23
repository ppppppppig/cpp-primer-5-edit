#ifndef SALES_DATA_H
#define SALES_DATA_H
#include "Head.h"
template <typename T> struct std::hash;
class Sales_data
{
	//��Ԫ����
	friend struct std::hash<Sales_data>;
	friend istream &read(istream &is, Sales_data &item);
	friend ostream &print(ostream &os, const Sales_data &data);
	friend Sales_data add(Sales_data lhs, Sales_data rhs);
	friend ostream &operator<<(ostream &, const Sales_data&);
	friend istream &operator>>(istream &is, Sales_data &m);
	friend Sales_data operator+(const Sales_data &m1, const Sales_data&);
	friend bool operator==(const Sales_data &m1, const Sales_data &m2);
private:
	string bookNo;
	//������������
	unsigned units_sold = 0;//���ڳ�ʼֵ
	double revenue = 0.0;
	//�����鼮��isbn���
	//�ó�Ա����Ϊ������Ա������
	//���������
public:
	string isbn() const { return bookNo; }//ʹ���˶������ʽ����this���ú����Ķ����ַ������һ������ָ�룩
										  //�������������ͽ��
	Sales_data &combine(const Sales_data &rng);
	//�ĸ�ί�й��캯��
	Sales_data() : Sales_data("", 0, 0) { /*cout << "�õ���0��������" << endl;*/ }
	Sales_data(const string &s, const unsigned n, const double p) :bookNo(s), units_sold(n), revenue(p*n) { /*cout << "�õ���3��������" << endl;*/ }
	//���ƹ��캯���������ʽת��
	/*explicit*/ Sales_data(const string &s) :Sales_data(s, 0, 0) {/* cout << "�õ���1��������" << endl;*/ }
	/*explicit*/ Sales_data(istream &is) : Sales_data() { read(is, *this);/* cout << "�õ���������" << endl;*/ }
	//���������
	Sales_data &operator+=(const Sales_data &);
	Sales_data& operator=(const string &);
	explicit operator string()const;
	explicit operator double() const;
};
inline Sales_data &Sales_data::combine(const Sales_data &rng)
{
	units_sold += rng.units_sold;
	revenue += rng.revenue;
	return *this;
}
istream &read(istream &is, Sales_data &item);
ostream &print(ostream &os, const Sales_data &data);
Sales_data add(Sales_data lhs, Sales_data rhs);
inline bool operator==(const Sales_data &m1, const Sales_data &m2) {
	return m1.bookNo == m2.bookNo;
}
#endif
