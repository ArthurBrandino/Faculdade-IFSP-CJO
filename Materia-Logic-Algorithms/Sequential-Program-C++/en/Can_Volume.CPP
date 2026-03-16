//C03EX03C.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void){
    float R, VOLUME, HEIGHT;

    float const PI = 3.14159;

    cout << "Can Volume Calculation Program" << endl << endl;

    cout << "Enter the radius of the can: "; cin >> R;
    cin.ignore(80, '\n');
    
    cout << "Enter the height of the can: "; cin >> HEIGHT;
    cin.ignore(80, '\n');

    VOLUME = PI * pow(R, 2) * HEIGHT;

    cout << "The Volume of the Can is: " << VOLUME << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
