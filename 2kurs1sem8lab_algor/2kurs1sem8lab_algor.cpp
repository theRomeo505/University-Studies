// 2kurs1sem8lab_algor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

#define d 10
#define MAX 10000
#define num_of_chars 256
using namespace std;

int sum = 0;
int control = 0;
int* shift(string p) {
	int i, j, m;
	int* t = new int[MAX];
	m = p.length();

	for (i = 0; i < MAX; i++)
		t[i] = m;

	for (j = 0; j < m - 1; j++)
		t[p[j]] = m - 1 - j;
	return t;
}
int max(int a, int b) { return (a > b) ? a : b; }
void preprocess_suffix(int* shift, int* bpos, string pat)
{
	int m = pat.size();
	int i = m, j = m + 1;
	bpos[i] = j;

	while (i > 0)
	{
		
		while (j <= m && pat[i - 1] != pat[j - 1])
		{
			if (shift[j] == 0)
				shift[j] = j - i;

			j = bpos[j];
		}
		
		i--; j--;
		bpos[i] = j;
	}
}

void preprocess_2(int* shift, int* bpos, string pat)
{
	int m = pat.length();
	int i, j;
	j = bpos[0];
	for (i = 0; i <= m; i++)
	{
		
		if (shift[i] == 0)
			shift[i] = j;

	
		if (i == j)
			j = bpos[j];
	}
}

int boyer_moore(string text, string pat)
{
	int s = 0, j;
	int m = pat.length();
	int n = text.length();
	int* bpos = new int[m + 1];
	int* shift = new int[m + 1];

	for (int i = 0; i < m + 1; i++) shift[i] = 0;
	preprocess_suffix(shift, bpos, pat);
	preprocess_2(shift, bpos, pat);
	while (s <= n - m)
	{

		j = m - 1;


		while (j >= 0 && pat[j] == text[s + j])
			j--;


		if (j < 0)
		{
			return s;
		}
		else
			
			s += shift[j + 1];
	}
	return -1;
} 
int naive(string s1, string s2) {
	if (s1.length() < s2.length()) {
		for (int i = 0; i < s2.length() - s1.length() + 1; i++) {
			if (s2[i] == s1[0]) {
				int j = i;
				int m = 0;
				for (int k = 0; k < s1.length(); k++) {



					if (s2[j] != s1[k]) {
						break;
					}
					else m++;
					if (m == s1.length()) return i;
					j++;
				}
			}
		}
	}
	return -1;
}
int horspool(string s1, string s2) {
	int* t = shift(s2);
	int i, j, k, m, n;
	n = s1.length();
	m = s2.length();
	i = m - 1;

	while (i < n) {
		k = 0;
		while ((k < m) && (s2[m - 1 - k] == s1[i - k]))
			k++;
		if (k == m)
			return(i - m + 1);
		else
			i += t[s1[i]];
	}
	delete[] t;
	return -1;
}
int KMP(string S, string pattern)
{
	int begin = 0;
	vector<int> temp(pattern.length());

	temp[0] = 0;
	for (int k = 0, i = 1; i < pattern.length(); ++i)
	{
		while ((k > 0) && (pattern[i] != pattern[k]))
			k = temp[k - 1];

		if (pattern[i] == pattern[k])
			k++;

		temp[i] = k;
	}
	
	for (int k = 0, i = begin; i < S.length(); ++i)
	{
		while ((k > 0) && (pattern[k] != S[i]))
			k = temp[k - 1];

		if (pattern[k] == S[i])
			k++;

		if (k == pattern.length())
			return (i - pattern.length() + 1);
	}

	return -1;
}
int RabinKarp(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();
	int q = rand() % 13;
	int i, j;
	int p = 0;
	int t = 0;
	int h = 1;

	for (i = 0; i < m - 1; i++)
		h = (h * d) % q;

	//  hash 
	for (i = 0; i < m; i++) {
		p = (d * p + pattern[i]) % q;
		t = (d * t + text[i]) % q;
	}

	// Find the match
	for (i = 0; i <= n - m; i++) {
		if (p == t) {
			for (j = 0; j < m; j++) {
				if (text[i + j] != pattern[j])
					break;
			}

			if (j == m)
				return i;
		}

		if (i < n - m) {
			t = (d * (t - text[i] * h) + text[i + m]) % q;

			if (t < 0)
				t = (t + q);
		}
	}
	return -1;
}
int main()
{
	string s1="";
	string s2;
	for (int i = 0; i < 200000; i++)
	{
		int k = rand() % 63 + 63;
		s1.insert(s1.end(), k);
	}
	s2 = s1;
	for (int i = 0; i < 500000; i++)
	{
		int k = rand() % 63 + 63;
		s2.insert(s2.begin(), k);
	}
	for (int i = 0; i < rand()%3000; i++)
	{
		s2.insert(s2.end(), s2[0]);
		s2.erase(s2.begin());
	}
	auto t_start = std::chrono::high_resolution_clock::now();
	cout << "Naive: " << naive(s1, s2) << " - ";
	auto t_end = std::chrono::high_resolution_clock::now();
	cout << "time" << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000<<endl;

	t_start = std::chrono::high_resolution_clock::now();
	cout << "boyer moore: " << boyer_moore(s2, s1) << " - ";
	t_end = std::chrono::high_resolution_clock::now();
	cout << "time" << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << endl;

	t_start = std::chrono::high_resolution_clock::now();
	cout << "horspool: " << horspool(s2, s1) << " - ";
	t_end = std::chrono::high_resolution_clock::now();
	cout << "time" << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << endl;

	t_start = std::chrono::high_resolution_clock::now();
	cout << "Rabin Karp: " << RabinKarp(s2, s1) << " - ";
	t_end = std::chrono::high_resolution_clock::now();
	cout << "time" << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << endl;

	t_start = std::chrono::high_resolution_clock::now();
	cout << "KMP: " << KMP(s2, s1) << " - ";
	t_end = std::chrono::high_resolution_clock::now();
	cout << "time" << std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000 << endl;
}
