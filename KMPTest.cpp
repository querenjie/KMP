#include "KMP.h"
#include <iostream>

int main() {
	KMP kmp("aaabbbaaaabaaab", "aaaab");
	int index = kmp.Index_KMP(1);	//�������ĵ�һ���ַ�λ�ÿ�ʼ����ģʽ�����������ҵ�����ʼλ�á�
	cout << "ģʽ���������е�λ��index = " << index << endl;
	cout << endl;

	return 0;
}