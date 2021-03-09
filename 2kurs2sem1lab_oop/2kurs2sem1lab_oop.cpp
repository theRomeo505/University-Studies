// 2kurs2sem1lab_oop.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"


#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <gtest/gtest.h>
using namespace std;
/**
* Node class to be used as node in our list
* \param eng English translation
* \param rus Russian translation
* \param left Left tree node
* \param right Right tree node
*/
struct node {
	string eng;
	string rus;
	node* left;
	node* right;
};
/**
* Checks if string is a word
*
*/
bool check(string s) {
	for (int i = 0; i < s.length(); i++)
		if (!isalpha(s[i]))
			return false;
	return true;
}


/** 
* Tree class
*/
class tree {
public:
	node* head;
	tree() {
		head = NULL;
	}
	/**
	* Adds new node
	* \param eng Eng translation
	* \param ru Rus translation
	*/
	void addnod(string eng,string ru) {
		if (!check(eng) || !check(ru))
			return;
		head = addnode(head,eng,ru);
	}
	
	/**
	* Find russian translate for an english word
	* \param eng English translate
	* \return Russian translate
	*/
	string find(string eng)
	{
		if (!check(eng))
			return;
		return finder(head, eng);
	}
	
	/**
	* Changes russian translation to another
	* \param eng English word
	* \param ru New russian translation
	*/
	void changetrans(string eng, string ru) {
		if (!check(eng) || !check(ru))
			return;
		 change(head, eng, ru);
	}
	
	/**
	* Prints full tree Left-Middle-Right
	*/
	void view() {
		view_tree(head);
	}
	/**
	* Cleares all the memmory
	*/
	void clear() {
		del_tree(head);
	}
	
private:
	string temp;
	/**
	* View function`s algorythm
	*/
	void  view_tree(node* tree) {
		if (tree != NULL) {
			cout << "English: " << tree->eng << endl;
			cout << "Russian: " << tree->rus << endl;
			//cout <<((tree->left==NULL)? tree->left->eng:"") << ((tree->right==NULL)?tree->right->eng:"") << endl;
			view_tree(tree->left);
			view_tree(tree->right);
		}

	}
	/**
	* addnod function`s algorythm
	*/
node* addnode(node* tree, string eng, string ru) {
	if (tree == NULL) {
		tree = new node;
		tree->eng = eng;
		tree->rus = ru;

		//tree->calls = count;


		tree->left = NULL;
		tree->right = NULL;
	}
	else if (eng < tree->eng)
	{
		tree->left = addnode(tree->left, eng, ru);
		//cout << "left";
	}
	else {
		tree->right = addnode(tree->right, eng, ru);
		//cout << "right";
	}
		return tree;
	}
/**
	* find function`s algorythm
	*/
string finder(node* tree, string eng) {
	string t = temp;
	finder1(tree, eng);
	if (t == temp)
		return "not found";
	return temp;
}
void finder1(node* tree,string eng) {
	if (tree != NULL) {
		//cout << tree->eng;

		if (tree->eng < eng) {
			//cout << "r";
			finder1(tree->right, eng);
		}
		else if (tree->eng > eng)
		{
			//cout << 'l';
			finder1(tree->left, eng);
		}
		else if (tree->eng == eng) {
			temp = tree->rus;
			return;
		}
	}
	}
/**
	* Changetrans function`s algorythm
	*/
void change(node* tree, string eng, string ru) {
	if (tree != NULL) {
		//cout << tree->eng << endl;
		if (tree->eng < eng) {
			change(tree->right, eng,ru);
		}
		else if (tree->eng > eng)
		{
			change(tree->left, eng,ru);
		}
		else {
			tree->rus = ru;
		}
	}
}
/**
* clear func algorythm
*/
void del_tree(node* tree) {
	if (tree != NULL) {
		del_tree(tree->left);
		del_tree(tree->right);
		delete tree;
	}
}
};

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Add" << endl;
		else  cout << "   Add" << endl;
		if (key == 1) cout << "-> Change" << endl;
		else  cout << "   Change" << endl;
		if (key == 2) cout << "-> Translate" << endl;
		else  cout << "   Translate" << endl;
		if (key == 3) cout << "-> Show" << endl;
		else  cout << "   Show" << endl;
		if (key == 4) cout << "-> End" << endl;
		else  cout << "   End" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

int main(int argc, char** argv) {
	doctest::Context ctx;
	ctx.setOption("abort-after", 5);  // default - stop after 5 failed asserts
	ctx.applyCommandLine(argc, argv); // apply command line - argc / argv
	ctx.setOption("no-breaks", true); // override - don't break in the debugger
	int res = ctx.run();              // run test cases unless with --no-run
	if (ctx.shouldExit())              // query flags (and --exit) rely on this
		return res;                   // propagate the result of the tests
	system("PAUSE");
	string str1, str2;
	tree tr;
	while (true) {
		int chose = menu();
	
		switch (chose) {
		case 0:
			cout << "Enter eng";
			cin >> str1;
			cout << "Enter rus";
			cin >> str2;
			tr.addnod(str1, str2);

			break;
		case 1:
			cout << "Enter eng";
			cin >> str1;
			cout << "Enter new rus";
			cin >> str2;
			tr.changetrans(str1, str2);
			break;
		case 2:
			cout << "Enter eng";
			cin >> str1;
			cout<<tr.find(str1);
			break;
		case 3:
			tr.view();
			break;
		case 4:
			tr.clear();
			return 0;
			break;
		}
	}
	

	return res; // + your_program_res
}
TEST_CASE("Adding"){
	tree tr;
	tr.addnod("dog", "sabaka");
	tr.addnod("cat", "koshka");
	tr.addnod("mouse", "mish");
	tr.addnod("parrot", "pepuga");
	CHECK(tr.head->eng == "dog");
	CHECK(tr.head->left->eng == "cat");
	CHECK(tr.head->right->eng == "mouse");
	CHECK(tr.head->right->right->eng == "parrot");
}

TEST_CASE("Find") {
	tree tr;
	tr.addnod("dog", "sabaka");
	tr.addnod("cat", "koshka");
	tr.addnod("mouse", "mish");
	tr.addnod("parrot", "pepuga");

	CHECK(tr.find("dog") == "sabaka");
	CHECK(tr.find("cat") == "koshka");
	CHECK(tr.find("mouse") == "mish");
	CHECK(tr.find("parrot") == "pepuga");

}

TEST_CASE("Find") {
	tree tr;
	tr.addnod("dog", "sabaka");
	tr.addnod("cat", "koshka");
	tr.addnod("mouse", "mish");
	tr.addnod("parrot", "pepuga");
	
	tr.changetrans("dog", "sabaken");
	tr.changetrans("cat", "kashak");
	tr.changetrans("mouse", "mush");
	tr.changetrans("parrot", "papagey");

	CHECK(tr.find("dog") == "sabaken");
	CHECK(tr.find("cat") == "kashak");
	CHECK(tr.find("mouse") == "mush");
	CHECK(tr.find("parrot") == "papagey");

}

