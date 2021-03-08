// 2kurs2sem1lab_oop.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"


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
* Tree class
* \param head Head of the tree
* \param \private temp Temporary variable for usage in recurse functions
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
		head = addnode(head,eng,ru);
	}
	
	/**
	* Find russian translate for an english word
	* \param eng English translate
	* \return Russian translate
	*/
	string find(string eng)
	{
		return finder(head, eng);
	}
	
	/**
	* Changes russian translation to another
	* \param eng English word
	* \param ru New russian translation
	*/
	void changetrans(string eng, string ru) {
		head = change(head, eng, ru);
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
	void del_tree(node* tree) {
		if (tree != NULL) {
			del_tree(tree->left);
			del_tree(tree->right);
			delete tree;
		}
	}
private:
	string temp;
	/*
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
	/*
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
/*
	* find function`s algorythm
	*/
string finder(node* tree, string eng) {
	finder1(tree, eng);
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
/*
	* Changetrans function`s algorythm
	*/
node* change(node* tree, string eng, string ru) {
	if (tree != NULL) {
		if (tree->eng < eng) {
			change(tree->right, eng,ru);
		}
		else if (tree->eng > eng)
		{
			change(tree->left, eng,ru);
		}
		else {
			tree->rus = ru;
			return tree;
		}
	}
}
};



TEST_CASE("Adding") {

}
int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
