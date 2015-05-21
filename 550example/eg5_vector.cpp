#include <iostream> // Header for stream I/O
#include <vector> // Header for vector class
using namespace std;

int main()
{
   typedef vector<double> vtd; 
   
   const int MAX_SIZE = 5; 
   
   vector<double> vec(MAX_SIZE);  // Declare the array to hold MAX_SIZE values.
   
   for(vtd::size_type i=0;i<vec.size();++i) {
	   vec[i] = i * 10;
	   cout << vec[i] << endl;
   }

   vec.push_back(100);

   for(vtd::size_type i=0;i<vec.size();++i) {
	   cout << vec[i] << endl;
   }
}