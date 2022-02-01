#include "ShopKeeper.h"
//#include <conio.h>
#include <iostream>
#include <stdlib.h>
//Для русского языка
#include <Windows.h>

using namespace std;

int main()
{
    //Для русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << endl << "Добро пожаловать в ShowKeeper!" << endl;
    string InterIndex;

    while (InterIndex != "exit")
    {
        //Подстраховка
        File.close();
        TempFile.clear();     
        InterIndex.clear();

        cout << endl << "Введите индекс выбора действия или введите |exit| для выхода из прокраммы:" << endl;
        cout << "1) ввежите 1 или |Show positions| чтобы перейти в окно вывода данных файла;" << endl;
        cout << "2) введите 2 или |Redact positions| чтобы перейти в окно изменения позиции;" << endl;
        cout << "3) введите 3 или |Add positions| чтобы перейти в окно добавления позиции;" << endl;
        cout << "4) введите 4 или |Delete positions| чтобы перейти в окно удаления позиции." << endl;
        cout << "Подсказка: ввод |exit| в любой функции кроме меню вернет вас обратно в меню." << endl;
        getline(cin, InterIndex);

        if (InterIndex == "exit")
        {
            return 0;
        }

        switch (ReturnChoiceInMain(InterIndex))
        {
        case 1:
        {
            ShowPositions();
            break;
        }

        case 2:
        {
            RedactPosition();
            break;
        }

        case 3:
        {
            AddPosition();
            break;
        }

        case 4:
        {
            DeletePosition();
            break;
        }

        default:
            cout << endl << "ОШИБКА: неверный ввод! Введите индекс с 1 по 4 или указанные ключевые фразы!" << endl;
            break;
        }
    };
}

