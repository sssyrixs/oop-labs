#include "medication_intake.h"
#include <cstring>
#include <stdexcept>

namespace { // внутри сппшки чтобы не было конфликта имен

    // проверка времени и возвращение в индекс
    int ToTimeIndex(TimeOfDay time) {
        const int index = static_cast<int>(time);
        if (index < 0 || index >= Medication_Intake::kDosesPerDay) {
            throw std::invalid_argument("Invalid time of day");
        }
        return index;
    }

    // названия времен суток
    const char* TimeOfDayName(int index) {
        static const char* kNames[Medication_Intake::kDosesPerDay] = {
            "Morning", "Noon", "Afternoon", "Evening", "Night"
        };
        return kNames[index];
    }

}

// конструкт с парам наименование и день / проверки и коп стр в дин память
Medication_Intake::Medication_Intake(const char* const medication_name, int intake_day)
    : medication_name_(nullptr),
    intake_day_(intake_day),
    plan_(new bool[kDosesPerDay] {false}),
    doses_taken_(new bool[kDosesPerDay] {false}) {
    if (medication_name == nullptr || std::strlen(medication_name) == 0) {
        throw std::invalid_argument("Medication name cannot be empty");
    }
    if (intake_day < 1 || intake_day > 365) {
        throw std::out_of_range("Intake day must be between 1 and 365");
    }
    const std::size_t name_length = std::strlen(medication_name);
    medication_name_ = new char[name_length + 1];
    strcpy_s(medication_name_, name_length + 1, medication_name);
}

// перегруз конструкт (объект флаг) / день +1, план по флагу, факт пустой
Medication_Intake::Medication_Intake(const Medication_Intake& prev, bool copy_plan)
    : medication_name_(nullptr),
    intake_day_(prev.intake_day_ + 1), // день +1
    plan_(new bool[kDosesPerDay] {false}),
    doses_taken_(new bool[kDosesPerDay] {false}) {
    const std::size_t name_length = std::strlen(prev.medication_name_);
    medication_name_ = new char[name_length + 1];
    strcpy_s(medication_name_, name_length + 1, prev.medication_name_);

    if (copy_plan) { // план по флагу
        for (int i = 0; i < kDosesPerDay; ++i) {
            plan_[i] = prev.plan_[i];
        }
    }
}

Medication_Intake::~Medication_Intake() { // динам памят освоб
    delete[] medication_name_;
    delete[] plan_;
    delete[] doses_taken_;
}

const char* Medication_Intake::GetMedicationName() const { // геттер
    return medication_name_;
}

int Medication_Intake::GetIntakeDay() const { // геттер
    return intake_day_;
}

void Medication_Intake::SetPlanForTime(TimeOfDay time, bool is_planned) { // сеттер
    const int index = ToTimeIndex(time); // проверка time
    plan_[index] = is_planned;
}

void Medication_Intake::SetTakenForTime(TimeOfDay time, bool is_taken) { // сеттер
    const int index = ToTimeIndex(time); // проверка time
    if (is_taken && !plan_[index]) {
        throw std::logic_error("Cannot mark intake that is not in the plan");
    }
    doses_taken_[index] = is_taken;
}

bool Medication_Intake::IsIntakeNeeded(TimeOfDay time) const { // нужен ли прием
    return plan_[ToTimeIndex(time)];
}

bool Medication_Intake::IsCompliantWithPlan() const { // факт совпадает с планом
    for (int i = 0; i < kDosesPerDay; ++i) {
        if (plan_[i] != doses_taken_[i]) {
            return false;
        }
    }
    return true;
}

// перегруз check с парам
bool Medication_Intake::check(TimeOfDay time) const {
    return IsIntakeNeeded(time);
}

// перегруз check без парам
bool Medication_Intake::check() const {
    return IsCompliantWithPlan();
}

// перегруз оператор[] / сслыка чтобы работало присваивание
bool& Medication_Intake::operator[](TimeOfDay time) {
    return doses_taken_[ToTimeIndex(time)];
}

// перегруз оператор<< / единственное место форматирования вывода
std::ostream& operator<<(std::ostream& out, const Medication_Intake& obj) {
    out << obj.medication_name_ << " | день " << obj.intake_day_ << "\n";
    for (int i = 0; i < Medication_Intake::kDosesPerDay; ++i) {
        out << "  " << TimeOfDayName(i)
            << ": план = " << (obj.plan_[i] ? "да" : "нет")
            << ", факт = " << (obj.doses_taken_[i] ? "да" : "нет") << "\n";
    }
    return out;
}

void Medication_Intake::PrintIntakeInfo() const {
    std::cout << *this;
    std::cout << "Compliant with plan: " << (IsCompliantWithPlan() ? "yes" : "no") << "\n";
}

// конструкт наследника: имя, день, пояснение
Detailed_Intake::Detailed_Intake(const char* const medication_name, int intake_day, const char* const note)
    : Medication_Intake(medication_name, intake_day),
    note_(nullptr) {
    SetNote(note);
}

// конструкт наследника (объект флаг) / день +1, план по флагу, пояснение копируем
Detailed_Intake::Detailed_Intake(const Detailed_Intake& prev, bool copy_plan)
    : Medication_Intake(prev, copy_plan),
    note_(nullptr) {
    SetNote(prev.note_);
}

Detailed_Intake::~Detailed_Intake() { // динам памят освоб
    delete[] note_;
}

void Detailed_Intake::SetNote(const char* const note) { // сеттер пояснения
    if (note == nullptr || std::strlen(note) == 0) {
        throw std::invalid_argument("Note cannot be empty");
    }
    delete[] note_; // освоб старую память
    const std::size_t length = std::strlen(note);
    note_ = new char[length + 1];
    strcpy_s(note_, length + 1, note);
}

const char* Detailed_Intake::GetNote() const { // геттер
    return note_;
}

// перегруз оператор<< для наследника / базовая часть + пояснение
std::ostream& operator<<(std::ostream& out, const Detailed_Intake& obj) {
    out << static_cast<const Medication_Intake&>(obj);
    out << "  пояснение: " << obj.note_ << "\n";
    return out;
}