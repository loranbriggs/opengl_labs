#include <iostream> // Header for stream I/O
using namespace std;

void main()
{
	int static_array[5];
	int *dynamic_array;
	
	for(int i=0;i<5;++i) {
		static_array[i] = i*10;
		cout << i << "th element is " << static_array[i] << endl;
	}
	
	int array_size;

	cout << "Enter the array size: " ;
	cin >> array_size;

	dynamic_array = new int[array_size];

	for(int i=0;i<array_size;++i) {
		dynamic_array[i] = i*20;
		cout << i << "th element is " << dynamic_array[i] << endl;
	}

	delete[] dynamic_array;
}