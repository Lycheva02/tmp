/*
 Рассмотрим случай, когда значения в map вставляются по возрастанию - тогда мы всегда знаем, что их нужно
 ставить в конец.
*/
#include <map>
#include <iostream>
#include <ctime>

int main() {
    double with_hint = 0;
    double without = 0;
    
    // проведём 5 итераций и вычислим среднее время работы
    for (int j = 0; j < 5; j++) {
        std::map<int, int> map;
        clock_t begin = clock();
        // insert без hint
        for (int k = 0; k < 20000; k++) {
            map.insert({k, 0});
        }
        clock_t end = clock();
        without += double(end - begin) / CLOCKS_PER_SEC * 1000;

        std::map<int, int> map2;
        clock_t begin2 = clock();
        // insert с hint
        for (int k = 0; k < 20000; k++) {
            map2.insert(map2.end(), {k, 0});
        }
        clock_t end2 = clock();
        with_hint += double(end2 - begin2) / CLOCKS_PER_SEC * 1000;
    }

    without /= 5;
    with_hint /= 5;
    std::cout << "Без hint среднее время " << without << std::endl;
    std::cout << "С hint среднее время " << with_hint << std::endl;

    return 0;
}