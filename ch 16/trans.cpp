#include "Head.h"
void transfors(string &s, string &oldVal, string &newVal)
{//���ַ����е�oldVal���ַ���ת����newVal�ַ���
	if (oldVal.empty()) return;
	typedef string::size_type st;
	st len = oldVal.size();
	for (st ix = 0; ix < s.size(); ++ix)
	{
		if (s[ix] == oldVal[0])
		{
			bool flag = false;
			st indexs = ix + 1;
			st indexo = 1;
			while (indexo < oldVal.size() && indexs < s.size())
			{
				if (s[indexs++] != oldVal[indexo++])
				{
					flag = true;
					break;
				}
			}
			if (!flag&&indexs < s.size()||indexs==s.size()&&indexo==oldVal.size())
			{
				s.replace(ix, len, newVal);
			}
		}
	}
}
string add(string &s, string &s1, string &s2)
{
	//�����ֵ�ǰ׺s1�ͺ�׺s2���뵽s�ϡ�
	s.insert(s.size(), s2);
	s.insert(0, s1);
	return s;
}