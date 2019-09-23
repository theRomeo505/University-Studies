#include <iostream>
#include <vector>
using namespace std;

//) Задаються n пар чисел, які задають багатокутник.Написати програму
//перевірки його опуклості
void vabka2task1(vector <int> a, vector <int> b) {
	int x, y,x1,y1,x2,y2,x3,y3,A,B,C; 
	x = a.at(a.size() - 1); a.pop_back();
	y = b.at(b.size() - 1); b.pop_back();
	x1 = a.at(a.size() - 1); a.pop_back();
	y1 = b.at(b.size() - 1); b.pop_back();
	x2 = a.at(a.size() - 1); a.pop_back();
	y2 = b.at(b.size() - 1); b.pop_back();
	x3 = a.at(a.size() - 1); a.pop_back();
	y3 = b.at(b.size() - 1); b.pop_back();
	for (int i = 0; i < a.size() - 3; i++) {
		A = y1 - y2;
		B = x2 - x1;
		C = y1 * (x1 - x2) - x1 * (y1 - y2);
		if ((x * A + y * B + C) * (x3 * A + y * B + C) < 0) {
			cout << "Not a convex";
			return ;
		}
		cout << "Convex";
		x = x1; y = y1; x1 = x2; y2 = y3; y1 = y2; x2 = x3;
		x3 = a.at(a.size() - 1); a.pop_back();
		y3 = b.at(b.size() - 1); b.pop_back();
	}
	// compare first with last
}
int main()
{

}