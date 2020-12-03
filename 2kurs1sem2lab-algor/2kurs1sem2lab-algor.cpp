// 2kurs1sem2lab-algor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;


void printArray(vector<int> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << ' ';
	}
	printf("\n");
}


int temp1, temp2; int i; int j;
int partition(int*arr, int low,
	int high, int pivot)
{
	i = low;
	

	for (j = low; j < high; j++)
	{
		if (arr[j] < pivot)
		{
			temp1 = arr[i];
			arr[i] = arr[j];
			arr[j] = temp1;
			i++;
		}
		else if (arr[j] == pivot)
		{
			temp1 = arr[j];
			arr[j] = arr[high];
			arr[high] = temp1;
			j--;
		}
	}
	temp2 = arr[i];
	arr[i] = arr[high];
	arr[high] = temp2;

	
	return i;
}
int pivot;
int max_depth = 0;
void matchPairs(int*nuts, int*bolts,
	int low, int high,int depth)
{		
	if (depth > max_depth)
		max_depth = depth;

		
		 pivot = partition(nuts, low,
			high, bolts[high]);

		
		partition(bolts, low, high, nuts[pivot]);

		
		if (low<pivot-1)
		matchPairs(nuts, bolts, low, pivot - 1,depth+1);
		if (pivot+1<high)
		matchPairs(nuts, bolts, pivot + 1, high,depth+1);
	
}
void testPartition() {
	int n;
	cin >> n;
	
	int* nuts = new int[n];// = { 3,5,4,1,2 , };
	int* bolts = new int[n];// = { 5,1,3,2,4 };

	for (int i = 0; i < n; i++) {
		nuts[i] = i;
		bolts[i] = (n - i - 1);
	}
	
	matchPairs(nuts, bolts, 0, n - 1,0);

	

	 //for (int i=0;i<n;i++)
	for (i = 0; i < n; i++) {
		if (nuts[i] != bolts[i])
		{
			cout << "no"; //return 0;
		}
	}
	cout << "1";
}
void QuickSortOne(int* a, int* b, int low, int high) {
	int i = low, j = high, i1 = low, j1 = high;
	int mid = (high + low) / 2;

	int first = a[mid];
	int temp;

	for (int k = low; k <= high; ++k) {
		if (b[k] == first) {
			temp = b[k];
			b[k] = b[mid];
			b[mid] = temp;
			break;
		}
	}

	int temp1 = b[mid];

	do {
		while (b[i] < first)
			i++;

		while (first < b[j])
			j--;

		if (i <= j) {
			temp = b[i];
			b[i] = b[j];
			b[j] = temp;

			i++;
			j--;
		}

	} while (i < j);

	do {
		while (a[i1] < temp1)
			i1++;

		while (temp1 < a[j1])
			j1--;

		if (i1 <= j1) {
			temp = a[i1];
			a[i1] = a[j1];
			a[j1] = temp;

			i1++;
			j1--;
		}
	} while (i1 < j1);


	if (low < j)
		QuickSortOne(a, b, low, j);

	if (i < high)
		QuickSortOne(a, b, i, high);
}
void testquick() {
	int n;
	cin >> n;

	int* nuts = new int[n];// = { 3,5,4,1,2 , };
	int* bolts = new int[n];// = { 5,1,3,2,4 };

	for (int i = 0; i < n; i++) {
		nuts[i] = i;
		bolts[i] = (n - i - 1);
	}

	QuickSortOne(nuts, bolts, 0, n - 1);
	for (i = 0; i < n; i++) {
		//if (nuts[i] != bolts[i])
		//{
		//	cout << "no"; //return 0;
		//}
		cout << nuts[i] << ' ' << bolts[i] << endl;
	}
	cout << "1";
}
int main()
{
	//testPartition();
	//cout << max_depth;
	testquick();
}

