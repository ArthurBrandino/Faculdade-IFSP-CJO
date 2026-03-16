//C02EX03M.CPP

#include <iostream>
#include <cctype>

using namespace std;

int main(void)
{
    string NAME;
    char GENDER;

    cout << "Greeting Program" << endl << endl;

    cout << "Enter your Name: "; 
    cin >> NAME;
    cin.ignore(80, '\n');

    cout << "Enter your Gender (M/F): "; 
    cin >> GENDER;
    cin.ignore(80, '\n');

    GENDER = toupper(GENDER);

    if (GENDER == 'M' || GENDER == 'F') {
        if (GENDER == 'M')
            cout << "Dear Mr. " << NAME << endl;
        else
            cout << "Dear Ms. " << NAME << endl;
    }
    else {
        cout << "Invalid gender input!" << endl;
    }

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
