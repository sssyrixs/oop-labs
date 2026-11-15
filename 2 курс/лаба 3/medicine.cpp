#include "Medicine.h"
using namespace std;

// конструктор
Medicine::Medicine(string n, int d, string p) : name(n), day(d), plan(p), fact("") {}

// 1. Конструктор (объект, флаг)
Medicine::Medicine(const Medicine& prev, bool copyPlan) {
    name = prev.name;
    day = prev.day + 1;               // день +1
    plan = copyPlan ? prev.plan : "";  // план по флагу
    fact = "";
}

// 2. operator<<
ostream& operator<<(ostream& out, Medicine& obj) {
    out << obj.name << " | день " << obj.day
        << " | план " << obj.plan
        << " | факт " << (obj.fact.empty() ? "—" : obj.fact);
    return out;
}

// 3. operator[] — возвращаем ссылку, чтобы работало присваивание
string& Medicine::operator[](const string& time) {
    return fact = time;
}

// 4а. Проверка по конкретному времени
bool Medicine::check(const string& time) const {
    return fact == time;
}

// 4б. Проверка без параметров — факт соответствует плану
bool Medicine::check() const {
    return !fact.empty() && fact == plan;
}