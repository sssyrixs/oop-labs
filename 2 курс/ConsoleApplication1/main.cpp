#include <iostream>
#include <windows.h>

class MyArray {
    int* arr;
    int size_;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

public:
    MyArray(int n, int val = 0) {
        size_ = n;
        arr = new int[size_];
        for (int i = 0; i < size_; i++) arr[i] = val;
    }

    MyArray(const MyArray& other) {
        size_ = other.size_;
        arr = new int[size_];
        for (int i = 0; i < size_; i++) arr[i] = other.arr[i];
    }

    MyArray& operator=(const MyArray& other) {
        if (this == &other) return *this;
        delete[] arr;
        size_ = other.size_;
        arr = new int[size_];
        for (int i = 0; i < size_; i++) arr[i] = other.arr[i];
        return *this;
    }

    ~MyArray() { delete[] arr; }

    int size() { return size_; }

    int& operator[](int i) { return arr[i]; }
};

int main() {
    SetConsoleCP(1251);        
    SetConsoleOutputCP(1251);  
    int students = 4, subjects = 5;
    MyArray table(students * subjects);

    table[0 * subjects + 0] = 5;
    table[0 * subjects + 1] = 4;
    table[1 * subjects + 0] = 3;
    table[2 * subjects + 4] = 5;

    for (int s = 0; s < students; s++) {
        int sum = 0;
        for (int p = 0; p < subjects; p++) {
            sum += table[s * subjects + p];
        }
        std::cout << "Студент " << s << ": средний балл = " << sum / (double)subjects << "\n";
    }

    return 0;
}