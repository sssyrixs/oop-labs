#include <exception>
#include <iostream>

#include "medication_intake.h"
#include "time_of_day.h"

int main() {
    try {
        Medication_Intake medication("Aspirin", 100);

        medication.SetPlanForTime(TimeOfDay::kMorning, true);
        medication.SetPlanForTime(TimeOfDay::kNoon, true);
        medication.SetPlanForTime(TimeOfDay::kEvening, true);

        medication.SetTakenForTime(TimeOfDay::kMorning, true);
        medication.SetTakenForTime(TimeOfDay::kNoon, true);
        medication.SetTakenForTime(TimeOfDay::kEvening, true);

        medication.PrintIntakeInfo();

        std::cout << "\nIntake needed at evening: " << (medication.IsIntakeNeeded(TimeOfDay::kEvening) ? "yes" : "no") << "\n";

        // проверка иск и неправильного ввода
        try {
            Medication_Intake bad_name("", 100);
        }
        catch (const std::exception& error) {
            std::cout << "Error (empty name): " << error.what() << "\n";
        }

        try {
            Medication_Intake bad_day("Aspirin", 400);
        }
        catch (const std::exception& error) {
            std::cout << "Error (bad day): " << error.what() << "\n";
        }

        try {
            medication.SetTakenForTime(TimeOfDay::kAfternoon, true);
        }
        catch (const std::exception& error) {
            std::cout << "Error (intake without plan): " << error.what() << "\n";
        }

    }
    catch (const std::exception& error) {
        std::cout << "Fatal: " << error.what() << "\n";
    }

    return 0;
}