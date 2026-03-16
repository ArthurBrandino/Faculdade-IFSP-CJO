// C01EX4H.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float LENGTH, HEIGHT, WIDTH, VOLUME;

    cout << "Box Volume Calculation Program" << endl << endl;

    cout << "Enter the Length: "; cin >> LENGTH;
    cin.ignore(80, '\n');

    cout << "Enter the Height: "; cin >> HEIGHT;
    cin.ignore(80, '\n');

    cout << "Enter the Width: "; cin >> WIDTH;
    cin.ignore(80, '\n');

    VOLUME = LENGTH * WIDTH * HEIGHT;

    cout << "The Volume of the Box is " << fixed << setprecision(2) << VOLUME << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
