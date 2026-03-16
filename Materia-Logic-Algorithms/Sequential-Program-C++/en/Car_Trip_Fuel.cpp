//C03EX03D.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float TIME, SPEED, DISTANCE, LITERS_USED;

    cout << "Car Trip Fuel Program" << endl << endl;

    cout << "Enter the duration of the trip: "; cin >> TIME;
    cin.ignore(80, '\n');
    
    cout << "Enter the average speed: "; cin >> SPEED;
    cin.ignore(80, '\n');

    DISTANCE = TIME * SPEED;

    LITERS_USED = DISTANCE /12;

    cout << "******************************" << endl;
    cout << left << setw(25) << "* Average Speed: " << setprecision(1) << SPEED << endl;
    cout << left << setw(25) << "* Duration of the Trip: " << setprecision(1) << TIME << endl;
    cout << left << setw(25) << "* Distance Traveled: " << setprecision(1) << DISTANCE << endl;
    cout << left << setw(25) << "* Liters Used: " << setprecision(1) << LITERS_USED << endl;
    cout << "******************************" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
