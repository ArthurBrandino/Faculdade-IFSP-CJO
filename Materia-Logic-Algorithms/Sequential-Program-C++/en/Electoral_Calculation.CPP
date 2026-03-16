//C03EX03R.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main (void){

    int A, B, C, BLANK, INVALID;

    float TOTAL, PORCENT_A, PORCENT_B, PORCENT_C, PORCENT_BLANK, PORCENT_INVALID;

    cout << "Electoral Calculation Program" << endl << endl;

    cout << "Enter the number of votes for candidate <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the number of votes for candidate <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the number of votes for candidate <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Enter the number of Blank votes: "; cin >> BLANK;
    cin.ignore(80, '\n');

    cout << "Enter the number of Null votes: "; cin >> INVALID;
    cin.ignore(80, '\n');

    TOTAL = A + B + C + BLANK + INVALID;

    PORCENT_A = (100 * A)/TOTAL;
    PORCENT_B = (100 * B)/TOTAL;
    PORCENT_C = (100 * C)/TOTAL;
    PORCENT_BLANK = (100 * BLANK)/TOTAL;
    PORCENT_INVALID = (100 * INVALID)/TOTAL;

    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 
    cout << "*" << setw(20) << " RESULTS " << setw(11) << "*" << endl;
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << "Total Votes:   " << right << setw(12) << TOTAL<< endl << endl;
    cout << fixed << setprecision(2);
    cout << "Candidate <A>: " << right << setw(12) << PORCENT_A << "%" << endl;
    cout << "Candidate <B>: " << right << setw(12) << PORCENT_B << "%" << endl;
    cout << "Candidate <C>: " << right << setw(12) << PORCENT_C << "%" << endl;
    cout << "Blank votes:   " << right << setw(12) << PORCENT_BLANK << "%" << endl;
    cout << "Null votes:    " << right << setw(12) << PORCENT_INVALID << "%" << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}

