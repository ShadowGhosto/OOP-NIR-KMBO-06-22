#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
private:
    double real;
    double image;
public:
    Complex() {
        real = 0; image = 0;
    }
    Complex(double r, double i) {
        real = r; image = i;
    }

    void print()
    {
        if (image == 0)
        {
            cout << "\n" << real << "";
            return;
        }
        if (real == 0)
        {
            cout << "\n" << image << "i";
            return;
        }
        if (image > 0)
            cout << real << " + " << image << "i\n";
        else
            cout << real << " - " << -image << "i\n";
    }

    double getReal() {
        return real;
    }
    double getImage() {
        return image;
    }

    void SetReal(double value) {
        real = value;
    }
    void SetImage(double value) {
        image = value;
    }

    double Module() {
        return sqrt(real * real + image * image);
    }

    Complex operator+(Complex F)
    {
        Complex res;
        res.real = real + F.real;
        res.image = image + F.image;
        return res;
    }
    double operator/(Complex W) {
        double ax = real;
        double bx = image;
        double ay = W.real;
        double by = W.image;

        double a = ((ax * ay) + (bx * by));
        double b = sqrt((ay * ay) + (by * by));
        return a / b;
    }

    bool operator<(Complex F) {
        if (real < F.real) {
            if (image < F.image) {
                return true;
            }
        }
        return false;
    }

    friend bool operator<(double s, Complex F);
};

bool operator<(double s, Complex F) {
    if (s < F.real) {
        if (0 < F.image) {
            return true;
        }
    }
    return false;
}


int main()
{
    setlocale(LC_ALL, "Rus");
    Complex Z(-3, 4);
    Complex W(1, 7);
    Complex X = Z + W;
    cout << "сумма комплексных чисел: ";
    X.print();
    if (Z < W) {
        cout << "Рузультат сравнения: true" << endl;
    }
    else {
        cout << "Рузультат сравнения: false" << endl;
    }
    cout << "Унарная операция проекции на действительную ось: " << W / Z << endl;

    if (-5 < Z) {
        cout << "Рузультат сравнения с помощью дружественной функции'<' : true" << endl;
    }
    else {
        cout << "Рузультат сравнения с помощью дружественной функции'<' : false" << endl;
    }

    char c; cin >> c;
    return 0;
}