void ShowPositions()
{
    ReadFile();
    bool bExitFunc = false;
    while (!bExitFunc)
    {
        cout << endl << "Введите одно из данных значений для поиска:" << endl;
        cout << "1) введите 1 или |Show all| чтобы увидеть все товарные позиции в файле;" << endl;
        cout << "2) введите 2 или |Show specific| чтобы увидеть определенную товарную позицию в файле." << endl;

        //exit

        string ChoiceInShowPos;
        getline(cin, ChoiceInShowPos);

        if (ChoiceInShowPos == "exit")
        {
            return;
        }

        if (ChoiceInShowPos == "Show all" || ChoiceInShowPos == "1")
        {
            //1) Show all
            //красивый вывод всех позиций
            for (int Index = 0; Index < TempFile.size(); Index++)
            {
                string TempOut = "";
                for (int Jindex = 0; Jindex < 4; Jindex++)
                {
                    TempOut += TempFile[Index][Jindex];
                    for (int SpaceCounter = 0; SpaceCounter < GetMaxColLength(Jindex) - TempFile[Index][Jindex].length() + 5; SpaceCounter++)
                    {
                        TempOut += " ";
                    }
                }

                cout << TempOut << endl;
            }

            bExitFunc = true;
        }
        else if (ChoiceInShowPos == "Show specific" || ChoiceInShowPos == "2")
        {
            //2) Show specific
            //вывод определенной строки
            //подсказка ввода кода товарa
            bool bExitError = false;
            int PositionByCode;

            while (!bExitError)
            {
                cout << endl << "Введите код товара:" << endl;
                //С этого момента данная переменая хранит код товара
                getline(cin, ChoiceInShowPos);
                if (ChoiceInShowPos == "exit")
                {
                    return;
                }

                PositionByCode = stoi(FindPositionByCode(ChoiceInShowPos));

                if (PositionByCode == -1)
                {
                    //вывод ошибки
                    cout << endl << "ОШИБКА: код товара не найден в файле!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                }
                else
                {
                    bExitError = true;
                }
            }

            //образование вывода
            CoutSpecificPosition(PositionByCode);
            bExitFunc = true;
        }
        else
        {
            //вывод ошибки и выбор повторить или меню
            cout << endl << "ОШИБКА: введен неверный индекс действия!" << endl;
            cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;
            string ErrorChoice;
            getline(cin, ErrorChoice);
            if (ErrorChoice == "No" || ErrorChoice == "Exit")
            {
                return;
            }
        }
    }

    TempFile.clear();
}

void RedactPosition()
{
    ReadFile();
    //redact positions

    cout << endl << "Введите код товара, данные которого вы хотите:" << endl;

    string Code;
    bool bExitCheck = false;
    int Index = -1;

    while (!bExitCheck)
    {
        getline(cin, Code);

        if (Code == "exit")
        {
            return;
        }

        if (!bIsDigit(Code) || Code.size() != 5)
        {
            cout << endl << "ОШИБКА: код товара должен быть числом и состоять из пяти цифр!" << endl;
            cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

            string ErrorChoice;
            getline(cin, ErrorChoice);
            if (ErrorChoice == "No" || ErrorChoice == "Exit")
            {
                return;
            }
            continue;
        }

        Index = stoi(FindPositionByCode(Code));

        if (Index == -1)
        {
            //вывод ошибки
            cout << endl << "ОШИБКА: код товара не найден в файле!" << endl;
            cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

            string ErrorChoice;
            getline(cin, ErrorChoice);
            if (ErrorChoice == "No" || ErrorChoice == "Exit")
            {
                return;
            }
            continue;
        }
        else
        {
            bExitCheck = true;
        }
    }

    bExitCheck = false;

    while (!bExitCheck)
    {
        cout << endl << "Найдена позиция:" << endl;
        CoutSpecificPosition(Index);
        cout << endl << "Введите столбец, который вы хотите изменить:" << endl;
        cout << "1) введите |1| или |Edit code| чтобы изменить код товара;" << endl;
        cout << "2) введите |2| или |Edit name| чтобы изменить наименование товара;" << endl;
        cout << "3) введите |3| или |Edit stock| чтобы изменить количество товара на складе;" << endl;
        cout << "4) введите |4| или |Edit price| чтобы изменить цену товара." << endl;
        getline(cin, Code);

        if (Code == "exit")
        {
            return;
        }

        bool bExit = false;

        if (Code == "1" || Code == "Edit code")
        {
            while (!bExit)
            {
                cout << endl << "Введите новый код товара:" << endl;
                string TempNewCode, TempLastCode;
                getline(cin, TempNewCode);

                if (TempNewCode.size() != 5)
                {
                    cout << endl << "ОШИБКА: код товара должен состоять из пяти символов!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                if (!bIsDigit(TempNewCode))
                {
                    cout << endl << "ОШИБКА: код товара должен быть числом!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                if (FindPositionByCode(TempNewCode) != "-1")
                {
                    cout << endl << "ОШИБКА: данный код товара уже существует в файле!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                TempLastCode = TempFile[Index][0];
                TempFile[Index][0] = TempNewCode;
                CoutSpecificPosition(Index);

                cout << endl << "Убедитесь в правильности ввода нового кода товара." << endl;
                cout << "Напишите |Yes| если новый код товара удовлетворителкн, для повтора ввода введите |No|." << endl;
                cout << "Или, если хотите выйти в главное меню без сохранения изменений, напишите |exit|." << endl;

                string ChangeChoice;
                getline(cin, ChangeChoice);

                if (ChangeChoice == "exit")
                {
                    TempFile[Index][2] = TempLastCode;
                    return;
                }
                if (ChangeChoice == "Yes")
                {
                    bExit = true;
                    bExitCheck = true;
                    break;
                }

                //введено No
                TempFile[Index][2] = TempLastCode;

            }
        }
        else if (Code == "2" || Code == "Edit name")
        {
            while (!bExit)
            {
                cout << endl << "Введите новое наименование товара на английском языке:" << endl;
                string TempNewName, TempLastName;
                getline(cin, TempNewName);

                if (TempNewName.size() == 0)
                {
                    cout << endl << "ОШИБКА: наименование товара не может быть пустым!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }
                
                TempLastName = TempFile[Index][1];
                TempFile[Index][1] = TempNewName;
                CoutSpecificPosition(Index);

                cout << endl << "Убедитесь в правильности ввода нового наименования." << endl;
                cout << "Новое наименование товара удовлетворяет правильности набора?" << endl;
                cout << "Напишите |Yes| если новое наименование удовлетворительно, для повтора ввода введите |No|." << endl;
                cout << "Или, если хотите выйти в главное меню без сохранения изменений, напишите |exit|." << endl;

                string ChangeChoice;
                getline(cin, ChangeChoice);

                if (ChangeChoice == "exit")
                {
                    TempFile[Index][1] = TempLastName;
                    return;
                }
                if (ChangeChoice == "Yes")
                {
                    bExit = true;
                    bExitCheck = true;
                    break;
                }

                //введено No
                TempFile[Index][1] = TempLastName;
            }
        }
        else if (Code == "3" || Code == "Edit stock")
        {
            while (!bExit)
            {
                cout << endl << "Введите новое количество товара на складе:" << endl;
                string TempNewStock, TempLastStock;
                getline(cin, TempNewStock);

                if (TempNewStock.size() == 0)
                {
                    cout << endl << "ОШИБКА: количество товара не может быть пустым!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                if (!bIsDigit(TempNewStock))
                {
                    cout << endl << "ОШИБКА: количество товара должен быть числом!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                TempLastStock = TempFile[Index][2];
                TempFile[Index][2] = TempNewStock;
                CoutSpecificPosition(Index);

                cout << endl << "Убедитесь в правильности ввода нового количества товара." << endl;
                cout << "Напишите |Yes| если новое количество товаров удовлетворительно, для повтора ввода введите |No|." << endl;
                cout << "Или, если хотите выйти в главное меню без сохранения изменений, напишите |exit|." << endl;

                string ChangeChoice;
                getline(cin, ChangeChoice);

                if (ChangeChoice == "exit")
                {
                    TempFile[Index][2] = TempLastStock;
                    return;
                }
                if (ChangeChoice == "Yes")
                {
                    bExit = true;
                    bExitCheck = true;
                    break;
                }

                //введено No
                TempFile[Index][2] = TempLastStock;
            }
        }
        else if (Code == "4" || Code == "Edit price")
        {
            while (!bExit)
            {
                cout << endl << "Введите новую цену товара:" << endl;
                string TempNewPrice, TempLastPrice;
                getline(cin, TempNewPrice);

                if (TempNewPrice.size() == 0)
                {
                    cout << endl << "ОШИБКА: цена не может быть пустой!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                int DotCounter = 0;
                bool bIsDigit = true;
                for (int CheckIndex = 0; CheckIndex < TempNewPrice.size(); CheckIndex++)
                {
                    if (TempNewPrice[CheckIndex] == ',' && DotCounter < 1)
                    {
                        DotCounter++;
                        continue;
                    }
                    if (!isdigit(TempNewPrice[CheckIndex]))
                    {
                        bIsDigit = false;
                        break;
                    }
                }

                if (!bIsDigit)
                {
                    cout << endl << "ОШИБКА: цена товара должна быть числом и иметь максимум одну запятую!" << endl;
                    cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                    string ErrorChoice;
                    getline(cin, ErrorChoice);
                    if (ErrorChoice == "No" || ErrorChoice == "Exit")
                    {
                        return;
                    }
                    continue;
                }

                TempLastPrice = TempFile[Index][3];
                TempFile[Index][3] = TempNewPrice;
                CoutSpecificPosition(Index);

                cout << endl << "Убедитесь в правильности ввода цены товара." << endl;
                cout << "Напишите |Yes| если новая цена удовлетворительна, для повтора ввода введите |No|." << endl;
                cout << "Или, если хотите выйти в главное меню без сохранения изменений, напишите |exit|." << endl;

                string ChangeChoice;
                getline(cin, ChangeChoice);

                if (ChangeChoice == "exit")
                {
                    TempFile[Index][3] = TempLastPrice;
                    return;
                }
                if (ChangeChoice == "Yes")
                {
                    bExit = true;
                    bExitCheck = true;
                    break;
                }

                //введено No
                TempFile[Index][3] = TempLastPrice;
            }
        }
        else
        {
            //ошибка
            //вывод ошибки и выбор повторить или меню
            cout << endl << "ОШИБКА: введен неверный индекс действия!" << endl;
            cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;
            string ErrorChoice;
            getline(cin, ErrorChoice);
            if (ErrorChoice == "No" || ErrorChoice == "Exit")
            {
                return;
            }
        }
    }

    WriteFile();
    TempFile.clear();
}

void AddPosition()
{
    ReadFile();
    vector<string> TempStrColoumn{};

    while (true)
    {
        while (true)
        {
            cout << endl << "Введите код товара для новой позиции. Он должен состоять из 5 цифр." << endl;
            string NewCode;
            getline(cin, NewCode);

            if (NewCode == "exit")
            {
                return;
            }

            if (NewCode.size() != 5 || !bIsDigit(NewCode))
            {
                cout << endl << "ОШИБКА: код товара должен быть числом и состоять из пяти цифр!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            if (FindPositionByCode(NewCode) != "-1")
            {
                cout << endl << "ОШИБКА: данный код товара уже существует в файле!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            TempStrColoumn.push_back(NewCode);
            break;
        }

        while (true)
        {
            cout << endl << "Введите наименование товара на английском языке:" << endl;
            string NewName;
            getline(cin, NewName);

            if (NewName == "exit")
            {
                return;
            }

            if (NewName.size() == 0)
            {
                cout << endl << "ОШИБКА: наименование товара не может быть пустым!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            TempStrColoumn.push_back(NewName);
            break;
        }

        while (true)
        {
            cout << endl << "Введите количество товара на складе:" << endl;
            string NewStock;
            getline(cin, NewStock);

            if (NewStock == "exit")
            {
                return;
            }

            if (NewStock.size() == 0)
            {
                cout << endl << "ОШИБКА: количество товара не может быть пустым!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            if (!bIsDigit(NewStock))
            {
                cout << endl << "ОШИБКА: количество товара должен быть числом!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            TempStrColoumn.push_back(NewStock);
            break;
        }

        while (true)
        {
            cout << endl << "Введите цену товара:" << endl;
            string NewPrice;
            getline(cin, NewPrice);

            if (NewPrice == "exit")
            {
                return;
            }

            if (NewPrice.size() == 0)
            {
                cout << endl << "ОШИБКА: цена не может быть пустой!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            int DotCounter = 0;
            bool bIsDigit = true;
            for (int CheckIndex = 0; CheckIndex < NewPrice.size(); CheckIndex++)
            {
                if (NewPrice[CheckIndex] == ',' && DotCounter < 1)
                {
                    DotCounter++;
                    continue;
                }
                if (!isdigit(NewPrice[CheckIndex]))
                {
                    bIsDigit = false;
                    break;
                }
            }

            if (!bIsDigit)
            {
                cout << endl << "ОШИБКА: цена товара должна быть числом и иметь максимум одну запятую!" << endl;
                cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

                string ErrorChoice;
                getline(cin, ErrorChoice);
                if (ErrorChoice == "No" || ErrorChoice == "Exit")
                {
                    return;
                }
                continue;
            }

            TempStrColoumn.push_back(NewPrice);
            break;
        }

        TempFile.push_back(TempStrColoumn);

        cout << endl << "Вы ввели:" << endl;
        CoutSpecificPosition(TempFile.size() - 1);
        cout << endl << "Если есть ошибки, вы можете их исправить в функции редактирования позиций." << endl;
        cout << "Можно повторить операцию или выйти без сохранения изменений." << endl;
        cout << "Напишите |Yes| если новая позиция удовлетворительна, для повтора ввода введите |No|." << endl;
        cout << "Или, если хотите выйти в главное меню без сохранения изменений, напишите |exit|." << endl;

        string ChangeChoice;
        getline(cin, ChangeChoice);

        if (ChangeChoice == "exit")
        {
            return;
        }
        if (ChangeChoice == "No")
        {
            continue;
        }

        break;
    }

    WriteFile();
    TempFile.clear();
}

void DeletePosition()
{
    ReadFile();

    string Code;

    while (true)
    {
        cout << endl << "Введите позицию которую надо удалить." << endl;
        getline(cin, Code);

        if (Code == "exit")
        {
            return;
        }

        if (!bIsDigit(Code) || Code.size() != 5)
        {
            cout << endl << "ОШИБКА: код товара должен быть числом и состоять из пяти цифр!" << endl;
            cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

            string ErrorChoice;
            getline(cin, ErrorChoice);
            if (ErrorChoice == "No" || ErrorChoice == "Exit")
            {
                return;
            }
            continue;
        }

        if (FindPositionByCode(Code) == "-1")
        {
            cout << endl << "ОШИБКА: данный код товара не существует в файле!" << endl;
            cout << "Вы хотите повторить операцию? Напишите |Yes| если хотите повторить или |No| если хотите выйти в главное меню." << endl;

            string ErrorChoice;
            getline(cin, ErrorChoice);
            if (ErrorChoice == "No" || ErrorChoice == "Exit")
            {
                return;
            }
            continue;
        }

        break;
    }
    
    cout << endl << "Вы уверены что хотите удалить эту позицию?" << endl;
    CoutSpecificPosition(stoi(FindPositionByCode(Code)));
    cout << endl << "Введите |Yes| если хотите удалить эту позицию или |No| если хотите вернуться в меню и не удалять позицию." << endl;

    string Choice;
    getline(cin, Choice);

    if (Choice == "No" || Choice == "exit")
    {
        return;
    }

    TempFile.erase(TempFile.begin() + stoi(FindPositionByCode(Code)));
    WriteFile();
}

void ReadFile()
{
    TempFile.clear();
    File.open("ShopKeeperPositions.txt");
    string FileLine;
    char Delimiter = '/';

    TempFile.push_back({ "Code","Name","Stock","Price" });

    while (getline(File, FileLine))
    {
        int Counter = 0; //считает колонки от 0 до 3
        vector<string> TempStrColoumn{}; //Колонки
        size_t DelimiterPosition = 0;

        while (/*DelimiterPosition =*/ FileLine.find(Delimiter) != string::npos)
        {
            DelimiterPosition = FileLine.find(Delimiter);
            TempStrColoumn.push_back(string(FileLine.substr(0, DelimiterPosition)));
            FileLine.erase(0, DelimiterPosition + 1); //2 - длина делимитера
            Counter++;
        }

        TempFile.push_back(TempStrColoumn);
    }
    File.close();
}


void WriteFile()
{
    ofstream oFile;
    oFile.open("ShopKeeperPositions.txt");

    for (int Index = 1; Index < TempFile.size(); Index++)
    {
        for (int Jindex = 0; Jindex < 4; Jindex++)
        {
            oFile << TempFile[Index][Jindex] << "/";
        }
        oFile << "\n";
    }

    oFile.close();
}


void CoutSpecificPosition(int Code)
{
    string TempOut = "";
    for (int Jindex = 0; Jindex < 4; Jindex++)
    {
        //0 для заголовков
        TempOut += TempFile[0][Jindex];
        for (int SpaceCounter = 0; SpaceCounter < GetMaxColLength(Jindex) - TempFile[0][Jindex].length() + 5; SpaceCounter++)
        {
            TempOut += " ";
        }
    }

    cout << TempOut << endl;
    TempOut = "";

    for (int Jindex = 0; Jindex < 4; Jindex++)
    {
        TempOut += TempFile[Code][Jindex];
        for (int SpaceCounter = 0; SpaceCounter < GetMaxColLength(Jindex) - TempFile[Code][Jindex].length() + 5; SpaceCounter++)
        {
            TempOut += " ";
        }
    }

    cout << TempOut << endl;
}

int GetMaxColLength(int Jindex)
{
    //Для выравнивания вывода
    int MaxLen = 0;
    //Находим максимальную длину столбца для красивого вывода.
    for (int Index = 1; Index < TempFile.size(); Index++)
    {
        if (TempFile[Index][Jindex].length() > MaxLen) MaxLen = TempFile[Index][Jindex].length();
    }

    return MaxLen;
}

string FindPositionByCode(string Code)
{
    for (int Index = 1; Index < TempFile.size(); Index++)
    {
        if (TempFile[Index][0] == Code)
        {
            return to_string(Index);
        }
    }

    return "-1";
}

int ReturnChoiceInMain(string InterIndex)
{
    //String to int
    if (InterIndex == "Show positions" || InterIndex == "1")
    {
        return 1;
    }
    if (InterIndex == "Redact positions" || InterIndex == "2")
    {
        return 2;
    }
    if (InterIndex == "Add positions" || InterIndex == "3")
    {
        return 3;
    }
    if (InterIndex == "Delete positions" || InterIndex == "4")
    {
        return 4;
    }

    return 0;
}

bool bIsDigit(string Input)
{
    for (int CheckIndex = 0; CheckIndex < Input.size(); CheckIndex++)
    {
        if (!isdigit(Input[CheckIndex]))
        {
            return false;
        }
    }

    return true;
}