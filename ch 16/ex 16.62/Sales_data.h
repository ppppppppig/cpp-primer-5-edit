#ifndef SALES_DATA_H
#define SALES_DATA_H
#include "Head.h"
template <typename T> struct std::hash;
class Sales_data
{
	//友元声明
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
	//销售数量与金额
	unsigned units_sold = 0;//类内初始值
	double revenue = 0.0;
	//返回书籍的isbn编号
	//该成员函数为常量成员函数。
	//重载运算符
public:
	string isbn() const { return bookNo; }//使用了额外的隐式参数this（该函数的对象地址，这是一个常量指针）
										  //更新销售数量和金额
	Sales_data &combine(const Sales_data &rng);
	//四个委托构造函数
	Sales_data() : Sales_data("", 0, 0) { /*cout << "用的是0个参数的" << endl;*/ }
	Sales_data(const string &s, const unsigned n, const double p) :bookNo(s), units_sold(n), revenue(p*n) { /*cout << "用的是3个参数的" << endl;*/ }
	//抑制构造函数定义的隐式转换
	/*explicit*/ Sales_data(const string &s) :Sales_data(s, 0, 0) {/* cout << "用的是1个参数的" << endl;*/ }
	/*explicit*/ Sales_data(istream &is) : Sales_data() { read(is, *this);/* cout << "用的是输入流" << endl;*/ }
	//重载运算符
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
