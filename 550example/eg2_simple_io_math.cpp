#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;


void main()
{
    unsigned int Miles;
    const double LessThan100 = 0.25;
    const double MoreThan100 = 0.15;
    double PriceLessThan100, PriceMoreThan100, TotalPrice;

    cout << "Enter the number of miles: ";
    cin >> Miles;

    if(Miles <= 100)
    {
        PriceLessThan100 = Miles * LessThan100;
        PriceMoreThan100 = 0;
    }
    else
    {
        PriceLessThan100 = 100 * LessThan100;
        PriceMoreThan100 = (Miles - 100) * MoreThan100;
    }

    TotalPrice = PriceLessThan100 + PriceMoreThan100;

    cout << "\nTotal Price = $" << TotalPrice << "\n\n";

	cout << "cos(PI) is " << cos(M_PI) << "\n";
}
