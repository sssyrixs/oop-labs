#include <iostream>
#include "Medicine.h"
using namespace std;

int main() {
    // День 1
    Medicine d1("Аспирин", 1, "08:00");
    cout << d1 << "\n";

    // День 2 — копируем план из предыдущего дня
    Medicine d2(d1, true);
    // День 3 — без плана
    Medicine d3(d1, false);

    // Установка приёма через operator[]
    d2["08:00"] = "08:00";   // принял вовремя

    cout << d2 << "\n";
    cout << d3 << "\n";

    // Проверка без параметров
    cout << "День 2: " << (d2.check() ? "приём по плану" : "приём НЕ по плану") << "\n";

    // Проверка с параметром
    cout << "День 2 в 08:00: " << (d2.check("08:00") ? "да" : "нет") << "\n";

    return 0;
}