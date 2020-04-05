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
typedef pol *node;
int prior(char s) {
	int lp = 0;
	if (s == '+' || s == '-')
		lp = 1;
	else if (s == '*' || s == '/' || s == '%')
		lp = 2;
	else if (s == '^')
		lp = 3;
	else
		lp = 60;
	return lp;
}

node createP(string s,int f,int l) {
	node tree=new pol;
	
	int k = 0,lp=0;
	for (int i = f; i <= l; i++) {
		if (!isdigit(s[i])) {
			lp = 1;
			break;
		}
		k *= 10;
		k += s[i]-48;
	}
	if (!lp) { /// from f to l number
		tree->isnum = 1;
		tree->nnum = k;
		tree->left = NULL;
		tree->right = NULL;
		
		return tree;
	}
	int min = 60, prt; k = 0;
	for (int i = f; i <= l; i++) {
		prt = prior(s[i]);
		if (prt < min) {
			min = prt;
			k = i;
		}
	}
	tree->isnum = 0;
	tree->nnum = s[k];
	tree->left = createP(s,f,k-1);
	tree->right = createP(s, k + 1, l);
	return tree;
}
int tr(node tree) {
	if (tree->left==NULL) {
		
		return tree->nnum;
	}
	int num1 = tr(tree->left);
	int num2 = tr(tree->right);
	switch ((char)tree->nnum) {
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': return num1 / num2;
	case '^': return pow(num1,num2);

	}
	tr(tree->left);
	tr(tree->right);
}
int main()
{
	string s;
	cin >> s;
	int y;
	for (int i = 0; i < s.size(); i++) {
		if (isalpha(s[i])) {
			cout << "cin" << s[i] << endl;
			cin >> y;
			vector<int> yy;
			while (y > 0) {
				yy.push_back(y % 10);
				y /= 10;
			}
					s[i] = yy[yy.size() - 1]+48;
					yy.pop_back();
					
					while (yy.size()>0) {
						s.insert(s.begin() + i + 1, yy[yy.size()-1]+48); 
						yy.pop_back(); i++;
			
			}
		}
	}
	cout << s<<endl;
	node p = createP(s, 0, s.size() - 1);
	system("Pause");
	
	cout<<tr(p);

}
