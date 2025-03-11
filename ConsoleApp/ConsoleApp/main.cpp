#include "pch.h"
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

class FuelStack {
private:
    stack<int> fuels; // Стек для хранения бочек с топливом

public:
    bool load(int fuel_type) {
        fuels.push(fuel_type);
        return true;
    }

    bool unload(int fuel_type) {
        if (fuels.empty() || fuels.top() != fuel_type) {
            return false; // Ошибка: нельзя выгрузить
        }
        fuels.pop();
        return true;
    }

    bool isEmpty() const {
        return fuels.empty();
    }

    int topFuel() const {
        return fuels.empty() ? -1 : fuels.top(); // Возвращаем верхнюю бочку
    }
};

class Barge {
private:
    vector<FuelStack> sections; // Отсеки баржи
    int max_capacity; // Максимальное количество бочек
    int current_load; // Текущее количество бочек

public:
    Barge(int K, int P) : sections(K), max_capacity(P), current_load(0) {}

    bool load(int section, int fuel_type) {
        if (current_load >= max_capacity) {
            return false; // Превышен лимит бочек
        }
        sections[section].load(fuel_type);
        current_load++;
        return true;
    }

    bool unload(int section, int fuel_type) {
        if (!sections[section].unload(fuel_type)) {
            return false; // Ошибка при выгрузке
        }
        current_load--;
        return true;
    }

    int getCurrentLoad() const {
        return current_load;
    }

    bool isEmpty() const {
        for (const auto& section : sections) {
            if (!section.isEmpty()) {
                return false; // Если хотя бы один отсек не пуст
            }
        }
        return true; // Все отсеки пусты
    }
};

int main() {
    int N, K, P;
    cin >> N >> K >> P;
    cin.ignore(); // Чистим буфер

    Barge barge(K, P);
    int max_buckets = 0;
    string line;

    for (int i = 0; i < N; i++) {
        getline(cin, line);
        stringstream ss(line);
        char action;
        int section, fuel_type;
        ss >> action >> section >> fuel_type;
        section--; // Приводим к 0-индексации

        // Проверка на допустимость секции
        if (section < 0 || section >= K) {
            cout << "Error!" << endl;
            return 0;
        }

        if (action == '+') {
            if (!barge.load(section, fuel_type)) {
                cout << "Error!" << endl;
                return 0;
            }
        }
        else if (action == '-') {
            if (!barge.unload(section, fuel_type)) {
                cout << "Error!" << endl;
                return 0;
            }
        }

        max_buckets = max(max_buckets, barge.getCurrentLoad());
    }

    if (!barge.isEmpty()) {
        cout << "Error!" << endl;
    }
    else {
        cout << max_buckets << endl;
    }

    return 0;
}
