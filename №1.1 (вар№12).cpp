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
            cout << "\n" << real << "\n";
            return;
        }
        if (real == 0)
        {
            cout << "\n" << image << "i\n";
            return;
        }
        if (image > 0)
            cout << "\n" << real << " + " << image << "i\n";
        else
            cout << "\n" << real << " - " << -image << "i\n";
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
    bool operator<(Complex F) {
        if (real == F.real) {
            if (image == F.image) {
                return true;
            }
        }
        return false;
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
};
     


int main()
{
    setlocale(LC_ALL, "Rus");
    Complex Z(-3, 4);
    Complex W(1, 7);
    Complex X = Z + W;
    cout << "ñóììà êîìïëåêñíûõ ÷èñåë: " << endl;
    X.print();
    if (Z < W) {
        cout << "Ðåçóëüòàò ñðàâíåíèÿ: true" << endl;
    }
    else {
        cout << "Ðåçóëüòàò ñðàâíåíèÿ: false" << endl;
    }
    cout << "Àëãåáðàè÷åñêàÿ îïåðàöèÿ ïðîåêöèè íà äåéñòâèòåëüíóþ îñü: "<< W / Z << endl;

    char c; cin >> c;
    return 0;
}
