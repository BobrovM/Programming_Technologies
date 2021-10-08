// UnifiedProblem1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//Для русского языка
#include <fstream>
#include "UnifiedProblem1.h"
#include <Windows.h>

using namespace std;

void main()
{
    //Для русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    int Index = -1;

    cout << "Добро пожаловать!" << endl;

    while (Index != 0 )
    {
        cout << endl;
        cout << "Выберите программу из списка:" << endl;
        cout << "1) Дано число x. Вычислить число x13 при помощи пяти операций умножения. Число из файла" << endl;
        cout << "2) Дано натуральное число. Вывести его последнюю цифру. Число из файла" << endl;
        cout << "3) Вычислить сумму четных чисел от 2 до n. n вводится из файла." << endl;
        cout << "4) Вычислить p = n! при n введенной из файла." << endl;
        cout << "5) Поменять местами значения переменных a и b. a и b из файла." << endl;
        cout << "6) Вычислить s = 1 + 2 + 3 + … + n. n из файла." << endl;
        cout << "Или нажмите 0 для завершения программы." << endl << endl;
        cin >> Index;

        if (Index == 0) break;

        SwtchFunction(Index);

        Index = -1;
    }
}

void SwtchFunction(int Index)
{
    switch (Index)
    {
    case 1:
        CalculationOf13DegreeNumber();
        break;
    case 2:
        ReturnLastDigitOfTheNumber();
        break;
    case 3:
        SumOf2To20();
        break;
    case 4:
        FactN();
        break;
    case 5:
        TheSwap();
        break;
    case 6:
        Sum1To100();
        break;
    default:
        cout << endl;
        cout << "Введено неверное значение! Повторите попытку!" << endl;
        break;
    }
}

// Циклы 1
// Дано число x. Вычислите число x13 при помощи пяти операций умножения.

void CalculationOf13DegreeNumber()
{
    cout << endl << "Ввожу число x..." << endl;
    int X, XForLoop, XInput;

    ifstream file("A:\\UniversityStuff\\3Semester\\TechProg\\Problem2\\UnifiedProblem1\\Debug\\1.txt");
    if (!file || file.eof())
    {
        cout << endl << "Файл (1.txt) не найден или поврежден!" << endl;
        return;
    }

    file >> XInput;
    cout << endl << "Число x равно " << XInput<< endl;
    X = XInput;

    cout << endl << "Вычисляю 13 степень числа x..." << endl;

    for (int Index = 0; Index <= 2; ++Index)
    {
        XForLoop = X;
        X *= XForLoop;
    }

    X *= XForLoop;
    X *= XInput;

    cout << endl << "Ответ: x в 13 степени равен " << X << endl;;
}

//Циклы 2
//Дано натуральное число. Выведите его последнюю цифру.

void ReturnLastDigitOfTheNumber()
{
    cout << endl << "Ввожу натуральное число из файла..." << endl;
    int Input;

    ifstream file("A:\\UniversityStuff\\3Semester\\TechProg\\Problem2\\UnifiedProblem1\\Debug\\2.txt");
    if (!file || file.eof())
    {
        cout << endl << "Файл (2.txt) не найден или поврежден!" << endl;
        return;
    }

    file >> Input;

    cout << endl << "Натуральное число из файла равно " << Input << endl;
    cout << endl << "Вычисляю..." << endl;

    Input = Input % 10;

    cout << endl << "Ответ: последня цифра - "<< Input << endl;
}

// Последовательности 2
//Вычислить сумму четных чисел от 2 до 20.

void SumOf2To20()
{
    int Sum = 0, Border1, Border2;

    cout << endl << "Ввожу границы из файла..." << endl;

    ifstream file("A:\\UniversityStuff\\3Semester\\TechProg\\Problem2\\UnifiedProblem1\\Debug\\3.txt");
    if (!file || file.eof())
    {
        cout << endl << "Файл (3.txt) не найден или поврежден!" << endl;
        return;
    }
    
    file >> Border1;
    file >> Border2;
    if (Border2 < Border1) swap(Border1, Border2);

    cout << endl << "Вычисляю сумму четных чисел из границ от " << Border1 << " до " << Border2 << endl;
    for (int Index = Border1 + (Border1 % 2); Index <= 20; Index += 2)
    {
        Sum += Index;
    }

    cout << endl<< "Ответ: сумма равна " << Sum << endl;
}

// Последовательности 1.7
// Вычислить p = n! при n = 8.

void FactN()
{
    int Fact = 1, n;
    cout << endl << "Ввожу n из файла..." << endl;
    ifstream file("A:\\UniversityStuff\\3Semester\\TechProg\\Problem2\\UnifiedProblem1\\Debug\\4.txt");
    if (!file || file.eof())
    {
        cout << endl << "Файл (4.txt) не найден или поврежден!" << endl;
        return;
    }

    file >> n;
    cout << endl << "n из файла равен " << n << endl;

    cout << endl << "Вычисляю факториал..." << endl;
    for (int Index = 1; Index <= n; Index++)
    {
        Fact *= Index;
    }


    cout << endl << "Ответ: факториал равен " << Fact << endl;
}

// Циклы 4
// Даны две целые переменные a и b. Составить программу, после работы которой значения переменных поменялись
    //бы местами, но не используя каких-либо других дополнительных переменных

void TheSwap()
{
    int A, B;
    cout << endl << "Ввожу a и b из файла..." << endl;

    ifstream file("A:\\UniversityStuff\\3Semester\\TechProg\\Problem2\\UnifiedProblem1\\Debug\\5.txt");
    if (!file || file.eof())
    {
        cout << endl << "Файл (5.txt) не найден или поврежден!" << endl;
        return;
    }

    file >> A;
    file >> B;

    cout << endl << "Исходно a = " << A << ", b = " << B << "\n";

    cout << endl << "Меняю местами..." << endl;
    swap(A, B);

    cout << endl << "Ответ: теперь a = " << A << ", b = " << B << endl;
}

//Последовательности 1. Вычислить s = 1 + 2 + 3 + … +100.

void Sum1To100()
{
    //TODO интерфейс для юзера
    int Sum = 0, Border;
    cout << endl << "Ввожу правую границу для суммы из файла..." << endl;
    ifstream file("A:\\UniversityStuff\\3Semester\\TechProg\\Problem2\\UnifiedProblem1\\Debug\\6.txt");
    if (!file || file.eof())
    {
        cout << endl << "Файл (6.txt) не найден или поврежден!" << endl;
        return;
    }

    file >> Border;
    cout << endl << "Правая граница для суммы из файла равна " << Border << endl;

    cout << endl << "Суммирую..." << endl;
    for (int Index = 1; Index <= Border; Index++)
    {
        Sum += Index;
    }

    cout << endl << "Ответ: сумма равна " << Sum << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.