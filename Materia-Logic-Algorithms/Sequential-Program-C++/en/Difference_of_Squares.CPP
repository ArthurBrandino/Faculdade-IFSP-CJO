//C03EX03J.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main (void){

    int A, B, R;

    cout << "Difference of Squares Program" << endl << endl;

    cout << "Enter the Value of <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the Value of <B>: "; cin >> B;
    cin.ignore(80, '\n');

    if(A > B){
        R = pow(A, 2) - pow(B, 2);
    }
    else{
        R = pow(B, 2) - pow(A, 2);
    }
    
    cout << "The Difference of Squares is: " << R << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
