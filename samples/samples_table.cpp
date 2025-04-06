
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include "polynomial.h"
#include "table.h"

using namespace std;

void printWelcomeMessage() 
{
    cout << "\n\tПривет!!! Эта программа позволит вам выполнять операции с многочленами.\n"
        << " При вводе многочлена, пожалуйста, следуйте некоторым правилам:\n"
        << " 1) Введите многочлен без пробелов\n"
        << " 2) В многочлене допускаются только 3 переменные: x, y и z\n"
        << " 3) Члены многочлена записываются в любом порядке\n"
        << " 4) Степень каждой переменной в члене от 0 до 9\n"
        << " 5) После ввода многочлена нажмите Enter\n\n";
}

void printMenu() 
{
    cout << "Выберите действие, которое хотите выполнить с многочленами:\n"
        << " 1. Сложить два многочлена\n"
        << " 2. Вычесть один многочлен из другого\n"
        << " 3. Перемножить два многочлена\n"
        << " 4. Умножить многочлен на число\n"
        << " 5. Найти количество одночленов в многочлене\n"
        << " 6. Вставить новый многочлен с ключом в таблицы\n"
        << " 7. Найти многочлен по ключу в таблицах\n"
        << " 8. Удалить многочлен по ключу из таблиц\n"
        << " 9. Вставить последний результат с ключом в таблицы\n"
        << " 10. Выход\n"
        << "Ваш выбор: ";
}

void handlePolynomialOperations(int choice, polynomial& lastResult)
{
    string s1, s2;
    cout << "Введите два многочлена:\n";
    cin >> s1 >> s2;

    try
    {
        polynomial p1(s1), p2(s2);

        switch (choice) 
        {
        case 1: p1 += p2; break;
        case 2: p1 -= p2; break;
        case 3: p1 *= p2; break;
        }

        p1.print();
        lastResult = p1;
    }
    catch (const exception& e) 
    {
        cerr << "Ошибка: " << e.what() << "\nПожалуйста, попробуйте снова.\n";
    }
}

void handleSinglePolynomialOperation(int choice, polynomial& lastResult) 
{
    string s;

    cout << "Введите многочлен:\n";

    cin >> s;

    try
    {
        polynomial p(s);

        if (choice == 4) 
        {
            double m;
            cout << "Введите число (double):\n";
            cin >> m;

            p *= m;
            p.print();
            lastResult = p;
        }
        else 
        {
            cout << "Количество одночленов: " << p.get_count() << '\n';
        }
    }
    catch (const exception& e) 
    {
        cerr << "Ошибка: " << e.what() << "\nПожалуйста, попробуйте снова.\n";
    }
}

void insertPolynomialToTables(const polynomial& p, unordered_table<polynomial>& t1,
    ordered_table<polynomial>& t2, hash_table<polynomial>& t3) 
{
    size_t key;

    cout << "Введите ключ для многочлена:\n";

    cin >> key;

    ofstream out("log.txt", ios::app);

    out << "\n**************** Вставка " << p << " ****************\n";

    out.close();

    while (!t1.insert(key, p) || !t2.insert(key, p) || !t3.insert(key, p))
    {
        cerr << "Вставка не удалась: ключ должен быть уникальным\n"
            << "Пожалуйста, попробуйте снова:\n";
        cout << "Введите новый ключ для многочлена:\n";
        cin >> key;
    }

    cout << "Ваш многочлен добавлен в таблицы\n";
}

void findPolynomialInTables(unordered_table<polynomial>& t1,

    ordered_table<polynomial>& t2,

    hash_table<polynomial>& t3) {

    size_t key;

    cout << "Введите ключ для поиска:\n";

    cin >> key;

    auto* found1 = t1.find(key);

    if (found1) 
    {
        cout << "Найден в неупорядоченной таблице: " << *found1 << endl;
    }
    else 
    {
        cout << "Не найден в неупорядоченной таблице\n";
    }

    auto* found2 = t2.find(key);

    if (found2) 
    {
        cout << "Найден в упорядоченной таблице: " << *found2 << endl;
    }
    else 
    {
        cout << "Не найден в упорядоченной таблице\n";
    }

    auto* found3 = t3.find(key);

    if (found3) 
    {
        cout << "Найден в хеш-таблице: " << *found3 << endl;
    }
    else 
    {
        cout << "Не найден в хеш-таблице\n";
    }
}

void erasePolynomialFromTables(unordered_table<polynomial>& t1,

    ordered_table<polynomial>& t2,

    hash_table<polynomial>& t3) 
{
    size_t key;

    cout << "Введите ключ для удаления:\n";

    cin >> key;

    if (t1.erase(key)) 
    {
        cout << "Удален из неупорядоченной таблицы\n";
    }
    else
    {
        cout << "Не найден в неупорядоченной таблице\n";
    }

    if (t2.erase(key))
    {
        cout << "Удален из упорядоченной таблицы\n";
    }
    else
    {
        cout << "Не найден в упорядоченной таблице\n";
    }


    if (t3.erase(key)) 
    {
        cout << "Удален из хеш-таблицы\n";
    }
    else 
    {
        cout << "Не найден в хеш-таблице\n";
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    printWelcomeMessage();

    printMenu();

    int choice;

    cin >> choice;

    polynomial lastResult;

    unordered_table<polynomial> unorderedTable;

    ordered_table<polynomial> orderedTable;

    hash_table<polynomial> hashTable;

    ofstream logFile("log.txt");

    while (choice != 10) 
    {
        try {
            switch (choice) 
            {
            case 1:
            case 2:
            case 3:
                handlePolynomialOperations(choice, lastResult);
                break;

            case 4:
            case 5:
                handleSinglePolynomialOperation(choice, lastResult);
                break;

            case 6:
            {
                string s;

                cout << "Введите многочлен:\n";

                cin >> s;

                polynomial p(s);

                insertPolynomialToTables(p, unorderedTable, orderedTable, hashTable);
                break;
            }

            case 7:
                findPolynomialInTables(unorderedTable, orderedTable, hashTable);
                break;

            case 8:
                erasePolynomialFromTables(unorderedTable, orderedTable, hashTable);
                break;

            case 9:
                if (lastResult.get_count() > 0) 
                {
                    insertPolynomialToTables(lastResult, unorderedTable, orderedTable, hashTable);
                }
                else 
                {
                    cout << "Нет последнего результата для вставки\n";
                }
                break;

            default:
                cout << "Неизвестный пункт меню\n";
            }
        }
        catch (const exception& e) 
        {
            cerr << "Ошибка: " << e.what() << "\nПожалуйста, попробуйте снова.\n";
        }

        printMenu();
        cin >> choice;
    }

    logFile.close();

    cout << "Программа завершена. До свидания!\n";

    return 0;
}