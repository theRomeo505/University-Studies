// mod2lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;
void swap(int a, int b) {
	int sw = a;
	a = b;
	b = sw;
}
void firstSort(int* arr, int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
			swap(arr[j - 1], arr[j]);
}
void bubleSort(int* arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			swap(arr[i], arr[i + 1]);
		}
	}
}
void shakerSort(int* arr, int n) {
	int buff;
	int left = 0;
	int right = n - 1;
	do {
		for (int i = left; i < right; i++) {
			if (arr[i] > arr[i + 1]) {
				buff = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = buff;
			}
		}
		right--;
		for (int i = right; i > left; i--) {
			if (arr[i] < arr[i - 1]) {
				buff = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = buff;
			}
		}
		left++;
	} while (left < right);
}
void quickSort(int* numbers, int left, int right)
{
	int pivot;
	int l_hold = left;
	int r_hold = right;
	pivot = numbers[left];
	while (left < right)
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--;
		if (left != right)
		{
			numbers[left] = numbers[right];
			left++;
		}
		while ((numbers[left] <= pivot) && (left < right))
			left++;
		if (left != right)
		{
			numbers[right] = numbers[left];
			right--;
		}
	}
	numbers[left] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot)
		quickSort(numbers, left, pivot - 1);
	if (right > pivot)
		quickSort(numbers, pivot + 1, right);
}
int* mergeSort(int* up, int* down, unsigned int left, unsigned int right)
{
	if (left == right)
	{
		down[left] = up[left];
		return down;
	}

	unsigned int middle = (left + right) / 2;


	int* l_buff = mergeSort(up, down, left, middle);
	int* r_buff = mergeSort(up, down, middle + 1, right);


	int* target = l_buff == up ? down : up;

	unsigned int l_cur = left, r_cur = middle + 1;
	for (unsigned int i = left; i <= right; i++)
	{
		if (l_cur <= middle && r_cur <= right)
		{
			if (l_buff[l_cur] < r_buff[r_cur])
			{
				target[i] = l_buff[l_cur];
				l_cur++;
			}
			else
			{
				target[i] = r_buff[r_cur];
				r_cur++;
			}
		}
		else if (l_cur <= middle)
		{
			target[i] = l_buff[l_cur];
			l_cur++;
		}
		else
		{
			target[i] = r_buff[r_cur];
			r_cur++;
		}
	}
	return target;
}
void shellSort(int* array, int size)
{
	int step, i, j, tmp;


	for (step = size / 2; step > 0; step /= 2)

		for (i = step; i < size; i++)

			for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step)
			{
				tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
			}
}
void task1(int** arr, int n, int* new_arr) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) new_arr[i]++;
		}
	}
}
void task2(int** arr, int n, int* new_arr) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) new_arr[i] += arr[i][j];
		}
	}
}
int func(int** coord, int i, int maxcoord) {

	int k = 0;
	for (int j = 0; j < maxcoord; j++) {
		k += coord[i][j];
	}
	return k;
}
void task3(int** coord, int n, int i, int* new_arr, int k) {
	new_arr[i] = k;
	int k = func(coord, i + 1, 2);
	task3(coord, n, i + 1, new_arr, k);
}
void task4(int** arr, int n, int* new_arr) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (arr[i][j] != 0) new_arr[i] += arr[i][j];
		}
	}
}
void rebr2(int** a, int i, int j, int max_coord, int** min_max_coord) {
	for (int k = 0; k < max_coord; k++) {
		min_max_coord[i][k] = a[i][k] + a[j][k];
		min_max_coord[i][k] /= 2;
	}
}
void task5(int** coord, int** arr, int n, int maxcoord, int** new_arr) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) rebr2(coord, i, j, maxcoord, new_arr);
		}
	}
}
int dfs_task6(int** arr, int* used, int* cycles, int n, int v, int length, int start_pos) {
	if (length == 0) cycles[start_pos] += (v + 1) * 100;
	if (length == 1) cycles[start_pos] += (v + 1) * 10;
	if (length == 2) cycles[start_pos] += (v + 1);
	if (length == 1)
		used[v] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (length == 3 && arr[i][j] != 0 && start_pos == j) return 0;
			else if ((length == 3 && arr[i][j] == 0) || (length == 3 && start_pos != j)) {
				cycles[start_pos] = 0;
				return 0;
			}
			if (arr[i][j] != 0) dfs_task6(arr, used, cycles, n, i, length + 1, start_pos);
		}
	}
	return 0;
}
int main()
{
	const int n = 7;
	int new_arr[n];
	int arr[n][n];
	int nodes[n]{ 0 };
	char tested_numb[50];
	FILE* fp = fopen("graf.txt", "r");
	for (int i = 0; i < n; i++) {
		fgets(tested_numb, 50, fp);
		for (int j = 0; j < n; j++) {
			arr[i][j] = tested_numb[j] - '0';
		}
	}
	fclose(fp);

	return 0;
}
