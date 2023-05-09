#include <iostream>
#include <fstream>

using namespace std;

class Exception : public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class InvalidSizeException : public Exception
{
protected:
	int rows, cols;
public:
	InvalidSizeException(const char* s, int Rows, int Cols) : Exception(s)
	{
		rows = Rows; cols = Cols;
	}
	InvalidSizeException(const InvalidSizeException& e) : Exception(e)
	{
		rows = e.rows; cols = e.cols;
	}
	virtual void print()
	{
		cout << "InvalidSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what();
	}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int row, col;
public:
	IndexOutOfBoundsException(const char* s, int Row, int Col) : Exception(s)
	{
		row = Row; col = Col;
	}
	IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e)
	{
		row = e.row; col = e.col;
	}
	virtual void print()
	{
		cout << "IndexOutOfBoundsException: " << str << "; row = " << row << "; column = " << col << "; " << what();
	}
};

class WrongSizeException : public Exception
{
protected:
	int rows, cols;
public:
	WrongSizeException(const char* s, int Rows, int Cols) : Exception(s)
	{
		rows = Rows; cols = Cols;
	}
	WrongSizeException(const WrongSizeException& e) : Exception(e)
	{
		rows = e.rows; cols = e.cols;
	}
	virtual void print()
	{
		cout << "WrongSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what();
	}
};

class NonPositiveSizeException : public WrongSizeException
{
public:
	NonPositiveSizeException(const char* s, int Rows, int Cols) : WrongSizeException(s, Rows, Cols) {}
	NonPositiveSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) {}
	virtual void print()
	{
		cout << "NonPositiveSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what();
	}
};

class TooLargeSizeException : public WrongSizeException
{
public:
	TooLargeSizeException(const char* s, int Rows, int Cols) : WrongSizeException(s, Rows, Cols) {}
	TooLargeSizeException(const NonPositiveSizeException& e) : WrongSizeException(e) {}
	virtual void print()
	{
		cout << "TooLargeSizeException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what();
	}
};

class BaseMatrix
{
protected:
	double** ptr;
	int height;
	int width;
public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		//конструктор
		if (Height <= 0 || Width <= 0)
			throw NonPositiveSizeException("Non-positive size of matrix in BaseMatrix constructor", Height, Width);
		if (Height >= 50 || Width >= 50)
			throw NonPositiveSizeException("Too large size of matrix in BaseMatrix constructor", Height, Width);
		cout << "\nBaseMatrix constructor int, int";
		height = Height;
		width = Width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];
	}

	BaseMatrix(double** arr, int w, int h)
	{

		this->height = h;
		this->width = w;

		if (height <= 0 || width <= 0)
			throw Exception("Non-positive size of matrix");

		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int j = 0; j < width; j++)
			{
				ptr[i][j] = arr[i][j];
			}
		}
	}

	BaseMatrix operator = (const BaseMatrix& obj)
	{
		if (this->height != obj.height || this->width != obj.width)
		{
			throw Exception("Matrix sizes do not match");
		}
		else
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					obj.ptr[i][j] = this->ptr[i][j];
				}
			}
		}
	}

	void RandomFill()
	{
		for (int i = 0; i < height; i++)
		{
			double* arr = new double[sizeof(width)];
			for (int j = 0; j < width; j++)
			{
				arr[j] = rand() % 100;

			}
			ptr[i] = arr;
		}
	}

	void GaussianElimination(double** A, int m, int n) {
		int i = 0, j = 0, k = 0;
		double t = 0;

		for (i = 0; i < m; i++) {
			if (A[i][j] == 0) {
				// Поиск первого ненулевого элемента в столбце
				for (k = i + 1; k < m; k++) {
					if (A[k][j] != 0) {
						// Меняем местами строки
						for (int l = 0; l < n; l++) {
							t = A[i][l];
							A[i][l] = A[k][l];
							A[k][l] = t;
						}
						break;
					}
				}
				// Если не нашли ненулевой элемент, переходим к следующему столбцу
				if (k == m) {
					j++;
					continue;
				}
			}
			// Деление первой строки на главный элемент
			t = A[i][j];
			for (int l = j; l < n; l++) {
				A[i][l] /= t;
			}
			// Вычитание первой строки из всех нижних строк
			for (k = i + 1; k < m; k++) {
				t = A[k][j];
				for (int l = j; l < n; l++) {
					A[k][l] -= t * A[i][l];
				}
			}
			j++;
		}
	}

	virtual ~BaseMatrix()
	{
		//деструктор
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
		cout << "\nBaseMatrix destructor";
	}

	void print()
	{
		//вывод
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
	}

	BaseMatrix(const BaseMatrix& M)
	{
		//конструктор копий
		height = M.height;
		width = M.width;
		ptr = new double* [height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int j = 0; j < width; j++)
				ptr[i][j] = M.ptr[i][j];
		}
	}
	double* operator[](int row)
	{
		if (row < 0 || row >= height)
			throw IndexOutOfBoundsException("Wrong index in operator[]", row, -1);
		return ptr[row];
	}
	double& operator()(int row, int column)
	{
		if (row < 0 || row >= height || column < 0 || column >= width)
			throw IndexOutOfBoundsException("Wrong index in operator()", row, column);
		return ptr[row][column];
	}

	friend ostream& operator<<(ostream& s, BaseMatrix M);
	friend istream& operator>>(istream& s, BaseMatrix& M);
};

