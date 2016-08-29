#include <iostream>
using namespace std;

#include <vector>
#include <assert.h>


void InsertSort(int* a, size_t size)
{
	assert(a);

	for (int i = 0; i < size-1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0 && a[end] > tmp)
		{
			a[end + 1] = a[end];
			--end;
		}
		a[end + 1] = tmp;
	}
}

void ShellSort(int* a , size_t size)
{
	assert(a);

	size_t gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < size - gap; ++i)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0 && (a[end] > tmp))
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

int partSort(int* a, int left, int right)
{
	int key = a[right];
	while (left < right)
	{
		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];
		while (left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}

void QuickSort(int* a, int left, int right)
{
	assert(a);

	if (left > right)
		return;

	int div = partSort(a, left, right);
	QuickSort(a, left, div-1);
	QuickSort(a, div+1, right);
}

void Swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

//void SelectSort(int* a,size_t size)
//{
//	assert(a);
//
//	int i, j, mMinIndex;
//	for (i = 0; i < size; ++i)
//	{
//		mMinIndex = i;
//		for (j = i + 1; j < size; ++j) // 遍历找出该趟最小的值
//		{
//			if (a[j] < a[mMinIndex])
//				mMinIndex = j;		
//		}
//		if (i != mMinindex)
//		{
//			Swap(a[i], a[mMinIndex]); // 让该趟最小的值和该趟其实元素交换一下
//		}
//	
//	}
//}

void SelectSort(int* a, size_t size)
{
	int i, min, max, left, right;
	
	for (left = 0, right = size - 1; left < right; left++, right--)
	{
		min = left;
		max = right;
		for (i = left; i <= right; i++)
		{
			if (a[i] < a[min])
				min = i;
			else if (a[i] > a[max])
				max = i;
		}

		if (min != left)
		{
			Swap(a[left], a[min]);
			if (max == left)
			{
				max = min;
			}
		}

		if (max != right)
		{
			Swap(a[right],a[max]);
		}
	}
}

void TestSelect()
{
	int a[] = { 49, 38, 65, 97, 76, 13, 27, 49 };
	SelectSort(a,sizeof(a)/sizeof(a[0]));

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << a[i] << " ";

	cout << endl;
}


void Merge(int* a, int* tmparr, int startIndex, int midIndex, int endIndex)
{
	int i = startIndex;
	int j = midIndex + 1;
	int k = startIndex; // tmp数组的下标
	while (i != midIndex + 1 && j != endIndex + 1)
	{
		if (a[i] >= a[j])
			tmparr[k++] = a[j++];
		else
			tmparr[k++] = a[i++];
	}

	while (i != midIndex + 1)
		tmparr[k++] = a[i++];

	while (j != endIndex + 1)
		tmparr[k++] = a[j++];

	for (i = startIndex; i <= endIndex; ++i)
		a[i] = tmparr[i];
}

void MergeSort(int* a, int* tmparr, int startIndex,int endIndex)
{
	assert(a);
	if (startIndex < endIndex)
	{
		int midIndex = startIndex + (endIndex - startIndex) / 2;
		MergeSort(a, tmparr, startIndex, midIndex);
		MergeSort(a, tmparr, midIndex + 1, endIndex);
		Merge(a, tmparr, startIndex, midIndex, endIndex);
	}
}

void TestMergeSort()
{
	int a[8] = { 49, 38, 65, 97, 76, 13, 27, 49 };
	int b[8];
	MergeSort(a, b, 0, 7);

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
		cout << a[i] << " ";
	cout << endl;
}

void CountSort(vector<int>& a)
{
	int min = a[0];
	int max = a[0];
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}

	int* count = new int[max - min + 1];
	memset(count, 0, (max - min + 1) * sizeof(int));
	
	for (int i = 0; i < a.size(); ++i)
	{
		count[a[i] - min]++;
	}

	int j = 0;
	for (int i = 0; i < max - min + 1; ++i)
	{
		while (count[i] > 0)
		{
			a[j++] = i + min;
			count[i]--;
		}
	}
}

void TestCountSort()
{
	vector<int> a;
	a.push_back(49);
	a.push_back(38);
	a.push_back(65);
	a.push_back(97);
	a.push_back(76);
	a.push_back(13);
	a.push_back(27);
	a.push_back(49);

	CountSort(a);

	for (int i = 0; i < a.size(); ++i)
		cout << a[i] << " ";

	cout << endl;
}





void TestInsertSort()
{
	int a[] = { 2, 5, 1, 8, 6, 4, 7, 9, 3, 10 };
	InsertSort(a,10);
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void TestShellSort()
{
	int a[] = { 2, 5, 1, 8, 6, 4, 7, 9, 3, 10 };
	ShellSort(a,10);
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void TestQuickSort()
{
	int a[] = { 49, 38, 65, 97, 76, 13, 27, 49};
	int left = 0;
	int right = sizeof(a) / sizeof(a[0]) - 1;
	QuickSort(a,left,right);
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

int main()
{
	TestInsertSort();
	TestShellSort();
	TestQuickSort();
	TestMergeSort();
	TestSelect();
	TestCountSort();

	system("pause");
	return 0;
}
