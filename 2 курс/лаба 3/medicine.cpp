#include "Medicine.h"
using namespace std;

// конструктор
Medicine::Medicine(string n, int d, string p) : name(n), day(d), plan(p), fact("") {}

// конструкт (объект флаг)
Medicine::Medicine(const Medicine& prev, bool copyPlan) {
    name = prev.name;
    day = prev.day + 1;               // день +1
    plan = copyPlan ? prev.plan : "";  // план по флагу
    fact = "";
}

// оператор<<
ostream& operator<<(ostream& out, Medicine& obj) {
    out << obj.name << " | день " << obj.day
        << " | план " << obj.plan
        << " | факт " << (obj.fact.empty() ? "Ч" : obj.fact);
    return out;
}

// оператор[] ссылка дл€ присваивани€
string& Medicine::operator[](const string& time) {
    return fact = time;
}

// проверка по конкр врем
bool Medicine::check(const string& time) const {
    return fact == time;
}

// проверка без парам
bool Medicine::check() const {
    return !fact.empty() && fact == plan;
}