#include <iostream>
#include <ctime>

#define dogsNum 9
#define dogSitterNum 3
using namespace std;


typedef struct Node {
	int data;
	int index;
} Node;

void MergeSort(Node *a, int low, int high);
void Merge(Node *a, int low, int high, int mid);
void printNodesArray(Node *arr, int size);
void printBestGroups(Node *arr, Node *limitsArray);






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
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}

	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}

	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}


	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i - low];
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
	Node *counts,*limitsArray;
	int j = 0;
	counts = new Node[dogsNum - 1];
	for (int i = dogsNum - 1; i>=0; i--) {         // here we build our diffs array
		counts[i].data = a[i].data - a[i - 1].data;
		counts[i].index = i+1;                  // we save the index where we made the subtract 
		cout << "index is : " << i << endl;
	}
	cout << "here is the counts array :" << endl;
	for (int i = dogsNum-1; i>0; i--) {
		cout << counts[i].data << endl;
	}

	MergeSort(counts, 0, dogsNum - 1);     // now we merge the counts array to be able to find the highest difference in the end of the array

	cout << "here is the counts array after merge  :" << endl;
	for (int i = dogsNum - 1; i>0; i--) {
		cout << counts[i].data << endl;
	}

	cout << "here is the counts array INDEX'S after merge  :" << endl;
	for (int i = dogsNum - 1; i>0; i--) {
		cout << counts[i].index << endl;
	}


	limitsArray = new Node[dogSitterNum-1];
	for (int i = 0; i < dogSitterNum-1; i++) {
		limitsArray[j].data = counts[dogsNum - (1+i)].index; // recevies the index of limit of the highest difference	
		j++;
		}
	MergeSort(limitsArray, 0, dogSitterNum - 1);


	cout << "we need to slice the array in this index's :" << endl;
	
	for (int i = dogSitterNum - 1; i > 0; i--) {
		cout << limitsArray[i].data << endl;
		
	}
	cout << endl;

	printBestGroups(a, limitsArray);

	}


void printNodesArray(Node *arr, int size) {
	for (int i = 0;  i< size; i++) {
		cout << arr[i].data << endl;
	}
}

void printBestGroups(Node *arr, Node *limitsArray) {
	int j = 0;
	int sumFinal = 0;
	int sum = 0;


	for (int i = 1; i < dogSitterNum; i++) {
		sum = 0;
		sum = arr[limitsArray[i].data-2].data - arr[j].data;
			cout << sum << endl;
			j = limitsArray[i].data - 1;
			if (i+ 1 == dogSitterNum) {
				sum = 0;
				sum = arr[dogsNum-1].data-arr[limitsArray[dogSitterNum-2].data].data;
				cout << "the last sum is : " << sum << endl;
			   
			}

	}
}




	void main() {
	srand(time(NULL));
	Node *arr;
	arr = new Node[dogsNum];
	for (int i = 0; i < dogsNum; i++) {
		arr[i].data = ((rand() % 20) +i) * 10;
	}
	printNodesArray(arr, dogsNum);

	cout << "end of dogs array insert" << endl;

	MergeSort(arr, 0, dogsNum-1);
	printNodesArray(arr, dogsNum);
	cout << "merge completed" << endl;


	buildCounts(arr);
	system("pause");
}
