#include <iostream>
#include <ctime>


using namespace std;


typedef struct Node {

	int data;

	int index;

} Node;



void MergeSort(Node *a, int low, int high,int dogsNum,int dogSitterNum);

void Merge(Node *a, int low, int high, int mid,int dogsNum, int dogSitterNum);

void printNodesArray(Node *arr, int size, int dogsNum, int dogSitterNum);

void printBestGroups(Node *arr, Node *limitsArray, int dogsNum, int dogSitterNum);


// A function to merge the two half into a sorted data.

void Merge(Node *a, int low, int high, int mid, int dogsNum, int dogSitterNum)

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

void MergeSort(Node *a, int low, int high, int dogsNum, int dogSitterNum)

{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		// Split the data into two half.
		MergeSort(a, low, mid, dogsNum, dogSitterNum);
		MergeSort(a, mid + 1, high, dogsNum, dogSitterNum);
		// Merge them to get sorted output.
		Merge(a, low, high, mid, dogsNum, dogSitterNum);
	}

}


void buildCounts(Node *a, int dogsNum, int dogSitterNum) {

	Node *counts, *limitsArray;

	int j = 0;

	counts = new Node[dogsNum - 1];

	for (int i = dogsNum - 1; i >= 0; i--) {         // here we build our diffs array

		counts[i].data = a[i].data - a[i - 1].data;

		counts[i].index = i + 1;                  // we save the index where we made the subtract 

	}

	MergeSort(counts, 0, dogsNum - 1, dogsNum, dogSitterNum);     // now we merge the counts array to be able to find the highest difference in the end of the array

	limitsArray = new Node[dogSitterNum - 1];

	for (int i = 0; i < dogSitterNum - 1; i++) {

		limitsArray[j].data = counts[dogsNum - (1 + i)].index; // recevies the index of limit of the highest difference	

		j++;

	}

	MergeSort(limitsArray, 0, dogSitterNum - 1, dogsNum, dogSitterNum);

	printBestGroups(a, limitsArray, dogsNum, dogSitterNum);

}


void printNodesArray(Node *arr, int size, int dogsNum, int dogSitterNum) {

	for (int i = 0; i< size; i++) {
		cout << arr[i].data << endl;
	}
}

void printBestGroups(Node *arr, Node *limitsArray, int dogsNum, int dogSitterNum) {

	int j = 0;
	int sumFinal = 0;
	int sum = 0;
	if (dogSitterNum > 1) {
		for (int i = 1; i < dogSitterNum; i++) {

			sum = arr[limitsArray[i].data - 2].data - arr[j].data;
			sumFinal = sumFinal + sum;
			int k = arr[limitsArray[i].data - 1].data;

			j = limitsArray[i].data - 1;

			if (i + 1 == dogSitterNum) {

				sum = 0;
				sum = arr[dogsNum - 1].data - k;
				sumFinal = sumFinal + sum;
			}
		}

		cout << "SUM IS  : " << sumFinal << endl;
	}
	else {
		cout << "SUM IS  : " << arr[dogsNum-1].data - arr[0].data << endl;
	}
}



void main() {

	srand(time(NULL));

	Node *arr;
	int dogsNum;
	int dogSitterNum;

	cout << "choose amount of dogs" << endl;
	cin >> dogsNum;
	cout << "choose amount of dogSitters" << endl;
	cin >> dogSitterNum;
	arr = new Node[dogsNum];

	cout << "choose size for your dogs "<< endl;
	for (int i = 0; i < dogsNum; i++) {
		cout << "choose size for dog  " << i + 1 << ": ";
		cin >> arr[i].data;
		cout << endl;
		
	}

	MergeSort(arr, 0, dogsNum - 1, dogsNum, dogSitterNum);
	buildCounts(arr,dogsNum,dogSitterNum);
	delete[] arr;
	
	system("pause");

}