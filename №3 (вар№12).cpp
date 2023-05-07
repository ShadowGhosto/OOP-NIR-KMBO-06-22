#include <iostream>
using namespace std;

class A1 {
protected:
	int a1;
public:
	A1(int input = 0) : a1(input) {
		cout << "A1 constructor" << endl;
	}
	virtual void print() {
		cout << "variable of A1 class" << endl;
	}
	virtual void show() {
		cout << "a1=" << a1 << "\n" << endl;
	}
};

class B1 : virtual public A1 {
protected:
	int b1;
public:
	B1(int input1, int input2) : A1(input1), b1(input2) {
		cout << "B1 constructor" << endl;
	}
	void print() override {
		cout << "variable of B1 class" << endl;
	}
	void show() override {
		cout << "a1=" << a1 << ", b1=" << b1 << "\n" << endl;
	}
};

class B2 : virtual public A1 {
protected:
	int b2;
public:
	B2(int input1, int input2) : A1(input1), b2(input2) {
		cout << "B2 constructor" << endl;
	}
	void print() override {
		cout << "variable of B2 class" << endl;
	}
	void show() override {
		cout << "a1=" << a1 << ", b2=" << b2 << "\n" << endl;
	}
};

class B3 : virtual public A1 {
protected:
	int b3;
public:
	B3(int input1, int input2) : A1(input1), b3(input2) {
		cout << "B3 constructor" << endl;
	}
	void print() override {
		cout << "variable of B3 class" << endl;
	}
	void show() override {
		cout << "a1=" << a1 << ", b3=" << b3 << "\n" << endl;
	}
};

class B4 : virtual public A1 {
protected:
	int b4;
public:
	B4(int input1, int input2) : A1(input1), b4(input2) {
		cout << "B4 constructor" << endl;
	}
	void print() override {
		cout << "variable of B4 class" << endl;
	}
	void show() override {
		cout << "a1=" << a1 << ", b4=" << b4 << "\n" << endl;
	}
};

class C1 : virtual public B1, virtual public B2, virtual public B3, virtual public B4 {
protected:
	int c1;
public:
	C1(int input1, int input2, int input3, int input4, int input5, int input6) : B1(input1, input2), B2(input1, input3), B3(input1, input4), B4(input1, input5), c1(input6) {
		cout << "C1 constructor" << endl;
	}
	void print() override {
		cout << "variable of C1 class" << endl;
	}
	void show() override {
		cout << "b1= " << b1 << ", b2= " << b2 << ", b3= " << b3 << ", b4= " << b4 << ", c1= " << c1 << "\n" << endl;
	}
};


class C2 : virtual public B1, virtual public B2, virtual public B3, virtual public B4 {
protected:
	int c2;
public:
	C2(int input1, int input2, int input3, int input4, int input5, int input6) : B1(input1, input2), B2(input1, input3), B3(input1, input4), B4(input1, input5), c2(input6) {
		cout << "C2 constructor" << endl;
	}
	void print() override {
		cout << "variable of C2 class" << endl;
	}
	void show() override {
		cout << "b1= " << b1 << ", b2= " << b2 << ", b3= " << b3 << ", b4= " << b4 << ", c2= " << c2 << endl;
	}
};

int main() {

	if (true) {
		A1 ex1(1);
		ex1.print();
		ex1.show();

		B1 ex2(22, 33);
		ex2.print();
		ex2.show();

		B2 ex3(444, 555);
		ex3.print();
		ex3.show();

		C1 ex4(-1, -2, -3, -4, -5, -6);
		ex4.print();
		ex4.show();

		C2 ex5(11, 22, 33, 44, 55, 66);
		ex5.print();
		ex5.show();
	}
}