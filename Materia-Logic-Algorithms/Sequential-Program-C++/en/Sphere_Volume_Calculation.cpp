//C03EX03U.CPP

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void)
{
    float VOLUME, RADIUS;
    const float PI = 3.14159; 

    cout << "Sphere Volume Calculation Program" << endl << endl;

    cout << "Enter the value of the Radius: "; cin >> RADIUS;
    cin.ignore(80, '\n');

    VOLUME =  (4.0 / 3.0) * PI * pow(RADIUS, 3);
    
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 
    cout << "*" << setw(20) << " RESULT " << setw(11) << "*" << endl;
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << "The Volume of the Sphere is " << fixed << setprecision(2) << VOLUME << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
