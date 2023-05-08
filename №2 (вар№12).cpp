#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;
class MyArrayParent {
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:

	//конструкторы и деструктор
	MyArrayParent(int Dimension = 100) {
		cout << "\nMyArray constructor";
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}

	MyArrayParent(const MyArrayParent& obj) {
		cout << "\nMyArray copy constructor";
		this->capacity = obj.capacity;
		this->count = obj.count;
		this->ptr = new double[sizeof(obj.ptr)];
		for (int i = 0; i < sizeof(obj.ptr); i++) {
			this->ptr[i] = obj.ptr[i];
		}
	}

	MyArrayParent(double* arr, int len) {
		cout << "\nMyArray constructor";
		this->ptr = new double[sizeof(len)];
		this->capacity = len;
		for (int i = 0; i < len; i++) {
			if (arr[i] != NULL) {
				this->count++;
				this->ptr[i] = arr[i];
			}
		}
	}

	//деструктор
	~MyArrayParent() {
		cout << "\nMyArray destructor";
		if (ptr != NULL) {
			delete[] ptr;
			ptr = NULL;
		}
	}

	//обращение к полям
	int Capacity() { return capacity; }
	int Size() { return count; }

	double GetComponent(int index) {
		if (index >= 0 && index < count) {
			return ptr[index];
		}
		return -1;
	}

	void SetComponent(int index, double value) {
		if (index >= 0 && index < count)
			ptr[index] = value;
	}

	//добавление в конец нового значения
	void push(double value) {
		if (count < capacity) {
			ptr[count] = value;
			count++;
		}
	}

	//удаление элемента с конца
	void RemoveLastValue() {
		if (count >= 0)
			count--;
	}

	//поиск элемента, добавил поиск элемента с конца
	int IndexOf(int value, bool bFindFromStart = true) {
		if (bFindFromStart) {
			for (int i = 0; i < count; i++) {
				if (ptr[i] == value) {
					return i;
				}
			}
		}
		else {
			for (int i = count - 1; i >= 0; i--) {
				if (ptr[i] == value) {
					return i;
				}
			}
		}
		return -1;
	}

	//перегрузка оператора []
	double& operator[](int index) {
		return ptr[index];
	}

	//исправил ошибку с освобождением старого участка памяти
	MyArrayParent& operator=(const MyArrayParent& obj) {
		if (this != &obj) {
			delete[] ptr;
		}
		cout << endl << "operator = ";
		this->capacity = obj.capacity;
		this->count = obj.count;
		this->ptr = new double[sizeof(obj.ptr)];
		for (int i = 0; i < sizeof(obj.ptr); i++) {
			this->ptr[i] = obj.ptr[i];
		}
		return *this;
	}

	void print() {
		cout << " MyArr, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++) {
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}
};

class MyArrayChild : public MyArrayParent {
public:

	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	void RemoveAt(int index = -1) {
		if (index == -1) {
			return;
		}
		if (index >= count) {
			return;
		}

		for (int i = index; i < count - 1; i++) {
			ptr[i] = ptr[i + 1];
		}
		count = count - 1;
	}

	void InsertAt(double value, int index = -1) {
		if (index == -1 || index == count)
			push(value);
		if (index<0 || index>count) return;

		for (int i = count; i > index; i--)
			ptr[i] = ptr[i - 1];

		ptr[index] = value;
		count++;
	}

	MyArrayChild ABCD(int* arr, int len) {
		MyArrayChild abcd;
		abcd.ptr = new double[sizeof(len)];
		abcd.capacity = len;
		abcd.count = 0;
		for (int i = 0; i < len; i++) {
			if (arr[i] >= 1000 && arr[i] <= 9999) {
				int a = arr[i] / 1000;
				int b = (arr[i] / 100) % 10;
				int c = (arr[i] / 10) % 10;
				int d = arr[i] % 10;
				if ((a + c) % 3 == 0 && (b + d) % 7 == 0) {
					abcd.ptr[abcd.count] = arr[i];
					abcd.count++;
				}
			}
		}
		return abcd;
	}

};

