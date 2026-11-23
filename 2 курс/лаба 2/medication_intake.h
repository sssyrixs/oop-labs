#pragma once // защита от повторного подключ

#include <iostream>

#include "time_of_day.h"

// класс для хран инфы о принятых лекарствах и какие нужно
// динам массивы наименование, план приема, отметки приема
class Medication_Intake { // объявление типа
public:
    static constexpr int kDosesPerDay = 5; // статик то что принадлежит классу

    // конструкт с парам наименование лекарства и день приема  / проверка что всё ок, коп стр в дин память
    Medication_Intake(const char* const medication_name, int intake_day);

    // перегруз конструкт: копируемый объект и флаг копировать ли план
    Medication_Intake(const Medication_Intake& prev, bool copy_plan);

    // динам памят освоб
    virtual ~Medication_Intake(); // виртуальный тк есть наследник

    // без копирования тк динам память
    Medication_Intake(const Medication_Intake&) = delete;
    Medication_Intake& operator=(const Medication_Intake&) = delete;

    // селекторы
    const char* GetMedicationName() const; // геттеры
    int GetIntakeDay() const;

    void SetPlanForTime(TimeOfDay time, bool is_planned); // сеттеры
    void SetTakenForTime(TimeOfDay time, bool is_taken);

    bool IsIntakeNeeded(TimeOfDay time) const;
    bool IsCompliantWithPlan() const;

    // перегруз метода проверки: с парам и без
    bool check(TimeOfDay time) const; // по конкр вр
    bool check() const;               // как по плану, так и по факту

    // перегруз оператор[] для приема по заданному времени
    bool& operator[](TimeOfDay time);

    // перегруз оператор<<
    friend std::ostream& operator<<(std::ostream& out, const Medication_Intake& obj);

    void PrintIntakeInfo() const; // печать инфы

protected: // было private — для доступа из наследника
    char* medication_name_;   // динам память: наименование
    int intake_day_;          // номер дня с начала года
    bool* plan_;              // план приема
    bool* doses_taken_;       // фактический прием
};

class Detailed_Intake : public Medication_Intake { // наследование
public:
    // конструкт с парам: имя, день, пояснение
    Detailed_Intake(const char* const medication_name, int intake_day, const char* const note);

    // конструкт копия с флагом + пояснение из прошлого объекта
    Detailed_Intake(const Detailed_Intake& prev, bool copy_plan);

    // динам памят освоб
    ~Detailed_Intake() override;

    // без копирования тк динам память
    Detailed_Intake(const Detailed_Intake&) = delete;
    Detailed_Intake& operator=(const Detailed_Intake&) = delete;

    // сеттер пояснения
    void SetNote(const char* const note);

    // геттер пояснения
    const char* GetNote() const;

    // перегруз оператор<< для наследника
    friend std::ostream& operator<<(std::ostream& out, const Detailed_Intake& obj);

private:
    char* note_; // пояснение к приему (строка в дин памяти)
};