#include <iostream>
#include "Shared_ptr.h"
#include "Sales_data.h"
#include <string>
using std::cout;
using std::endl;
namespace std {
	template<>
	struct hash<Sales_data> {//hashģ���һ����������
		typedef size_t result_type;
		using arguement_type = Sales_data;//����Ҫ��������������
		size_t operator()(const Sales_data&) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data &s) const {
		return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}
int main() {
	std::unordered_multiset<Sales_data> se;
	Sales_data a("�ŷ��ݵ���", 2, 30.00), b("һ������ŷ�ĵ����˾���ȥ��", 3, 20.01);
	se.insert(a);
	se.insert(b);
	cout << se.bucket_count() << endl;
	for (size_t i = 0; i <= 8; ++i)
		cout << se.bucket_size(i) << endl;
	for (const auto &val : se)
		cout << val << endl;
	return 0;
} 