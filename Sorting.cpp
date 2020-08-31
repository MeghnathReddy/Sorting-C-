#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time
using namespace std;

class sortElements {
protected:
	int numElements; //Number of elements of the array
	int* elements; //dynamic array with the elements of type int
public:
	sortElements(); // default constructor
	sortElements(int n); // non-default constructor
	~sortElements() {}; // destructor
	void generateRandom(int seed, int lower, int upper); // will generate
														//numElement set of elements randomly with the seedand range from lower to upper

	void displayElements(int* arr); // display the given set
	int* getElementsArray(); // return the entire array of elements
	int getnumElements(); // return the number of elements
	int* bubblesort(int* arr, int low, int high); //bubblesort method
	int* quicksort(int* arr, int low, int high);//quicksort method
	int* shellsort(int* arr, int low, int high);//quicksort method
	int partition(int* arr, int low, int high); //to help quicksort method inorder for pivot values
	void swap(int* orginal, int* previous); //swap places method
};

sortElements::sortElements()
{
	numElements = 0;	//initiate
	elements = NULL;
}

sortElements::sortElements(int n)
{
	numElements = n;		//non-default
	elements = new int[n];
}

void sortElements::generateRandom(int seed, int lower, int upper)
{
	srand(seed); //create a seed 
	int range = upper - lower + 1; //set the range
	for (int i = 0; i < numElements; i++)
	{
		elements[i] = rand() % range + lower; //generate random numbers

	}
}

void sortElements::displayElements(int* arr)
{
	for (int i = 0; i < numElements; i++)
	{
		cout << arr[i] << " "; //display elements
	}
	cout << endl;
}

int* sortElements::getElementsArray()
{
	return elements;
}

int sortElements::getnumElements()
{
	return numElements;
}

int* sortElements::bubblesort(int* arr, int low, int high)
{

	int i, j;
	bool is_swap;
	for (i = 0; i < numElements - 1; i++) //outer loop
	{
		is_swap = false;
		for (j = 0; j < numElements - i - 1; j++) //inner loop
		{
			if (arr[j] > arr[j + 1]) //check which element is greater
			{
				swap(&arr[j], &arr[j + 1]);
				is_swap = true;
			}
		}
		if (is_swap == false) //if boolean value is false when no elements are swapped
			break;
	}
	int* bubblesort = new int[numElements];
	for (int k = 0; k < numElements; k++) {
		bubblesort[k] = elements[k];	// to go through a loop for numberofelements given
	}
	//delete [] bubblesort; //to free up memory
	return bubblesort;
}

int* sortElements::quicksort(int* arr, int low, int high)
{
	if (low < high)
	{

		int index_part = partition(arr, low, high); //call partition method
		quicksort(arr, low, index_part - 1); ///sort elements before partition recurssive call
		quicksort(arr, index_part + 1, high); //sorted elements after partition recurssive call
	}
	int* quicksort = new int[numElements];
	for (int k = 0; k < numElements; k++) {
		quicksort[k] = elements[k];		// to go through a loop for numberofelements given
	}
	//delete [] quicksort;  //to free up memory
	return quicksort;
	

}

int* sortElements::shellsort(int* arr, int low, int high)
{
	// Start with a big gap, then reduce the gap 
	for (int gap = numElements / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < numElements; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location 
			arr[j] = temp;
		}
	}
	int* shellsort = new int[numElements];
	for (int k = 0; k < numElements; k++) {
		shellsort[k] = elements[k];	// to go through a loop for numberofelements given
	}
	//delete [] shellsort; //to free up memory
	return shellsort;
}


int sortElements::partition(int* arr, int low, int high)
{
	int pivot = arr[high]; //set pivot  
	int i = (low - 1); // index of least element 

	for (int j = low; j <= high - 1; j++)
	{

		if (arr[j] < pivot)		// compare current element with the pivot
		{
			i++; // increase index of lower element  
			swap(&arr[i], &arr[j]); //call the swap method
		}
	}
	swap(&arr[i + 1], &arr[high]); //incremented value swap
	return (i + 1);
}


void sortElements::swap(int* orginal, int* previous)
{
	int temp = *orginal; //store in temporary value
	*orginal = *previous;
	*previous = temp;
}

int main() {
	int numElements,seed{},lower{},upper{},n; //to store the input from input text file
	cin >> numElements;
	sortElements* sort = new sortElements(numElements); //pass number of elements
	cin.get(); //read line
	while (!cin.eof()) { 
		cin >> seed >> lower >> upper;

	};
	n = numElements;
	cout << "Number of elements: " << numElements << endl;
	sort->generateRandom(seed,lower,upper); //call genearte random method with given values
	cout << "Pseudorandom elements:" << endl;
	sort->displayElements(sort->getElementsArray()); //before any change actaul values generated
	cout << "Bubble Sort:" << endl;
	sort->displayElements(sort->bubblesort(sort->getElementsArray(), 0, n - 1)); //result from bubblesort
	cout << "Quick Sort:" << endl;
	sort->displayElements(sort->quicksort(sort->getElementsArray(), 0, n - 1)); //result from quicksort
	cout << "Shell Sort:" << endl;
	sort->displayElements(sort->shellsort(sort->getElementsArray(), 0, n - 1)); //result from shellsort
	cout << "Adaptive Sort:" << endl;
	sort->displayElements(sort->shellsort(sort->getElementsArray(), 0, n - 1)); //result from adptivesort
	
	/*
	//to calculate execution time//
	clock_t start, stop; // clock variables to get the time 
	double totalTime; //to store bubblesort time
	double totalTime1; //to store quicksort time
	double totalTime2; //to store shellsort time
	//for bubblesort
	start = clock(); //clock to check the start time
	sort->bubblesort(sort->getElementsArray(), 0, n - 1);
	stop = clock();//clock to check the End time
	totalTime = ((double)(stop - start)) / CLOCKS_PER_SEC;//calculating the total time
	cout << "time taken for bubblesort  " << totalTime << endl; //displaying the total time taken

	//for quicksort
	start = clock(); //clock to check the start time
	sort->quicksort(sort->getElementsArray(), 0, n - 1);
	stop = clock();//clock to check the End time
	totalTime1 = ((double)(stop - start)) / CLOCKS_PER_SEC;//calculating the total time
	cout << "time taken for quicksort  " << totalTime1 << endl; //displaying the total time taken

	//for shellsort
	start = clock(); //clock to check the start time
	sort->shellsort(sort->getElementsArray(), 0, n - 1);
	stop = clock();//clock to check the End time
	totalTime2 = ((double)(stop - start)) / CLOCKS_PER_SEC;//calculating the total time
	cout << "time taken for shellsort  " << totalTime2 << endl; //displaying the total time taken*/

	return 0;

}

/*
references
for ctime library-http://cplusplus.com/forum/beginner/146620/
for bubblesort-https://www.geeksforgeeks.org/bubble-sort/
for quicksort-https://www.geeksforgeeks.org/quick-sort/
for shellsort-https://www.geeksforgeeks.org/shellsort/
*/