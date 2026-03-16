//C03EX03E.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    float INSTALLMENTS, TIME, TAX, VALUE;

    cout << "===================================" << endl;
    cout << "  Installment Calculation Program  " << endl;
    cout << "===================================" << endl << endl;

     cout << left << setw(25) << "Enter the Value: "; cin >> VALUE; 
     cin.ignore(80, '\n');

     cout << left << setw(25) << "Enter the Time: "; cin >> TIME; 
     cin.ignore(80, '\n');

     cout << left << setw(25) << "Enter the Tax: "; cin >> TAX; 
     cin.ignore(80, '\n');

     INSTALLMENTS = VALUE + (VALUE *(TAX/100)* TIME);
    
    cout << "\n===================================" << endl;
    cout << left << setw(35) << "The Value of the Installments is: " << fixed << setprecision(2) << INSTALLMENTS << endl;
    cout << "===================================" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
