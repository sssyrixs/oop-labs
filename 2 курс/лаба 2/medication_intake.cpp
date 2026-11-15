//#define _CRT_SECURE_NO_WARNINGS
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

Medication_Intake::~Medication_Intake() {
    delete[] medication_name_;
    delete[] plan_;
    delete[] doses_taken_;
}

void Medication_Intake::SetPlanForTime(TimeOfDay time, bool is_planned) {
    // TODO проверить time
    plan_[ToTimeIndex(time)] = is_planned;
}

void Medication_Intake::SetTakenForTime(TimeOfDay time, bool is_taken) {
    // TODO проверить time

    const int index = ToTimeIndex(time);
    if (is_taken && !plan_[index]) {
        throw std::logic_error("Cannot mark intake that is not in the plan");
    }
    doses_taken_[index] = is_taken;
}

bool Medication_Intake::IsIntakeNeeded(TimeOfDay time) const {
    return plan_[ToTimeIndex(time)];
}

bool Medication_Intake::IsCompliantWithPlan() const {
    for (int i = 0; i < kDosesPerDay; ++i) {
        if (plan_[i] != doses_taken_[i]) {
            return false;
        }
    }
    return true;
}

void Medication_Intake::PrintIntakeInfo() const {
    std::cout << "Medication: " << medication_name_ << "\n";
    std::cout << "Intake day: " << intake_day_ << "\n";
    std::cout << "Plan / Actual intake:\n";
    for (int i = 0; i < kDosesPerDay; ++i) {
        std::cout << "  " 
                  << TimeOfDayName(i) << ": plan = " << (plan_[i] ? "yes" : "no") << ", taken = " << (doses_taken_[i] ? "yes" : "no") << "\n";
    }
    std::cout << "Compliant with plan: " << (IsCompliantWithPlan() ? "yes" : "no") << "\n";
}