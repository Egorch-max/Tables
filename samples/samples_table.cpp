#pragma once

#include <iostream>
#include <string>
#include "polynomial.h"
#include "table.h"
#include <locale>

int main() {

    setlocale(LC_ALL, "Russian");

    std::cout << "\n\tПривет!!! Эта программа позволит вам выполнять операции с многочленами.\n" <<
        " При вводе многочлена, пожалуйста, следуйте некоторым правилам : \n";
    std::cout << " 1) Введите многочлен без пробелов\n" <<
        " 2) В многочлене допускаются только 3 переменные: x, y и z\n" <<
        " 3) Члены многочлена записываются в любом порядке\n" <<
        " 4) Степень каждой переменной в члене от 0 до 9\n" <<
        " 5) После ввода многочлена нажмите Enter\n\n";
    std::cout << "Выберите действие, которое хотите выполнить с многочленами\n" <<
        " 1. Сложить два многочлена\n" <<
        " 2. Вычесть один многочлен из другого\n" <<
        " 3. Перемножить два многочлена\n" <<
        " 4. Умножить многочлен на число\n" <<
        " 5. Найти количество одночленов в многочлене\n" <<
        " 6. Вставить (новый) многочлен с ключом в упорядоченную, неупорядоченную и хеш-таблицу\n" <<
        " 7. Найти многочлен по ключу в упорядоченной, неупорядоченной и хеш-таблице\n" <<
        " 8. Удалить многочлен по ключу из упорядоченной, неупорядоченной и хеш-таблицы\n" <<
        " 9. Вставить полученный многочлен с ключом в упорядоченную, неупорядоченную и хеш-таблицу\n" <<
        " 10. Выход\n";

    int item;
    std::cin >> item;

    polynomial last;

    unordered_table<polynomial> t1;
    ordered_table<polynomial> t2;
    hash_table<polynomial> t3;

    std::ofstream out;
    out.open("log.txt");

    while (item != 10) {
        if (item == 1 || item == 2 || item == 3) {
            std::cout << " Введите два многочлена:\n";

            std::string s1, s2;
            std::cin >> s1 >> s2;
            try {
                polynomial p1(s1), p2(s2);

                if (item == 1) {
                    p1 += p2;
                }
                else {
                    if (item == 2) p1 -= p2;
                    else p1 *= p2;
                }
                p1.print();
                last = p1;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cout << " Пожалуйста, попробуйте снова:\n";
            }
        }
        if (item == 4 || item == 5) {
            try {
                std::cout << "Введите многочлен\n";
                std::string s;
                std::cin >> s;
                polynomial p(s);

                if (item == 4) {
                    std::cout << "Введите число (double)\n";
                    double m;
                    std::cin >> m;

                    p *= m;
                    p.print();
                    last = p;
                }
                else
                    std::cout << p.get_count() << '\n';

            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cout << " Пожалуйста, попробуйте снова:\n";
            }
        }
     
        if (item >= 6 && item <= 9) {
            try {
                std::string s;
                polynomial p;
                if (item == 6) {
                    std::cout << "Введите многочлен\n";
                    std::cin >> s;
                    p = s;
                }

                std::cout << "Введите имя многочлена в качестве ключа\n";
                size_t key;
                std::cin >> key;

                if (item == 6) {
                    std::ofstream out;
                    out.open("log.txt", std::ios::app);
                    out << "\n**************** Вставка ";
                    out << p;
                    out << " ****************\n";
                    out.close();

                    while (t1.insert(key, p) != true) {
                        std::cout << "Вставка не удалась: ключ должен быть уникальным\n";
                        std::cout << " Пожалуйста, попробуйте снова:\n";

                        std::cout << "Введите имя многочлена в качестве ключа\n";
                        std::cin >> key;
                    }
                    t2.insert(key, p);
                    t3.insert(key, p);

                    std::cout << "Ваш многочлен добавлен в таблицы\n";
                }
                if (item == 9) {
                    std::ofstream out;
                    out.open("log.txt", std::ios::app);
                    out << "\n**************** Вставка ";
                    out << last;
                    out << " ****************\n";
                    out.close();

                    while (t1.insert(key, last) != true) {
                        std::cout << "Вставка не удалась: ключ должен быть уникальным\n";
                        std::cout << " Пожалуйста, попробуйте снова:\n";

                        std::cout << "Введите имя многочлена в качестве ключа\n";
                        std::cin >> key;
                    }

                    t2.insert(key, last);
                    t3.insert(key, last);

                    std::cout << "Ваш многочлен добавлен в таблицы\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cout << " Пожалуйста, попробуйте снова:\n";
            }
        }
        std::cout << "Введите пункт\n";
        std::cin >> item;
    }

    out.close();
    return 0;
}