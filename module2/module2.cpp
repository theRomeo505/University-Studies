// module2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
struct node {
	int number;
	node* l;
	node* r;
};
node l,r;
void fun1(node *h) {
	if (h==nullptr)
		return;
	if (h->l != nullptr || h->r != nullptr) {
		fun1(h->l);
		fun1(h->r);
	}
	l = *h->l;
	r = *h->r;
	h->l = &r;
	h->r = &l;
}
int maxh = 0;
void height(node* h, int he) {
	if (h == nullptr)
	{	
		if (he - 1 > maxh)
			maxh = he - 1;
		return;
	}
	if (h->l != nullptr || h->r != nullptr) {
		height(h->l,he+1);
		height(h->r,he+1);
	}
}
void add(node* h, int b) {
	
		//1
		if (h == NULL)
		{
			h = new node;
			h->number = b;
			h->l = h->r = NULL;
		}

		//2
		if (b < h->number)
		{
			if (h->l != NULL) add(h->l, b);
			else
			{
				h->l = new node;
				h->l->l = h->l->r = NULL;
				h->l->number = b;
			}

		}

		//3
		if (b > h->number)
		{
			if (h->r != NULL) add(h->r, b);
			else
			{
				h->r = new node;
				h->r->r = h->r->l = NULL;
				h->r->number= b;
			}
		}
	
}
int hei1, hei2;
node* addTrees(node* h, node* h1) {
	if (h == nullptr)
		return;
	if (h->l != nullptr || h->r != nullptr) {
		fun1(h->l);
		fun1(h->r);
	}
	add(h1, h->number);
	return h1;
}
void findH2(node* h, int he,int h2) {
	if (h == nullptr)
	{
		return;
	}
	if (he + 1 == h2) {
		maxh = 0;
		height(h->l->l, 1);
		hei1 = maxh; maxh = 0;
		height(h->l->r, 1); hei2 = maxh; maxh = 0;
		if (hei1 == hei2) {
			h->l->l = addTrees(h->l->l, h->l->r);
			h->l = h->l->l;
		}
		maxh = 0;
		height(h->r->l, 1);
		hei1 = maxh; maxh = 0;
		height(h->r->r, 1); hei2 = maxh; maxh = 0;
		if (hei1 == hei2) {
			h->r->r = addTrees(h->r->r, h->r->l);
			h->r = h->r->r;
		}
	}
	else if (h->l != nullptr || h->r != nullptr) {
		findH2(h->l, he + 1,h2);
		findH2(h->r, he + 1,h2);
	}
}
void fun2(node* h) {
	height(h, 1);
	findH2(h, 1, maxh / 2);
}

void fun4h(bool **m,int length, int pos,int toFind,bool first) {
	if (!first) {
		if (pos == toFind)
			t = true;
		return;
	}
	for (int i = 0; i < length; i++) {
		if (m[pos][i])
			fun4h(m, length, i, toFind,false);
	}
}
bool t = false; ///// true if has cycle
void fun4(bool **m,int length) {
	fun4h(m, length, 0,0,true);

}
////// fun3 
struct node3 {
	char c;
	node3* left;
	node3* right;
};

int prior(char s) {
	int lp = 0;
	if (s == '-' || s == '&')
		lp = 1;
	else if (s == '|')
		lp = 2;
	else
		lp = 60;
	return lp;
}
string simplify(string s) {
	for (int i = 0; i < s.length(); i++) {
		//simplify
		if (s[i] == '0') {
			if (prior(s[i - 1]) < prior(s[i + 1]))
			{
				s.erase(i);
				s.erase(i);
			}
			else{
				if (s[i - 1] == '-')
				{
					s.erase(i - 1);
					s[i - 1] = '1';
				}
				else {
					s.erase(i - 1);
					s.erase(i - 2);
				}
				
			}
			simplify(s);
		}
		if (s[i] == '1') {
			// analog to 0 but where 0 is 1 
		}
	}
	return s;
}

node3* createP(string s, int f, int l) {
	node3 *tree = new node3;
	int min = 60, prt, k = 0;
	if (f == l && isalpha(s[f])) {
		tree->c = s[f];
		tree->left = tree->right = NULL;
		return;
	}
	for (int i = f; i <= l; i++) {
		prt = prior(s[i]);
		if (prt < min) {
			min = prt;
			k = i;
		}
	}
	tree->c = s[k];
	tree->left = createP(s, f, k - 1);
	tree->right = createP(s, k + 1, l);
	return tree;
}
void calc(string s) {
	bool tt = true;
	for (int i = 0; i < s.length(); i++) {
		if (isalpha(s[i]))
		{
			s[i] = 0;
			calc(s);
			s[i] = 1;
			calc(s);
			tt = false;
		}
	}
	if (tt) {
		//s now has only digits 
		int y = stoi(s); // calculates it 
	}
}
void fun3(string s) {
	s = simplify(s);
	node3* n = createP(s, 0, s.length() - 1);

}
using namespace std;
int main()
{
	
}
