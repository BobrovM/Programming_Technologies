#include <iostream>
#include <fstream> //Rus
#include <Windows.h> //Rus
using namespace std;

int h, p, Ch;

int PowerRecurs(int Power)
{
    if (Power == 0) return 1;
    return (p + Ch * h) * PowerRecurs(Power - 1);
}

int main()
{
    //Rus
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int Power = 0, S = 0;
    Ch = Power;
    int Q;

    cout << endl << "Введите p:" << endl;
    cin >> p;
    cout << endl << "Введите h:" << endl;
    cin >> h;
    cout << endl << "Введите Q:" << endl;
    cin >> Q;

    while (S <= Q)
    {
        S += PowerRecurs(Power);
        Ch = ++Power;
    }

    cout << endl << "Ответ: " << S << endl;
}