class MySortedArray : public  MyArrayChild {
protected:

	int binary_search(double value, int left, int right) {
		int middle = (left + right) / 2;

		if (ptr[middle] == value) {
			return middle;
		}
		if (count == 1) {
			return -1;
		}
		if (left + 1 == right) {
			if (ptr[right] == value) return right;
			return -1;
		}
		if (ptr[middle] > value) {
			return binary_search(value, left, middle);
		}
		if (ptr[middle] < value) {
			return binary_search(value, middle, right);
		}
	}
public:

	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor"; }

	MySortedArray(double* arr, int len) : MyArrayChild(arr, len) { cout << "\nMySortedArray constructor"; sort(ptr, ptr + count); }

	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }
	
	//функция выделения подпоследовательности Subsequence()
	MySortedArray Subsequence(int startIndex, int endIndex) {
		int length = endIndex - startIndex + 1;
		double* subsequenceArr = new double[length];
		for (int i = startIndex; i <= endIndex; i++) {
			subsequenceArr[i - startIndex] = ptr[i];
		}
		MySortedArray subsequence(subsequenceArr, length);
		return subsequence;
	}

	MySortedArray operator+(const MySortedArray& other) {
		MySortedArray result(capacity + other.capacity);
		for (int i = 0; i < count; i++) {
			result.push(ptr[i]);
		}
		for (int i = 0; i < other.count; i++) {
			result.push(other.ptr[i]);
		}
		return result;
	}

	// переделал функцию push
	void push(double value) {
		if (count == 0) {
			MyArrayParent::push(value);
			return;
		}
		int index = binary_search(value, 0, count - 1);
		InsertAt(value, index);
	}

	int IndexOf(double value, bool bFindFromStart = true) {
		int bs = (binary_search(value, 0, count - 1));
		if (count > 1 && (ptr[bs] == value)) {
			return bs;
		}
		else {
			return -1;
		}
	}
};

int main() {

	if (true) {
		MyArrayParent arr;
		int i = 0;
		for (int i = 0; i < 10; i++) {
			arr.push(i + 1);
		}
		arr.print();


		MyArrayParent Original;
		Original.push(50511);
		cout << "\n";
		Original.print();
		MyArrayParent Copy{ Original };
		cout << "\n";
		Copy.print();

		//реализация функции выделения подпоследовательности Subsequence()
		MySortedArray arr1(10);
		for (int j = 0; j < 10; j++) {
			arr1.push(j + 1);
		}
		MySortedArray sub = arr1.Subsequence(2, 5);
		cout << "\n"<< " the work of the operator Subsequence:";
		sub.print();

		//реализация перегрузки оператора +
		MySortedArray A1(3);
		A1.push(1.0);
		A1.push(2.0);
		A1.push(3.0);
		MySortedArray A2(2);
		A2.push(4.0);
		A2.push(5.0);
		MySortedArray A3 = A1 + A2;
		cout << "\n" << " the work of the operator +:";
		A3.print();
	}

	if (true) {
		MyArrayChild B;
		const int size_arr = 100;
		int arr[size_arr];
		for (int i = 0; i < size_arr; i++) {
			arr[i] = rand() % 9000 + 1000;;
		}
		MyArrayChild A = B.ABCD(arr, size_arr);
		cout << "\n";
		A.print();


		//реализация бинарного поиска
		MySortedArray arr3(100);
		for (int i = 0; i < 10; i++) {
			arr3.push(i + 1);
		}

		cout << "\n";
		arr3.print();
		int index = arr3.IndexOf(6, false);
		cout << "\n Result of binary_search: " << index << endl;


		arr3.push(3.4);
		arr3.push(0.4);
		arr3.push(4.1);
		arr3.print();
		cout << "\n Result of binary_search with push elements: " << arr3.IndexOf(8, false) << endl;

		return 0;
	}

	char c; cin >> c;
};
