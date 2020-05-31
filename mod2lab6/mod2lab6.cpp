#include <iostream>
using namespace std;
char cl[70];
int p[70];
int cycle_st = -1, cycle_end;
int min(int a, int b)
{
	return (a > b ? b : a);
}
int task1(int** mas, int n, int a, int b) {
	a--; b--;

	if (a == b) {
		cout << "ERROR\n";
		return 0;
	}
	if (a > b) {
		int k = a;
		a = b; b = k;
	}
	for (int j = 0; j < n; j++) {
		if (mas[b][j] == 1) mas[a][j] = 1;
	}
	for (int i = b; i < n - 1; i++) {
		for (int j = 0; j < n; j++) {
			mas[i][j] = mas[i + 1][j];
		}
	}
	return 0;
}
int task2(int** a, int n) {
	long long maxr = 0;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j && a[i][k] != 0 && a[k][j] != 0) {
					if (a[i][j] == 0) {
						a[i][j] = a[i][k] + a[k][j];
					}
					else
					{
						a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > maxr) maxr = a[i][j];
		}
	}
	return maxr;
}

bool dfs_task3(int v, int** arr, int n) {
	cl[v] = 1;
	for (size_t i = 0; i < n; ++i) {
		int to = arr[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			if (dfs_task3(to, arr, n))  return true;
		}
		else if (cl[to] == 1) {
			cycle_end = v;
			cycle_st = to;
			return true;
		}
	}
	cl[v] = 2;
	return false;
}
void task3(int** arr, int n) {
	int v = 0;
	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) v += arr[i][j];
		}
		if (v > max) max = v;
	}
	if (max > n) max = n;
	if (max == 0) max = 1;
	for (int i = 0; i < n; i++) {
		if (dfs_task3(i, arr, n))break;
	}
	if (max == 2) {
		if (cycle_st != -1) {
			max++;
		}
	}
	cout << max << endl;
}
void dfs_task5(int* used, int** a, int n, int s) {
	used[s] = 1;
	for (int i = 0; i < n; i++) {
		if (used[i] == 0 && a[s][i] == 1)
			dfs_task5(used, a, n, i);
	}
}
void GetMatr(int** mas, int** p, int i, int j, int m) {
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) {
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) {
			if (kj == j) dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}
