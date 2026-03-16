//C03EX03T.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float DISTANCE, TIME, SPEED;

    cout << "Projectile Speed Calculation Program" << endl << endl;

    cout << "Enter the distance traveled in km: "; cin >> DISTANCE;
    cin.ignore(80, '\n');

    cout << "Enter the time traveled in minutes: "; cin >> TIME;
    cin.ignore(80, '\n');

    SPEED = (DISTANCE * 1000) / (TIME * 60);
    
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 
    cout << "*" << setw(20) << " RESULT " << setw(11) << "*" << endl;
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << "The Projectile's Speed is " << fixed << setprecision(2) << SPEED << " m/s" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
