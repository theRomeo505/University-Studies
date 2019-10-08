// 30.09.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;
//Array10.Дан целочисленный массив размера N.Вывести вначале все содержа -
//щиеся в данном массиве четные числа в порядке возрастания их индексов,
//а затем — все нечетные числа в порядке убывания их индексов.
int n;
void array10(int *m)
{
	for (int i = 0; i < n; i++) {
		if (m[i] % 2 == 0)
			cout << m[i] << ' ';
	}
	cout << endl;
	for (int i = n-1; i >=0; i--) {
		if (m[i] % 2 == 1)
			cout << m[i] << ' ';
	}
}
//Array20.Дан массив размера N и целые числа K и L(1 ≤ K ≤ L ≤ N).Найти сум -
//му элементов массива с номерами от K до L включительно.
void array20(int *m, int k, int l) {
	int s = 0;
	for (int i = k-1; i <= l-1; i++)
		s += m[i];
	cout << s;
}
//Array30.Дан массив размера N.Найти номера тех элементов массива, которые
//больше своего правого соседа, и количество таких элементов.Найденные
//номера выводить в порядке их возрастания.
void array30(int *m) {
	int s = 0;
	for (int i = 0; i < n-1; i++) {
		if (m[i] > m[i + 1]) {
			s++;
			cout << i << ' ';
		}
	}
	cout << s;
}
//Array40.Дано число R и массив A размера N.Найти элемент массива, который
//наиболее близок к числу R(то есть такой элемент AK, для которого величи -
	//на | AK – R | является минимальной).
void array40(int *m,int r) {
	int min = fabs(m[0] - r), k = 0;;
	for (int i = 1; i < n; i++)
	{
		if (fabs(r - m[i]) < min) {
			min = fabs(r - m[i]);
			k = i;
		}
	}
	cout << k;
}
//Array50.Дан целочисленный массив A размера N, являющийся перестановкой
//(определение перестановки дано в задании Array49).Найти количество ин -
//версий в данной перестановке, то есть таких пар элементов AI и AJ, в кото -
//рых большее число находится слева от меньшего : AI > AJ при I < J.
void array50(int *m) {
	int k=0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j++; j < n) {
			if (m[i] > m[j])
				k++;
		}
	}
	cout << k;
}
//Array60.Дан массив A размера N.Сформировать новый массив B того же раз -
//мера по следующему правилу : элемент BK равен сумме элементов массива
//A с номерами от K до N.
void array60(int* m) {
	int  k = 0;
	int *b = new int[n],s=0;
	for (int i = n - 1; i >= 0; i++)
	{
		s += m[i];
		b[i] = s;
	}
	for (int i = 0; i < n; i++) {
		cout << b[i] << ' ';
	}
}
//Array80.Дан массив размера N.Осуществить сдвиг элементов массива влево на
//одну позицию(при этом AN перейдет в AN–1, AN–1 — в AN–2, ..., A2 — в A1,
//	a исходное значение первого элемента будет потеряно).Последний эле -
	//мент полученного массива положить равным 0.
void array80(int* m) {
	for (int i = 0; i < n-1; i++) {
		m[i] = m[i + 1];
	}
	m[n - 1] = 0;

}
//Array90.Дан массив размера N и целое число K(1 ≤ K ≤ N).Удалить из массива
//элемент с порядковым номером K.
void del(int* m,int k) {
	for (int i = k; i < n - 1; i++) {
		m[i] = m[i + 1];
	}
	m[n - 1] = 0;
}
//Array100.Дан целочисленный массив размера N.Удалить из массива все эле -
//менты, встречающиеся ровно два раза, и вывести размер полученного мас -
//сива и его содержимое.
void array100(int* m) {
	int s,nn=0;//;;;
	for (int i = 0; i < n; i++) {
		s = 0;
		for (int j = 0; j < n; j++) {
			if (m[i] == m[j] && i != j)
				s++;
		}
		if (s == 2) { nn--; }
		else cout << m[i] << ' ';
	}
	

}
//Array110.Дан целочисленный массив размера N.Продублировать в нем все
//четные числа.
void array110(int* m) {
	for (int i = 0; i < n; i++)
	{
		cout << m[i]<<' ';
		if (m[i] % 2 == 0)
			cout << m[i] << ' ';
	}
}
//Array120.Дан целочисленный массив размера N, содержащий по крайней мере
//одну серию, длина которой больше 1. Преобразовать массив, уменьшив
//каждую его серию на один элемент.
void array120(int* m) {
	int  l = n;
	for (int i = 0; i < n - 1; i++) {
		if (m[i] == m[i + 1])
		{
			del(m, i); l--;
		}
	}
	for (int i = 0; i < l; i++) {
		cout << m[i] << ' ';
	}
}
//Array130.Дан целочисленный массив размера N.Преобразовать массив, увели -
//чив все его серии наибольшей длины на один элемент.
void array130(int* m) {
	int k=0;
	for (int i = 0; i < n; i++) {
		cout << m[i];
		if (m[i] == m[i + 1] && k != 1)
		{
			cout << m[i]; k = 1;
		}
		else k = 0;

	}
}
//Array140.Дано множество A из N точек с целочисленными координатами x, y.
//Порядок на координатной плоскости определим следующим образом :
//(x1, y1) < (x2, y2), если либо x1 + y1 < x2 + y2, либо x1 + y1 = x2 + y2 и x1 < x2.
//	Расположить точки данного множества по убыванию в соответствии с ука -
	//занным порядком.
