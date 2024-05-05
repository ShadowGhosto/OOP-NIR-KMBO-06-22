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

    // ������ ��� ���������
    int getNumerator() const {
        return numerator;
    }

    // ������ ��� �����������
    int getDenominator() const {
        return denominator;
    }

    // ���������� ��������� "<" ��� ��������� ������
    bool operator<(const Fraction& other) const {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    // ���������� ��������� "==" ��� ��������� ������
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

// ������� ��� ���������� ������
list<Fraction> filter(const list<Fraction>& fractions, int a) {
    list<Fraction> result;
    for (const Fraction& obj : fractions) {
        if (abs(obj.getNumerator()) > a) {
            result.push_back(obj);
        }
    }
    return result;
}

// ������� ��� ������ ����������� ������ � ������� ����������
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

    cout << "������ �� ����������: ";
    printList(fractions);

    int a = 1;
    list<Fraction> filteredFractions = filter(fractions, a);

    cout << "������ ����� ���������� (|numerator| > " << a << "): ";
    printList(filteredFractions);

    return 0;
}