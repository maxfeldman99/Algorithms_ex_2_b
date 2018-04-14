#include <iostream>
#include <ctime>

#define dogsNum 9
#define dogSitterNum 2
using namespace std;


typedef struct Node {
	int data;
	int left, right;
} Node;

void MergeSort(Node *a, int low, int high);
void Merge(Node *a, int low, int high, int mid);







// A function to merge the two half into a sorted data.
void Merge(Node *a, int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k;
	Node *temp;
	temp = new Node[dogsNum];
	i = low;
	k = 0;
	j = mid + 1;

	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i].data < a[j].data)
		{
			temp[k].data = a[i].data;
			k++;
			i++;
		}
		else
		{
			temp[k].data = a[j].data;
			k++;
			j++;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k].data = a[i].data;
		k++;
		i++;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k].data = a[j].data;
		k++;
		j++;
	}


	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i].data = temp[i - low].data;
	}
}

// A function to split array into two parts.
void MergeSort(Node *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		// Split the data into two half.
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);

		// Merge them to get sorted output.
		Merge(a, low, high, mid);
	}
}

void buildCounts(Node *a) {
	Node *counts;
	counts = new Node[dogsNum - 1];
	for (int i = dogsNum - 1; i>0; i--) {
		counts[i].data = a[i].data - a[i - 1].data;
		counts[i].left = i - 1;
		counts[i].right = i;
	}

	MergeSort(counts, 0, dogsNum - 1);
	for (int i = 0; i < dogSitterNum; i++) {
		int limit = counts[dogsNum - 1].right; // recevies the index of limit of the highest difference
		for (int j = dogsNum - 1; j >= 0; j--) {
			cout << "group " << i << "contains the dogs: " << endl;
			if (j > limit - 1) {
				cout << a[j].data;
			}
			// to be continued
			
		}

	}


}




void main() {
	srand(time(NULL));
	Node *arr;
	arr = new Node[dogsNum];
	for (int i = 0; i < dogsNum; i++) {
		arr[i].data = (rand() % 10) * 10;
	}
	for (int i = 0; i < dogsNum; i++) {
		cout << arr[i].data << "," << i << endl;

	}

	MergeSort(arr, 0, dogsNum);

	for (int i = 0; i < dogsNum; i++) {
		cout << arr[i].data << "," << i << endl;

	}
	system("pause");


}