int task4(int** mas, int m) {
	int i, j, d, k, n;
	int** p;
	p = new int* [m];
	for (i = 0; i < m; i++)
		p[i] = new int[m];
	j = 0; d = 0;
	k = 1;
	n = m - 1;
	if (m < 1) cout << "Определитель вычислить невозможно!";
	if (m == 1) {
		d = mas[0][0];
		return(d);
	}
	if (m == 2) {
		d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
		return(d);
	}
	if (m > 2) {
		for (i = 0; i < m; i++) {
			GetMatr(mas, p, i, 0, m);
			d = d + k * mas[i][0] * task4(p, n);
			k = -k;
		}
	}
	cout << d << endl;
	for (int i = 0; i < m; i++) {
		delete[] p[i];
	}
	delete[] p;
	return(d);
}
void task5(int** a, int* used, int n)
{
	int cnt = 0;
	//dfs(3);

	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			dfs_task5(used, a, n, i);
			cnt++;
		}
	}

	cout << endl << cnt << endl;
}
void prnt(int* path, int n)
{
	int p;
	for (p = 0; p < n; p++)
		cout << path[p] + 1 << "\t";
	cout << path[0] + 1;
	cout << "\n";
}
int task6(int k, int* path, int n, int* c, int v0, int** a)
{
	int v, q1 = 0;
	for (v = 0; v < n && !q1; v++)
	{
		if (a[v][path[k - 1]] || a[path[k - 1]][v])
		{
			if (k == n && v == v0) q1 = 1;
			else if (c[v] == -1)
			{
				c[v] = k; path[k] = v;
				q1 = task6(k + 1, path, n, c, v0, a);
				if (!q1) c[v] = -1;
			}
			else continue;
		}
	}   return q1;
}
void is_bridge(int a, int b) {
	cout << a << "-" << b << endl;
}
void max_task7(int** arr, int n, int* versh, int* number) {
	int k = 0;
	for (int i = 0; i < n; i++) {
		k = 0;
		for (int j = 0; j < n; j++) {
			k += arr[i][j];
		}
		versh[i] = k;
	}
	int swap = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (versh[j] == swap) number[swap]++;
			swap++;
		}
	}
}
void task7(int** arr, int n) {
	int al = n;
	int* versh = new int[n];
	int* number = new int[n] {};
	max_task7(arr, n, versh, number);
	int calc = 0;
	for (int i = n - 1; i > 0; i--) {
		if (number[i] >= i - 1) cout << "K" << i + 1 << endl;
	}
	delete[] versh;
	delete[] number;
}
void dfs_task8(int v, int* used, int n, int** arr)
{
	used[v] = 1;
	for (int i = 0; i < n; i++) {
		if (used[i] != 1 && arr[v][i] == 1) {
			dfs_task8(i, used, n, arr);
		}
	}
}
void dfs_task9(int start_pos, int v, int* used, int n, int** arr, int leng)
{
	used[v] = 1;
	for (int i = 0; i < n; i++) {
		if (v != start_pos && arr[v][start_pos] == 1 && abs(v - start_pos) > 1) {
			cout << "There is a cycle\nLength= " << leng << endl;
			break;
		}
		if (used[i] != 1 && arr[v][i] == 1) {
			leng += 1;
			dfs_task9(start_pos, i, used, n, arr, leng);
		}
	}
}
void task10(int** cost, int n) {
	int a, b, u, v, i, j, ne = 1;
	int* visited = new int[n] { 0 };
	int min, mincost = 0,
		int path[100] = { 0 };
	int path_index = 0;



	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
		{
			if (cost[i][j] == 0)
				cost[i][j] = 999;
		}
	}
	visited[1] = 1;
	cout << "\n";

	while (ne < n)
	{
		for (i = 1, min = 999; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (cost[i][j] < min)
					if (visited[i] != 0)
					{
						min = cost[i][j];
						a = u = i;
						b = v = j;
					}
		if (visited[u] == 0 || visited[v] == 0)
		{
			path[path_index] = b;
			path_index++;
			ne++;
			mincost += min;
			visited[b] = 1;

		}
		cost[a][b] = cost[b][a] = 999;
	}


	cout << "\n";

	cout << 1 << " --> ";
	for (int i = 0; i < n - 1; i++)
	{
		cout << path[i];
		if (i < n - 2) cout << " --> ";
	}

	cout << "\n Min   " << mincost;
	delete[] visited;
}
void dfs_task11(int v, int* used, int* tin, int* fup, int** arr, int timer, int n, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i = 0; i < n; ++i) {
		int to = arr[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs_task11(to, used, tin, fup, arr, timer, n, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
				is_bridge(v, to);
		}
	}
}

void task11(int v, int* used, int* tin, int* fup, int** arr, int timer, int n) {
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs_task11(i, used, tin, fup, arr, timer, n);
}
void task12(int** arr, int n) {
	float k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			k += arr[i][j];
		}
	}
	k /= 2;
	if (n < 3 * k - 6) cout << "planar\n";
	else cout << "not planar\n";
}
void task13(int v, int* used, int* tin, int* fup, int** arr, int timer, int n) {
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs_task11(i, used, tin, fup, arr, timer, n);
}
void task14(int v, int* used, int* tin, int* fup, int** arr, int timer, int n) {
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs_task11(i, used, tin, fup, arr, timer, n);
}
//task13,14==task11}
int main()
{
	const int k = 4;
	char tested_numb[50];

	int n;
	cin >> n;
	int* used = new int[n] {};
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}
	int b = 0;
	cin >> b;
	if (b == 0) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> arr[i][j];
			}
		}
	}
	else {
		FILE* fp = fopen("graf.txt", "r");
		for (int i = 0; i < n; i++) {
			fgets(tested_numb, 50, fp);
			for (int j = 0; j < n; j++) {
				arr[i][j] = tested_numb[j] - '0';
			}
		}
		fclose(fp);
	}
	task7(arr, n);
	
	return 0;

	int nodes[7];
	
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	delete[] used;
	return 0;
}