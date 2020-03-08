// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

struct pol {
	int isnum;
	int nnum;
	pol* left;
	pol* right;
};
int prior(char s) {
	int lp = 0;
	//cout << "bat ebal";
	if (s== '+' || s == '-')
		lp = 1;
	else if (s == '*' || s == '/' || s == '%')
		lp = 2;
	else if (s == '^')
		lp = 3;
	return lp;
}
vector <pol> cr (string s)
{
	vector <pol> m; int lp; int k = 0; pol p;
	for (int i = 0; i < s.size(); i++) {
		lp = prior(s[i]);
		k = 0;
		if (lp == 0) {
			while (isdigit(s[i]) && s[i]>=0) {
				k *= 10;
				k += s[i] - 48;
				i++;
			}
			p.isnum = 0;
			p.nnum = k;
			m.push_back(p); i--;
		}
		else {
		//	cout << "mat ebal";
			p.isnum = lp;
			if (s[i] == '+')
				p.nnum = 1;if (s[i] == '-')
				p.nnum = 2;if (s[i] == '%')
				p.nnum = 3;if (s[i] == '*')
				p.nnum = 4;if (s[i] == '/')
				p.nnum = 5;if (s[i] == '^')
				p.nnum = 6;
			m.push_back(p);
		}
	}
	for (int i = 0; i < m.size(); i++) {
		cout << m[i].isnum << ' ' << m[i].nnum << endl;
	}
	return m;
}/*
pol createP(string s,int f,int l) {
	
	pol *p=new pol;// koef bukva step bukva step
	
	int k = 0,lp=0;
	
	if (f == l) {
		p->isnum = lp;
		if (!lp) {
			p->nnum = k;
		}
		p->left = NULL;
		p->right = NULL;
	}
	int min = 60, prt; k = 0;
	for (int i = f; i < l; i++) {
		prt = prior(s[i]);
		if (prt < min) {
			min = prt;
			k = i;
		}
	}
	p.
	return *p;
}
*/
int main()
{
	string s;
	cin >> s;
	int y;
	for (int i = 0; i < s.size(); i++) {
		if (isalpha(s[i])) {
			cout << "cin" << s[i] << endl;
			cin >> y;
//			bukv[s[i] - 'a']=y;
			for (int j = i; j < s.size(); j++) {
				if (s[j] == s[i]) {
					double f = y;
					while (f > 10) {
						f /= 10;
						//cout << f << endl;
					}
					s[j] = (int)f +48;
					f = f - (int)f;
					//cout << endl;
					f *= 10;
					while (f != 0) {
						
						//system("Pause");
						s.insert(s.begin() + j + 1, (int)f + 48); //cout << f << endl;
						if ((int)(f*10)%10==0) {
							f = 0;
						}
						else {
							f = f - (int)f; 
							f *= 10;
						}
						//cout << f << endl;
					}
				}
			}
		}
	}
	cout << s<<endl;
	vector <pol> p = cr(s);
}
