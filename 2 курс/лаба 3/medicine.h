#pragma once
#include <iostream>
#include <string>

class Medicine {
    std::string name;   // наименование лекарства
    std::string plan;   // плановое время приёма
    std::string fact;   // фактическое время приёма
    int day;            // номер дня

public:
    // обычн констр
    Medicine(std::string n, int d, std::string p);

    // перегруз констр
    Medicine(const Medicine& prev, bool copyPlan);

    // перегрузка оператор<< 
    friend std::ostream& operator<<(std::ostream& out, Medicine& obj);

    // перегруз оператор[] для приема по заданному времени
    std::string& operator[](const std::string& time);

    // перегруз метода проверки с параметром и без
    bool check(const std::string& time) const;  // по конкр врем
    bool check() const;                          // как по плану, так и по факту
};