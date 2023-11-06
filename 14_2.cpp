#include <iostream>
#include <string>

using namespace std;

struct NOTE
{
    string lastName;
    string firstName;
    string phoneNumber;

    void enterData()
    {
        cout << "enter last name: ";
        cin >> lastName;
        cout << "enter first name: ";
        cin >> firstName;
        cout << "enter phone number: ";
        cin >> phoneNumber;
    }

    void print() 
    {
        cout << lastName << " " << firstName << " " << phoneNumber << endl;
    }
};

void findF(NOTE *a, int l)
{
    string ln;
    cout << "enter last name: ";
    cin >> ln;
    for (int i = 0; i < l; i++)
    {
        if (a[i].lastName == ln)
        {
            a[i].print();
        }
    }
}

void findP(NOTE* a, int l)
{
    string pn;
    cout << "enter last name: ";
    cin >> pn;
    for (int i = 0; i < l; i++)
    {
        if (a[i].phoneNumber == pn)
        {
            a[i].print();
        }
    }
}


int main()
{
    NOTE arr[5] = {};

    for (int i = 0; i < 5; i++)
    {
        arr[i].enterData();
        arr[i].print();
    }

    findF(arr, 5);
}
