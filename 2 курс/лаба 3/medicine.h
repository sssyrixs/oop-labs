#pragma once
#include <iostream>
#include <string>

class Medicine {
    std::string name;   // наименование лекарства
    std::string plan;   // плановое время приёма
    std::string fact;   // фактическое время приёма
    int day;            // номер дня

public:
    // Обычный конструктор
    Medicine(std::string n, int d, std::string p);

    // 1. Перегрузка конструктора: (объект, флаг копировать план?)
    Medicine(const Medicine& prev, bool copyPlan);

    // 2. Перегрузка operator<<
    friend std::ostream& operator<<(std::ostream& out, Medicine& obj);

    // 3. Перегрузка operator[] — установка приёма в заданное время
    std::string& operator[](const std::string& time);

    // 4. Перегрузка метода проверки: с параметром и без
    bool check(const std::string& time) const;  // по конкретному времени
    bool check() const;                          // факт == план за день
};