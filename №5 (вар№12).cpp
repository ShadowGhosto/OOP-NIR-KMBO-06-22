#include <iostream>
#include <fstream>
#include <typeinfo>

using namespace std;

class Exception : public exception {
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception(const char* s) {
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception() {
		delete[] str;
	}

	virtual void print() { cout << "Exception: " << str << "; " << what(); }
};

class InvalidSizeException : public Exception {
protected:
	int rows, cols;
public:
	InvalidSizeException(const char* s, int Rows, int Cols) : Exception(s) { rows = Rows; cols = Cols; }
	InvalidSizeException(const InvalidSizeException& e) : Exception(e) { rows = e.rows; cols = e.cols; }
	virtual void print() { cout << "InvalidSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what(); }
};

class IndexOutOfBoundsException : public Exception {
protected:
	int row, col;
public:
	IndexOutOfBoundsException(const char* s, int Row, int Col) : Exception(s) { row = Row; col = Col; }
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { row = e.row; col = e.col; }
	virtual void print() { cout << "IndexOutOfBoundsException: " << str << "; row = " << row << "; column = " << col << "; " << what(); }
};

class WrongSizeException : public Exception {
protected:
	int rows, cols;
public:
	WrongSizeException(const char* s, int Rows, int Cols) : Exception(s) { rows = Rows; cols = Cols; }
	WrongSizeException(const WrongSizeException& e) : Exception(e) { rows = e.rows; cols = e.cols; }
	virtual void print() { cout << "WrongSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what(); }
};

class NonPositiveSizeException : public WrongSizeException {
public:
	NonPositiveSizeException(const char* s, int Rows, int Cols) : WrongSizeException(s, Rows, Cols) {}
	NonPositiveSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) {}
	virtual void print() { cout << "NonPositiveSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what(); }
};

class TooLargeSizeException : public WrongSizeException {
public:
	TooLargeSizeException(const char* s, int Rows, int Cols) : WrongSizeException(s, Rows, Cols) {}
	TooLargeSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) {}
	virtual void print() { cout << "TooLargeSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what(); }
};

class GaussianEliminationException : public Exception {
public:
	GaussianEliminationException(const char* s) : Exception(s) {}
	GaussianEliminationException(const GaussianEliminationException& e) : Exception(e) {}
	virtual void print() { cout << "GaussianEliminationException: " << str << "; " << what(); }
};


template<class T>
class BaseMatrix {
protected:
	T** ptr;
	int height;
	int width;
public:

BaseMatrix(int Height = 2, int Width = 2) {
	if (Height <= 0 || Width <= 0) { throw NonPositiveSizeException("Non-positive size of matrix in BaseMatrix constructor", Height, Width); }
	if (Height >= 50 || Width >= 50) { throw NonPositiveSizeException("Too large size of matrix in BaseMatrix constructor", Height, Width); }
	cout << "\nBaseMatrix constructor int, int";
	height = Height;
	width = Width;
	ptr = new T*[height];
	for (int i = 0; i < height; i++) {
		ptr[i] = new T[width];
	}
}

BaseMatrix<typename T> operator=(BaseMatrix A) {
	for (int i = 0; i < A.height; i++) {
		for (int j = 0; j < A.width; j++) {
			ptr[i][j] = A[i][j];
		}
	}
	return *this;
}

BaseMatrix(T** arr, int w, int h) {

	this->height = h;
	this->width = w;

	if (height <= 0 || width <= 0)
		throw Exception("Non-positive size of matrix");

	ptr = new T* [height];
	for (int i = 0; i < height; i++) {
		ptr[i] = new T[width];
		for (int j = 0; j < width; j++) {
			ptr[i][j] = arr[i][j];
		}
	}
}



BaseMatrix<T> GaussianElimination() {
	int i = 0, j = 0, k = 0;
	T t;

	for (i = 0; i < height; i++) {
		if (ptr[i][j] == 0) {
			// Найдите первый ненулевой элемент в столбце
			for (k = i + 1; k < height; k++) {
				if (ptr[k][j] != 0) {
					// Поменять местами строки
					for (int l = 0; l < width; l++) {
						t = ptr[i][l];
						ptr[i][l] = ptr[k][l];
						ptr[k][l] = t;
					}
					break;
				}
			}
			//Если ненулевой элемент не найден, перейдем к следующему столбцу
			if (k == height) {
				j++;
				if (j >= width) { throw GaussianEliminationException("Matrix is singular"); }
				continue;
			}
		}
		// Разделим первую строку на ведущий элемент
		t = ptr[i][j];
		for (int l = j; l < width; l++) {
			ptr[i][l] /= t;
		}
		// Вычтитание первой строки из всех нижних строк
		for (k = i + 1; k < height; k++) {
			t = ptr[k][j];
			for (int l = j; l < width; l++) {
				ptr[k][l] -= t * ptr[i][l];
			}
		}
		j++;
	}
	return *this;
}


virtual ~BaseMatrix() {
	//деструктор
	if (ptr != NULL) {
		for (int i = 0; i < height; i++)
			delete[] ptr[i];
		delete[] ptr;
		ptr = NULL;
	}
	cout << "\nBaseMatrix destructor";
}

void print() {
	//вывод
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			cout << ptr[i][j] << " "<< "\n";
	}
}

BaseMatrix<T>(const BaseMatrix<T>& M) {
	//конструктор копий
	height = M.height;
	width = M.width;
	ptr = new T*[height];
	for (int i = 0; i < height; i++) {
		ptr[i] = new T[width];
		for (int j = 0; j < width; j++) {
			ptr[i][j] = M.ptr[i][j];
		}
	}
}
T* operator[](int row) {
	if (row < 0 || row >= height) { throw IndexOutOfBoundsException("Wrong index in operator[]", row, -1); }
	return ptr[row];
}
T& operator()(int row, int column) {
	if (row < 0 || row >= height || column < 0 || column >= width) { throw IndexOutOfBoundsException("Wrong index in operator()", row, column); }
	return ptr[row][column];
}

template <typename T>
friend istream& operator>>(istream& s, BaseMatrix<T>& M);
template <typename T>
friend ostream& operator<<(ostream& s, BaseMatrix<T> M);
};

template<class T>
class Matrix : public BaseMatrix<T> {
public:
Matrix<T>(int Height = 2, int Width = 2) : BaseMatrix<T>(Height, Width) { cout << "\nMatrix constructor int, int"; }
Matrix<T>(T arr, int w, int h) : BaseMatrix<T>(arr, w, h) { cout << "\nMatrix constructor double**"; }
using BaseMatrix<T>::width;
using BaseMatrix<T>::height;
using BaseMatrix<T>::ptr;

T operator*() {
	if (width != height) { throw InvalidSizeException("Quantity of rows and columns should be equal int operator*()", height, width); }

	double res = 1;
	for (int i = 0; i < height; i++) {
		res *= ptr[i][width - i - 1];
	}
	return res;
}

virtual ~Matrix() { cout << "\nMatrix destructor"; }

void RandomFill() {
	for (int i = 0; i < height; i++) {
		T* arr = new T[sizeof(width)];
		for (int j = 0; j < width; j++) {
			arr[j] = rand() % 100;
		}
		ptr[i] = arr;
	}
}
};



template<class T>
ostream& operator<<(ostream& s, BaseMatrix<T> M) {
	if (typeid(s) == typeid(ofstream)) {
		s << M.height << " " << M.width << " ";
		for (int i = 0; i < M.height; i++) {
			for (int j = 0; j < M.width; j++) {
				s << M.ptr[i][j] << " ";
			}
		}
	}
	else {
		for (int i = 0; i < M.height; i++) {
			for (int j = 0; j < M.width; j++) {
				s << M.ptr[i][j] << " ";
			}
			s << "\n";
		}
	}
	return s;
}

template<class T>
istream& operator>>(istream& s, BaseMatrix<T>& M) {
	if (typeid(s) == typeid(ifstream)) {
		int h, w; s >> h >> w;
		if (M.height != h || M.width != w) { throw WrongSizeException("Matrices in file and in code have got different size", h, w); }
	}
	for (int i = 0; i < M.height; i++) {
		for (int j = 0; j < M.width; j++) {
			s >> M.ptr[i][j];
		}
	}
	return s;
}



int main() {

	try {

		//Matrix* arr = new Matrix[10];
		Matrix<int> arr[10];
		for (int i = 0; i < 10; i++) {
			arr[i](0, 0) = i;
			arr[i](0, 1) = i + 1;
			arr[i](1, 0) = i + 2;
			arr[i](1, 1) = i + 3;
		}

		Matrix<int> matrix(3, 3);
		matrix.RandomFill();
		cout << "\nRandomFill\n" << matrix;

		matrix.GaussianElimination();
		cout << "\nGaussianElimination\n" << matrix;

		Matrix<int> matrix1(4, 4);
		matrix1.RandomFill();
		cout << "\nRandomFill1\n" << matrix1;

		matrix1.GaussianElimination();
		cout << "\nGaussianElimination1\n" << matrix1;

        ofstream fout("test1.txt");
        if (fout) {
            //fout << M;
            //fout << "10\n";
            for (int i = 0; i < 10; i++) {
                if (i != 9)
                    fout << arr[i] << "\n";
                else
                    fout << arr[i];
            }
            fout.close();
        }
       
        ifstream fin("test.txt");
        if (fin) {
            //int n; fin >> n;
            //for (int i = 0; i < n; i++)
            while (!fin.eof()) {
                try {
                    Matrix<int> M1;
                    fin >> M1;
                    cout << "\nAfter reading file:\n" << M1;
                }
                catch (exception e) { cout << "Caught exception: " << e.what(); }
            }
            fin.close();
        }
       //delete[] arr;
	}

	catch (InvalidSizeException e)
	{
		cout << "\nCaught exception: "; e.print();
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nCaught exception: "; e.print();
	}
	catch (WrongSizeException e)
	{
		cout << "\nCaught WrongSizeException: "; e.print();
	}
	catch (Exception e)
	{
		cout << "\nCaught exception: "; e.print();
	}
	catch (exception e)
	{
		cout << "\nCaught exception: "; cout << e.what();
	}
	catch (GaussianEliminationException e)
	{
		cout << "\nCaught GaussianEliminationException: "; cout << e.what();
	}

	char c; cin >> c;
	return 0;
}
