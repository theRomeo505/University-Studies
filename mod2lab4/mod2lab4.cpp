

#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

struct word {
	string angl;
	string ukr;
	int count;
	word* l;
	word* r;
};
typedef word* node;

node cr(vector <word> list, int f, int l) {
	node dic=new node;
	if (f == l) {
		dic->angl = list[f].angl;
		dic->ukr = list[f].ukr;
		dic->count = list[f].count;
		dic->l = NULL;
		dic->r = NULL;
		return dic;
	}
	dic->l = cr(list, f, f + (l - f) / 2 - 1);
	dic->r = cr(list, f + (l - f) / 2 + 1, l);

}
int main()
{
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 4) % 4;
		if (key == 0) std::cout << "-> Enter" << std::endl;
		else  std::cout << "   Enter" << std::endl;
		if (key == 1) std::cout << "-> Show" << std::endl;
		else  std::cout << "   Show" << std::endl;if (key == 2) std::cout << "-> Redo" << std::endl;
		else  std::cout << "   Redo" << std::endl;if (key == 3) std::cout << "-> Show2" << std::endl;
		else  std::cout << "   Show2" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
}
