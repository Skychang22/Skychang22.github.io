//加密 
#include <iostream>
#include<windows.h>
using namespace std;


char KEY1[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
char PWD1[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
string str1 = "gdufe40";


void Encryption11(int n)
{
	int index;
	for (int i = 0; i < n; i++)
	{
		index = (int)str1[i];
		if (str1[i] >= 'a' && str1[i] <= 'z')
		{
			index -= (int)'a';
			index += 3;
			if (index >= 26)
				index -= 26;
			str1[i] = PWD1[index];
		}
		else if (str1[i] >= 'A' && str1[i] <= 'Z')
		{
			index -= (int)'A';
			index -= 2;
			if (index < 0)
				index += 26;
			str1[i] = KEY1[index];
		}
	}
	cout << "加密成功" << endl;
	printf("%s", str1);
	system("pause");
	cout << str1 << endl;
}

void main22()
{
	Encryption11(7);
}