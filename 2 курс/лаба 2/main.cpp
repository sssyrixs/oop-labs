#include <exception>
#include <iostream>
#include <windows.h>

#include "medication_intake.h"
#include "time_of_day.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try {
        // день 1 обычный прием
        Medication_Intake d1("Aspirin", 1);
        d1.SetPlanForTime(TimeOfDay::kMorning, true);
        d1.SetPlanForTime(TimeOfDay::kNoon, true);
        d1.SetTakenForTime(TimeOfDay::kMorning, true);
        d1.SetTakenForTime(TimeOfDay::kNoon, true);

        std::cout << "=== день 1 (обычный) ===\n" << d1 << "\n";

        // день 1 прием с пояснением
        Detailed_Intake dd1("Aspirin", 1, "принимать до еды");
        dd1.SetPlanForTime(TimeOfDay::kMorning, true);
        dd1.SetPlanForTime(TimeOfDay::kNoon, true);
        dd1.SetTakenForTime(TimeOfDay::kMorning, true);
        dd1.SetTakenForTime(TimeOfDay::kNoon, true);

        std::cout << "=== день 1 (с пояснением) ===\n" << dd1 << "\n";

        // день 2 копия с планом
        Detailed_Intake dd2(dd1, true);
        dd2[TimeOfDay::kMorning] = true;

        std::cout << "=== день 2 (с пояснением, с планом) ===\n" << dd2 << "\n";

        // день 3 копия без плана
        Detailed_Intake dd3(dd1, false);

        std::cout << "=== день 3 (с пояснением, без плана) ===\n" << dd3 << "\n";

        // проверки
        std::cout << "день 2: " << (dd2.check() ? "прием по плану" : "прием НЕ по плану") << "\n";
        std::cout << "день 2 утро: " << (dd2.check(TimeOfDay::kMorning) ? "нужен прием" : "не нужен") << "\n";
        std::cout << "пояснение день 2: " << dd2.GetNote() << "\n";

        // проверка иск
        try { Detailed_Intake bad("Aspirin", 1, ""); }
        catch (const std::exception& e) { std::cout << "Error (empty note): " << e.what() << "\n"; }

        try { dd1.SetNote(nullptr); }
        catch (const std::exception& e) { std::cout << "Error (null note): " << e.what() << "\n"; }
    }
    catch (const std::exception& e) {
        std::cout << "Fatal: " << e.what() << "\n";
    }

    return 0;
}