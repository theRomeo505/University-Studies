// 17.09.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <conio.h>
#include <iostream>
using namespace std;
//Case10.Робот может перемещаться в четырех направлениях(«С» — север,

	//«З» — запад, «Ю» — юг, «В» — восток) и принимать три цифровые ко -
	//манды: 0 — продолжать движение, 1 — поворот налево, –1 — поворот на -
	//право.Дан символ C — исходное направление робота и целое число N —

	//посланная ему команда.Вывести направление робота после выполнения
	//полученной команды.
void switch10(char a, int b) {
	int c;
	switch (a)
	{
	case 'Ю': c = 1; break;
	case 'З': c = 2; break;
	case 'В': c = 4; break;
	case 'С': c = 3; break;

	}
	switch (b)
	{
	//case 1: c--; break; case -1:c++; break;
	}
	switch (c) {
	case '1': cout<<'Ю'; break;
	case '2': cout<<"З"; break;
	case '4': cout<<"В"; break;
	case '3': cout<<"С"; break;
	}
}
//For40.Даны целые числа A и B(A < B).Вывести все целые числа от A до B
	//включительно; при этом число A должно выводиться 1 раз, число A + 1
	//должно выводиться 2 раза и т.д.
void for40(int a, int b)
{
	for (int i = a; i <= b; i++)
	{
		for (int j = a; j <= i; j++)
		{
			cout << i << ' ';
		}
	}
}
//While30.Даны положительные числа A, B, C.На прямоугольнике размера A × B
//размещено максимально возможное количество квадратов со стороной C

//(без наложений).Найти количество квадратов, размещенных на прямо -
//угольнике.Операции умножения и деления не использовать.
void while30(int a, int b, int c)
{
	int k = 0, k0 = 0, sum = 0;
	do
	{
		a -= c;
		k++;
	} while (a >= c);
	do
	{
		b -= c;
		k0++;
	} while (b >= c);
	for (int i = 0; i < k; i++)
		sum += k0;
	cout << sum;
}
int main() {
	setlocale(LC_ALL, "Russian");
	int a, b, c;
	int key = 0;
	int code;
	while (true) {
		do {
			system("cls");
			key = (key + 3) % 3;
			if (key == 0) cout << "-> switch10" << endl;
			else  cout << "   switch10" << endl;
			if (key == 1) cout << "-> for40" << endl;
			else  cout << "   for40" << endl;
			if (key == 2) cout << "-> while30" << endl;
			else  cout << "   while30" << endl;

			code = _getch();
			if (code == 224)
			{
				code = _getch();
				if (code == 80) key++;
				if (code == 72) key--;
			}
		} while (code != 13);
		system("cls");
		if (key == 0) { cin >> a >> b; switch10(a, b); }
		if (key == 1) { cin >> a >> b; for40(a, b); }
		if (key == 2) { cin >> a >> b>>c; while30(a, b,c); }
		system("pause");
	}
	return key;
}

