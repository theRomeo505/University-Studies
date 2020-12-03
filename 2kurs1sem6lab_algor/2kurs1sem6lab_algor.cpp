// 2kurs1sem6lab_algor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> z(string str)
{
	int n = str.size();
	vector<int> answer(n, 0);
	int l, r;
	l = 0;
	r = 1;
	for (int i = 1; i < n; ++i)
	{
		if (i < r)
		{
			answer[i] = min(r - i, answer[i - l]);
		}
		while ((i + answer[i] < n) && (str[answer[i]] == str[i + answer[i]]))
		{

			++answer[i];
		}
		if (i + answer[i] > r)
		{
			l = i;
			r = i + answer[i];
		}
	}
	return answer;
}

int search(string& pattern, string& text)
{
	// abcd \\ cdabcdab
	
	vector<int> zf = z(pattern + "#" + text);
	int ps = pattern.size();
	int ts = text.size();
	
	for (int i = 0; i + ps - 1 < text.size(); ++i) // i+ 3
	{
		if (zf[i + ps + 1] == ps) // i+5
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	// abcd \\\ dcba
	string str1 = "", str2 = "", str; int l = 0;
	for (int i = 0; i < 100; i++) {
		int k = rand() % 63+63;
		str1.insert(str1.end(), k);
		str2 = str1;
		for (int j = 0; j < rand() % 10; j++) {
			str2.insert(str2.end(), str2[0]);
			str2.erase(str2.begin());
		}
		//cout << str1<<endl;
		//cout << str2 << endl << endl;
		str = str2 + str2;
		if (search(str1, str) == -1)
			l++;
	}
	cout << l << "of 100 did not pass";
	 return 0;
	//string str(str2 + str2);
	int mas = -1;
	if (str1.length() == str2.length())
		mas = search(str1, str);
	cout << mas << endl;
	return 0;
}