#include "Sales_data.h"
ostream &print(ostream &os, const Sales_data &data)
{
	os << data.isbn() << " " << data.units_sold << " " << data.revenue;
	return os;
}
istream &read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price*item.units_sold;
	return is;
}
Sales_data add(Sales_data lhs, Sales_data rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
ostream &operator<<(ostream &os, const Sales_data &data)
{
	os << data.isbn() << " " << data.units_sold << " " << data.revenue;
	return os;
}
istream &operator>>(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	if (is)
		item.revenue = price*item.units_sold;
	else
		item = Sales_data();//显示调用Sales_data的默认构造函数
	return is;
}
Sales_data operator+(const Sales_data &m1, const Sales_data &m2)
{
	Sales_data k(m1);
	k += m2;
	return k;
}
Sales_data &Sales_data::operator+=(const Sales_data &m)
{
	units_sold += m.units_sold;
	revenue += m.revenue;
	return *this;
}
Sales_data& Sales_data::operator=(const string &s)
{
	bookNo = s;
	return *this;
}
Sales_data::operator string()const
{
	return isbn();
}
Sales_data::operator double() const
{
	return units_sold;
}