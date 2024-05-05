

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
class OnlyOneElementException :public Exception {
protected:
    int rows, cols;
public:
    OnlyOneElementException(const char* s, int Rows, int Cols) :Exception(s) {}
    OnlyOneElementException(const OnlyOneElementException& e) : Exception(e)
    {
        rows = e.rows; cols = e.cols;
    }
    virtual void print()
    {
        cout << "OnlyOneElementException: " << str << "; rows = " << rows << "; columns = " << cols << "; " << what();
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
template <typename T>
class BaseMatrix
{
protected:
    T** ptr;
    int height;
    int width;
public:
    template <typename T>
    friend istream& operator>>(istream& s, BaseMatrix<T>& M);
    template <typename T>
    friend ostream& operator<<(ostream& s, BaseMatrix<T> M);
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
        ptr = new T * [height];
        for (int i = 0; i < height; i++)
            ptr[i] = new T[width];
    }

    BaseMatrix(T** arr, int w, int h)
    {
        cout << "\nBaseMatrix constructor double**";
    }

    BaseMatrix<typename T> operator=(BaseMatrix a)
    {
        for (int i = 0; i < a.height; i++)
            for (int j = 0; j < a.width; j++)
                ptr[i][j] = a[i][j];
        return *this;
    }

    virtual ~BaseMatrix()
    {
        //деструктор
        if (ptr != NULL)
        {

            
         
            
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




    BaseMatrix<T>(const BaseMatrix<T>& M)
    {
        //конструктор копий
        height = M.height;
        width = M.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }
    }
    T* operator[](int row)
    {
        if (row < 0 || row >= height)
            throw IndexOutOfBoundsException("Wrong index in operator[]", row, -1);
        return ptr[row];
    }
    T& operator()(int row, int column)
    {
        if (row < 0 || row >= height || column < 0 || column >= width)
            throw IndexOutOfBoundsException("Wrong index in operator()", row, column);
        return ptr[row][column];
    }

};
template <typename T>
ostream& operator<<(ostream& s, BaseMatrix<T> M)
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
template <typename T>
istream& operator>>(istream& s, BaseMatrix<T>& M)
{
    if (typeid(s) == typeid(ifstream))
    {
        int h, w; s >> h >> w;
        if (M.height != h || M.width != w) {
            
            for (int i = 0; i < M.height; i++)
                delete[] M.ptr[i];
            delete[]  M.ptr;
            M.ptr = new T*  [h];
            for (int i = 0; i < w; i++)
                M.ptr[i] = new T [w];
                M.height = h;
            M.width = w;
        }
    }
    for (int i = 0; i < M.height; i++)
        for (int j = 0; j < M.width; j++)
            s >> M.ptr[i][j];
    return s;
}
template <typename T>
class Matrix : public BaseMatrix<T>
{
public:
    Matrix<T>(int Height = 2, int Width = 2) : BaseMatrix<T>(Height, Width) { cout << "\nMatrix constructor int, int"; }
    Matrix<T>(T arr, int w, int h) : BaseMatrix<T>(arr, w, h) { cout << "\nMatrix constructor double**"; }
    using BaseMatrix<T>::width;
    using BaseMatrix<T>::height;
    using BaseMatrix<T>::ptr;
    double operator*()
    {
        if (width != height)
            throw InvalidSizeException("Quantity of rows and columns should be equal int operator*()", height, width);
        double res = 1;
        for (int i = 0; i < height; i++)
            res *= ptr[i][width - i - 1];
        return res;
    }

    Matrix newVector() {
        Matrix a;
        if (width == 1 || height == 1)
            throw OnlyOneElementException("Quantity of rows and height should be more than one", height, width);
        for (int i = 0; i < height; i++) {
            int c = 0;
            for (int j = 0; j < width; j++)
                if (ptr[i][j] == 0 && ptr[i][j + 1] == 0) {
                    a.ptr[i][c] = 0;
                    j++;
                    c++;
                }
                else {
                    a.ptr[i][c] = ptr[i][j];
                    c++;
                }

        }
        return a;
    }
    virtual ~Matrix() { cout << "\nMatrix destructor"; }
};

int main()
{
    try
    {
        // Matrix<int>* arr = new Matrix<int>[10];
        Matrix<int> arr[10];
        for (int i = 0; i < 10; i++)
        {
            arr[i](0, 0) = i;
            arr[i](0, 1) = i + 1;
            arr[i](1, 0) = i + 2;
            arr[i](1, 1) = i + 3;
        }
        Matrix<int> arr2[10];
        Matrix<int> arr3[10];
        cout << "Arr3";
        for (int i = 0; i < 10; i++)
        {
            arr2[i](0, 0) = 1;
            arr2[i](0, 1) = 0;
            arr2[i](1, 0) = 1;
            arr2[i](1, 1) = 0;
            arr3[i] = arr2->newVector();
        }
        for (int i = 0; i < 10; i++)
        {
            cout << arr[i]<<" ";
        }
        ifstream fins("in.txt");
        if (fins)
        {
            int a,j,k; fins >> a;
            for (int i = 0; i < a; i++) {
                // try
                 //{

                Matrix<double> M1;
                fins >> M1;
                cout << "\nAfter reading file in.txt:\n" << M1;
            }
                //}
                //catch (exception e) { cout << "Caught exception: " << e.what(); }
            
            fins.close();
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
                    Matrix<double> M1;
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