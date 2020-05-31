

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
const int char_sz = 20;
struct node {
	char eng[char_sz];
	char rus[char_sz];
	int calls;
	node* left;
	node* right;
};
node* addnode(node* tree, char eng[]) {
	if (tree == NULL) {
		tree = new node;
		for (int i = 0; i < strlen(eng) + 1; i++) {
			tree->eng[i] = eng[i];
		}
		cout << "enter Russian: ";
		cin.getline(tree->rus, 20);
		cout << "enter calls( ONLY NUMBERS): ";
		cin >> tree->calls;
		if (tree->calls < 0) tree->calls = 0;
		cin.ignore();
		tree->left = NULL;
		tree->right = NULL;
	}
	else if (int(eng[0]) < int(tree->eng[0]))
		tree->left = addnode(tree->left, eng);
	else tree->right = addnode(tree->right, eng);
	return tree;
}
void array_fuller(node* tree, int* arr, int i) {
	if (tree != NULL) {
		arr[i] = tree->calls;
		if (tree->left != NULL) {
			i++;
			/*arr = */array_fuller(tree->left, arr, i);
		} if (tree->right != NULL) {
			i++;
			/*arr = */array_fuller(tree->right, arr, i);
		}
	}
}

void finder(node* tree3, node* tree, int obr) {
	if (tree != NULL) {
		if (obr == tree->calls) {
			for (int j = 0; j < strlen(tree->eng) + 1; j++) {
				tree3->eng[j] = tree->eng[j];
			}
			for (int k = 0; k < strlen(tree->rus) + 1; k++) {
				tree3->rus[k] = tree->rus[k];
			}
			tree3->calls = obr;
			tree3 = tree;
		}
		finder(tree3, tree->left, obr);
		finder(tree3, tree->right, obr);
	}
}
node* swap(node* tree, node* tree2, int obr) {
	if (tree != NULL) {
		if (tree2 == NULL) {
			tree2 = new node;
			tree2->calls = obr;
			tree2->left = NULL;
			tree2->right = NULL;
			for (int j = 0; j < strlen(tree->eng) + 1; j++) {
				tree2->eng[j] = tree->eng[j];
			}
			for (int k = 0; k < strlen(tree->rus) + 1; k++) {
				tree2->rus[k] = tree->rus[k];
			}
			return tree2;
		}
		else if (obr < tree2->calls) {
			tree2->left = swap(tree, tree2->left, obr);
		}
		else {
			tree2->right = swap(tree, tree2->right, obr);
		}
	}
	return tree2;
}
node* createempttree(node* tree) {
	if (tree == NULL) {
		tree = new node;
		cout << "enter English: ";
		cin.getline(tree->eng, 20);
		cout << "enter Russian: ";
		cin.getline(tree->rus, 20);
		cout << "enter OBR( ONLY NUMBERS): ";
		cin >> tree->calls;
		if (tree->calls < 0) tree->calls = 0;
		cin.ignore();
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
}
void* view_tree(node* tree) {
	if (tree != NULL) {
		cout << "English: " << tree->eng << endl;
		cout << "Russian: " << tree->rus << endl;
		cout << "Calls: " << tree->calls << endl;
		view_tree(tree->left);
		view_tree(tree->right);
	}
	return tree;
}
void del_tree(node* tree) {
	if (tree != NULL) {
		del_tree(tree->left);
		del_tree(tree->right);
		delete tree;
	}
}
int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0) cout << "-> Add node" << endl;
		else  cout << "   Add node" << endl;
		if (key == 1) cout << "-> View tree (first)" << endl;
		else  cout << "   View tree (first)" << endl;
		if (key == 2) cout << "-> Start program" << endl;
		else  cout << "   Start program" << endl;
		if (key == 3) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	node* tree2 = NULL;
	node* tree3 = NULL;
	tree3 = new node;
	const int arr_size = 50;
	int arr[arr_size];
	int alph[arr_size];
	char english[char_sz];
	int find;
	int obr = 0;
	node* tree = NULL;
	for (;;) {
		system("pause");
		int answer = menu();

		switch (answer)
		{
		case 0: if (tree == NULL) {
			tree = createempttree(tree);
			obr = 1;
		}
				else {
			cout << "Enter english word: " << endl;
			cin.getline(english, 20);
			tree = addnode(tree, english);
		}
				break;
		case 1: view_tree(tree); break;
		case 2: {
			del_tree(tree2);
			tree2 = new node;
			node* tree2 = NULL;
			array_fuller(tree, arr, 0);
			for (int i = 0; i < 50; i++) {
				if (arr[i] < 0) {
					find = i - 1; break;
				}
			}
			for (int i = 0; i <= find; i++) {
				/*tree3 =*/ finder(tree3, tree, arr[i]);
				tree2 = swap(tree3, tree2, arr[i]);
			}
			cout << "First Tree: \n";
			view_tree(tree);
			cout << "second tree: \n";
			view_tree(tree2);
			break; }
		case 3: del_tree(tree);
			del_tree(tree3);
			del_tree(tree2);
			exit(0); break;
		}
	}
	
	return 0;
}