void array140(int* m, int *k) {
	int n = sizeof(m) / sizeof(int), x;
	for (int i = 0; i < n; i++) {
		for (int j = i = 1; j < n; j++) {
			if (m[j] + k[j] > m[i] + k[i] || (m[j] + k[j] == m[i] + k[i] && m[j] > m[i])) {
				x = m[i];
				m[i] = m[j];
				m[j] = m[i];
				x = k[i];
				k[i] = k[j];
				k[j] = k[i];
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << m[i] << ' ' << k[i] << endl;
}
int main()
{
	int code,a,b,key=0,c;
	int *m;
	while (true) {
		do {
			system("cls");
			key = (key + 13) % 13;
			if (key == 0) cout << "-> array10" << endl;
			else  cout << "   array10" << endl;
			if (key == 1) cout << "-> array20" << endl;
			else  cout << "   array20" << endl;
			if (key == 2) cout << "-> array30" << endl;
			else  cout << "   array30" << endl;
			if (key == 3) cout << "-> array40" << endl;
			else  cout << "   array40" << endl;
			if (key == 4) cout << "-> array50" << endl;
			else  cout << "   array50" << endl;
			if (key == 5) cout << "-> array60" << endl;
			else  cout << "   array60" << endl;
			if (key == 6) cout << "-> array80" << endl;
			else  cout << "   array80" << endl;
			if (key == 7) cout << "-> array90" << endl;
			else  cout << "   array90" << endl;
			if (key == 8) cout << "-> array100" << endl;
			else  cout << "   array100" << endl;
			if (key == 9) cout << "-> array110" << endl;
			else  cout << "   array110" << endl;
			if (key == 10) cout << "-> array120" << endl;
			else  cout << "   array120" << endl;
			if (key == 9) cout << "-> array130" << endl;
			else  cout << "   array130" << endl;
			if (key == 10) cout << "-> array140" << endl;
			else  cout << "   array140" << endl;
			
			code = _getch();
			if (code == 224)
			{
				code = _getch();
				if (code == 80) key++;
				if (code == 72) key--;
			}
		} while (code != 13);
		system("cls");
		cin >> n;
		
		int *m= new int[n];
		
		if (key != 12) {
			

			for (int i = 0; i < n; i++)
				cin >> m[i];
		}
		if (key == 0) {  array10(m); }
		if (key == 1) { cin >> b>>c; array20(m,b,c); }
		if (key == 2) {  array30(m); }
		if (key == 3) { cin >> a; array40(m,a); }
		if (key == 4) { array50(m); }
		if (key == 5) { array60(m); }
		if (key == 6) {  array80(m); }
		if (key == 7) { cin >> a ; del(m, a); }
		if (key == 8) {  array100(m); }
		if (key == 9) {  array110(m); }
		if (key == 10) {  array120(m); }
		if (key == 11) {  array130(m); }

		if (key == 12) {  
			cin >> n;
			int* m = new int[n], *m1= new int[n];
			for (int i = 0; i < n; i++)
				cin >> m[i]>>m1[i];
			array140(m,m1); }
		system("pause");
		delete(m);
	}
}

