#include <iostream>
#include <string>
using namespace std;

string GetName()
{
    string FirstName, LastName, FN;
    
    cout << "Employee's First Name: ";
    cin >> FirstName;
    cout << "Employee's Last Name: ";
    cin >> LastName;
    
    FN = FirstName + " " + LastName;
    return FN;
}

double GetHours(string FullName)
{
    double Mon, Tue, Wed, Thu, Fri, TotalHours;
    
    cout << endl << FullName << "'s Weekly Hours\n";
    cout << "Monday: ";
    cin >> Mon;
    cout << "Tuesday: ";
    cin >> Tue;
    cout << "Wednesday: ";
    cin >> Wed;
    cout << "Thursday: ";
    cin >> Thu;
    cout << "Friday: ";
    cin >> Fri;
    
    TotalHours = Mon + Tue + Wed + Thu + Fri;
    return TotalHours;
}

int main()
{
    string FullName;
    double Hours;
     
	FullName = GetName();
    Hours = GetHours(FullName);
    
	cout << "\nEmployee's Name: " << FullName;
    cout << "\nWeekly Hours: " << Hours << " hours\n\n";
	
	return 0;
}

