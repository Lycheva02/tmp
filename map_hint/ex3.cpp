/*
 Рассмотрим банальный случай вставки некоторого пропущенного в map значения.
*/

#include <map>
#include <iostream>
#include <ctime>

int main() {
    double with_hint = 0;
    double without = 0;

    std::map<int, int> map;
    std::map<int, int> map2;

    for (size_t i = 0; i < 5000; i++) {
        if ((i == 4500)) {
            continue;
        } 
        map.insert(map.end(), {i, i});
        map2.insert(map2.end(), {i, i});
    }
    auto hint = map2.find(4499);
    
    // проведём 5 итераций и вычислим среднее время работы
    for (int j = 1; j <= 5; j++) {
        clock_t begin = clock();
        // insert без hint
        map.insert({4500, 0});
        clock_t end = clock();
        without += double(end - begin) / CLOCKS_PER_SEC * 1000;

        clock_t begin2 = clock();
        // insert с hint
        map2.insert(hint, {4500, 0});
        clock_t end2 = clock();
        with_hint += double(end2 - begin2) / CLOCKS_PER_SEC * 1000;
        map.erase(4500);
        map2.erase(4500);
    }

    without /= 5;
    with_hint /= 5;
    std::cout << "Без hint среднее время " << without << std::endl;
    std::cout << "С hint среднее время " << with_hint << std::endl;

    return 0;
}