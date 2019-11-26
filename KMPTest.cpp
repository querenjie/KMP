#include "KMP.h"
#include <iostream>

int main() {
	KMP kmp("aaabbbaaaabaaab", "aaaab");
	int index = kmp.Index_KMP(1);	//从主串的第一个字符位置开始查找模式串，并返回找到的起始位置。
	cout << "模式串在主串中的位置index = " << index << endl;
	cout << endl;

	return 0;
}