ostream& operator<<(ostream& s, BaseMatrix M)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << M.height << " " << M.width << " ";
		for (int i = 0; i < M.height; i++)
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
	}
	else
		for (int i = 0; i < M.height; i++)
		{
			for (int j = 0; j < M.width; j++)
				s << M.ptr[i][j] << " ";
			s << "\n";
		}
	return s;
}

istream& operator>>(istream& s, BaseMatrix& M)
{
	if (typeid(s) == typeid(ifstream))
	{
		int h, w; s >> h >> w;
		if (M.height != h || M.width != w)
			throw WrongSizeException("Matrices in file and in code have got different size", h, w);
	}
	for (int i = 0; i < M.height; i++)
		for (int j = 0; j < M.width; j++)
			s >> M.ptr[i][j];
	return s;
}

class Matrix : public BaseMatrix
{
public:
	Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) { cout << "\nMatrix constructor int, int"; }
	Matrix(double** arr, int w, int h) : BaseMatrix(arr, w, h) { cout << "\nMatrix constructor double**"; }
	double operator*()
	{
		if (width != height)
			throw InvalidSizeException("Quantity of rows and columns should be equal int operator*()", height, width);
		double res = 1;
		for (int i = 0; i < height; i++)
			res *= ptr[i][width - i - 1];
		return res;
	}
	virtual ~Matrix() { cout << "\nMatrix destructor"; }
};

int main()
{
	try
	{
		//Matrix* arr = new Matrix[10];
		Matrix arr[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i](0, 0) = i;
			arr[i](0, 1) = i + 1;
			arr[i](1, 0) = i + 2;
			arr[i](1, 1) = i + 3;
		}

		BaseMatrix arr1[10];
		for (int i = 0; i < 10; i++)
		{
			arr[i](0, 0) = i;
			arr[i](0, 1) = i + 1;
			arr[i](1, 0) = i + 2;
			arr[i](1, 1) = i + 3;
			
		}
		
		
		ofstream fout("test.txt");
		if (fout)
		{
			//fout << M;
			//fout << "10\n";
			for (int i = 0; i < 10; i++)
			{
				if (i != 9)
					fout << arr[i] << "\n";
				else
					fout << arr[i];
			}
			fout.close();
		}
		ifstream fin("test.txt");
		if (fin)
		{
			//int n; fin >> n;
			//for (int i = 0; i < n; i++)
			while (!fin.eof())
			{
				try
				{
					Matrix M1;
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

	/*try
	{
		Matrix M(2, 3); M(0, 0) = 1; M(0, 1) = 2; M(1, 0) = 3; M(1, 1) = 4; M(1, 2) = 100; M(0, 2) = 5;
		cout << "\n*M = " << *M;
		cout << "\n"; M.print();
	}
	catch (InvalidSizeException e)
	{
		cout << "\nCaught exception: "; e.print();
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nCaught exception: "; e.print();
	}*/

	char c; cin >> c;
	return 0;
}