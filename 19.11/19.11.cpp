// 19.11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include<windows.h>
#include <conio.h>

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
/*
void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}*/
using namespace std;
int main()
{
	string m;
	ifstream f("dtt.dat");
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | BACKGROUND_RED);
	//SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | BACKGROUND_RED);
	char c=0; int i = 0,j=0;
	//GetConsoleText
	//GetConsole
	//SetConsoleTextAttribute(hConsoleHandle, (0,0,0,60) | (255,255,255,50 ));
	//cout << "lkjhlkj"; system("pause");
	int l = 0;
	while (c!= 13) {
		
		c = _getch();
		system("cls");	
		i = 0; l = 0;
		while (!f.eof()) {
			f >> m;
			if (l == 1)
			{
				cout << m << ' ';
				if (m[m.length() - 1] == 'a' || m[m.length() - 1] == 'e' || m[m.length() - 1] == 'i' || m[m.length() - 1] == 'o' || m[m.length() - 1] == 'y' || m[m.length() - 1] == 'u') {
					i++;
				}
			}
			else {
				if (m[m.length() - 1] == 'a' || m[m.length() - 1] == 'e' || m[m.length() - 1] == 'i' || m[m.length() - 1] == 'o' || m[m.length() - 1] == 'y' || m[m.length() - 1] == 'u') {
					i++;
					//cout << "(" << m << ")";
					if (i == j) {
						//SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | BACKGROUND_RED);
						//j++;
						cout << " (" << m << ") ";
						l = 1;
					}
					else {
						cout << m << ' ';

					}
				}
				else
					cout << m << ' ';
			}
			//SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_INTENSITY | COLOR_BACKGROUND);
		}
		j++;
		cout << i << endl;
		if (i < j)
			j = 1;
		
		//if (f.eof()) j = 1;
		f.seekg(0, ios::beg);

	}
	//SetColor(Blue, Black);
}


