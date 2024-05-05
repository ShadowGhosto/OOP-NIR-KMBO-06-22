#include <iostream>
#include <list>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

public:

    Fraction(int num, int denom) {
        numerator = num;
        denominator = denom;
    }

    // Геттер для числителя
    int getNumerator() const {
        return numerator;
    }

    // Геттер для знаменателя
    int getDenominator() const {
        return denominator;
    }

    // Перегрузка оператора "<" для сравнения дробей
    bool operator<(const Fraction& other) const {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    // Перегрузка оператора "==" для сравнения дробей
    bool operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

};

void push(list<Fraction>& fractions, const Fraction& obj) {
    fractions.insert(lower_bound(fractions.begin(), fractions.end(), obj), obj);
}

void pop(list<Fraction>& fractions, const Fraction& obj) {
    fractions.remove(obj);
}

// Функция для фильтрации списка
list<Fraction> filter(const list<Fraction>& fractions, int a) {
    list<Fraction> result;
    for (const Fraction& obj : fractions) {
        if (abs(obj.getNumerator()) > a) {
            result.push_back(obj);
        }
    }
    return result;
}

// Функция для вывода содержимого списка с помощью итераторов
void printList(const list<Fraction>& fractions) {
    for (const Fraction& obj : fractions) {
        cout << obj.getNumerator() << "/" << obj.getDenominator() << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    list<Fraction> fractions;
    push(fractions, Fraction(1, 2));
    push(fractions, Fraction(3, 4));
    push(fractions, Fraction(1, 3));
    push(fractions, Fraction(2, 5));

    cout << "Список до фильтрации: ";
    printList(fractions);

    int a = 1;
    list<Fraction> filteredFractions = filter(fractions, a);

    cout << "Список после фильтрации (|numerator| > " << a << "): ";
    printList(filteredFractions);

    return 0;
}