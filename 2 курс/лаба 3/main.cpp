#include <iostream>
#include "Medicine.h"
using namespace std;

int main() {
    // день 1
    Medicine d1("Аспирин", 1, "08:00");
    cout << d1 << "\n";

    // день 2 как день 1
    Medicine d2(d1, true);
    // день 3 без плана
    Medicine d3(d1, false);

    // уст приема через оператор[]
    d2["08:00"] = "08:00";   // вовремя

    cout << d2 << "\n";
    cout << d3 << "\n";

    // проверка без парам
    cout << "День 2: " << (d2.check() ? "приём по плану" : "приём НЕ по плану") << "\n";

    // проверка с парам
    cout << "День 2 в 08:00: " << (d2.check("08:00") ? "да" : "нет") << "\n";

    return 0;
}