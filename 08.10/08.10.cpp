// 08.10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;
//Matrix10.Дана матрица размера M × N.Вывести ее элементы, расположенные в
//столбцах с нечетными номерами(1, 3, ...).Вывод элементов производить
//по столбцам, условный оператор не использовать.
int m, n;
void mt10(int **b) {
	for (int i = 0; i < m; i += 2)
	{
		for (int j = 0; j < n; j++) {
			cout << b[i][j] << ' ';
		}
		cout << endl;
	}
}
//Matrix15.Дана квадратная матрица A порядка M(M — нечетное число).Начи -
//ная с элемента A1, 1 и перемещаясь по часовой стрелке, вывести все ее эле -
//менты по спирали : первая строка, последний столбец, последняя строка в

//обратном порядке, первый столбец в обратном порядке, оставшиеся эле -
//менты второй строки и т.д.; последним выводится центральный элемент

//матрицы.
void mt15(int** b) {
	int g;
	
	for (int i = 0; i < ceil(m / 2); i++) {
		for (int j = i; j < m-i; j++)
			cout << b[i][j] << ' ';
		for (int j=i+1;j<m-i;j++)
			cout << b[i][j] << ' ';
		for (int j=m-i-1;j>i;j--)
			cout << b[i][j] << ' ';
		for (int j=m-i-1;j>i+1;j--)
			cout << b[i][j] << ' ';
	}
}
//Matrix20.Дана матрица размера M × N.Для каждого столбца матрицы найти
//произведение его элементов.
void mt20(int** b) {
	int h;
	for (int i = 0; i < m; i++) {
		h = 1;
		for (int j = 0; j < n; j++) {
			h *= b[i][j];
		}
		cout << h<<' ';
	}
}
//Matrix30.Дана матрица размера M × N.В каждом ее столбце найти количество
//элементов, больших среднего арифметического всех элементов этого
///столбца.
void mt30(int** b) {
	double h;
	for (int i = 0; i < m; i++) {
		h = 0;
		for (int j = 0; j < n; j++) {
			h += b[i][j];
		}
		h /= n;
		for (int j = 0; j < n; j++) {
			if (b[i][j] > h)
				cout << b[i][j]<< ' ' ;
		}
		cout << endl;
	}
}
//Matrix50.Дана матрица размера M × N.Преобразовать матрицу, поменяв мес -
//тами минимальный и максимальный элемент в каждом столбце.
void mt50(int** b) {
	int mx,mn,l;
	for (int i = 0; i < m; i++) {
		mx = b[i][0]; mn = b[i][0];
		for (int j = 0; j < n; j++) {
			if (b[i][j] > b[i][mx])
				mx = j;
			if (b[i][j] < b[i][mn])
				mn = j;
		}
		l = b[i][mn];
		b[i][mn] = b[i][mx];
		b[i][mx] = l;
	}
}
//Matrix61.Дана матрица размера M × N и целое число K(1 ≤ K ≤ M).Удалить
//строку матрицы с номером K.
int** mt61(int** b,int k) {
	for (int i = k; i < m - 1; i++)
	{
		for (int j = 0; j < n; j++) {
			b[i][j] = b[i + 1][j];
		}
	}
	return b;
}
int main()
{
	int key = 0,y;
	int code;
	while (true) {
		do {
			system("cls");
			key = (key + 6) % 6;
			if (key == 0) cout << "-> mt10" << endl;
			else  cout << "   mt10" << endl;
			if (key == 1) cout << "-> mt15" << endl;
			else  cout << "   mt15" << endl;
			if (key == 2) cout << "-> mt20" << endl;
			else  cout << "   mt20" << endl;
			if (key == 3) cout << "-> mt30" << endl;
			else  cout << "   mt30" << endl;
			if (key == 4) cout << "-> mt50" << endl;
			else  cout << "   mt50" << endl;
			if (key == 5) cout << "-> mt61" << endl;
			else  cout << "   mt61" << endl;
			code = _getch();
			if (code == 224)
			{
				code = _getch();
				if (code == 80) key++;
				if (code == 72) key--;
			}
		} while (code != 13);
		system("cls");
		if (key == 0) {
			cin >> m >> n;
			int** b = new int* [m];
			for (int i=0;i<m;i++)
				b[i] = new int[n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> b[i][j];
				}
			}
			mt10(b);
		}
		if (key == 1) {
			cin >> m;
			int** b = new int* [m];
			for (int i = 0; i < m; i++)
				b[i] = new int[m];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> b[i][j];
				}
			}
			mt15(b);
		}
		if (key == 2) {
			cin >> m >> n;
			int** b = new int* [m];
			for (int i = 0; i < m; i++)
				b[i] = new int[n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> b[i][j];
				}
			}
			mt20(b);
		}
		if (key == 3) {
			cin >> m >> n;
			int** b = new int* [m];
			for (int i = 0; i < m; i++)
				b[i] = new int[n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> b[i][j];
				}
			}
			mt30(b);
		}
		if (key == 4) {
			cin >> m >> n;
			int** b = new int* [m];
			for (int i = 0; i < m; i++)
				b[i] = new int[n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> b[i][j];
				}
			}
			mt50(b);
		}
		if (key == 5) {
			cin >> m >> n>>y;
			int** b = new int* [m];
			for (int i = 0; i < m; i++)
				b[i] = new int[n];
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					cin >> b[i][j];
				}
			}
			mt61(b,y);
		}
		system("pause");
	}
	return key;
}

