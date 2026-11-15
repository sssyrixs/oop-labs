#pragma once // защита от повторного подключ

#include <iostream>

#include "time_of_day.h"

// класс дл€ хран инфы о прин€тых лекарствах и какеи нужно
// динам массивы наименование, план приема, отметки приема.
class Medication_Intake { // объ€вление типа
public:
    static constexpr int kDosesPerDay = 5; // статик то что принадлежит классу

    // конструкт с парам наименование лекарства и день приема  / проверка что всЄ ок, коп стр в дин пам€ть
    Medication_Intake(const char* const medication_name, int intake_day);

    // динам пам€т освоб
    ~Medication_Intake();

    // без копировани€ тк динам пам€ть
    Medication_Intake(const Medication_Intake&) = delete;
    Medication_Intake& operator=(const Medication_Intake&) = delete;

    // селекторы // TODO перенести реализации cpp
    const char* GetMedicationName() const { return medication_name_; } // геттеры
    int GetIntakeDay() const { return intake_day_; } 

    void SetPlanForTime(TimeOfDay time, bool is_planned); // сеттеры

    void SetTakenForTime(TimeOfDay time, bool is_taken);

    bool IsIntakeNeeded(TimeOfDay time) const;

    bool IsCompliantWithPlan() const;

    void PrintIntakeInfo() const;

private:
    char* medication_name_;   // динамическа€ пам€ть: наименование
    int intake_day_;          // номер дн€ с начала года
    bool* plan_;              // план приема
    bool* doses_taken_;       // фактический прием
};