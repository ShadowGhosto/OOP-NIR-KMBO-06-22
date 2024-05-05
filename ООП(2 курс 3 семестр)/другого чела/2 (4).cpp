#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Book {
private:
    string authorLastName;
    string authorFirstName;
    string title;
    int publicationYear;
    string publisherName;
    int pageCount;

    int tirage;

public:
    enum EditionType { Electronic, Paper, Audio };
    EditionType edition;
    // Constructors
    Book(string lastName, string firstName, string bookTitle, int year, string publisher, int pages, EditionType ed, int copies)
        : authorLastName(lastName), authorFirstName(firstName), title(bookTitle),
        publicationYear(year), publisherName(publisher), pageCount(pages), edition(ed), tirage(copies) {}

    Book() : authorLastName(""), authorFirstName(""), title(""), publicationYear(0),
        publisherName(""), pageCount(0), edition(Electronic), tirage(0) {}

    // Getters
    string getAuthorLastName() const { return authorLastName; }
    string getAuthorFirstName() const { return authorFirstName; }
    string getTitle() const { return title; }
    int getPublicationYear() const { return publicationYear; }
    string getPublisherName() const { return publisherName; }
    int getPageCount() const { return pageCount; }
    EditionType getEdition() const { return edition; }
    int getTirage() const { return tirage; }

    // Setters
    void setAuthorLastName(string lastName) { authorLastName = lastName; }
    void setAuthorFirstName(string firstName) { authorFirstName = firstName; }
    void setTitle(string bookTitle) { title = bookTitle; }
    void setPublicationYear(int year) { publicationYear = year; }
    void setPublisherName(string publisher) { publisherName = publisher; }
    void setPageCount(int pages) { pageCount = pages; }
    void setEdition(EditionType ed) { edition = ed; }
    void setTirage(int copies) { tirage = copies; }

    // Overloaded operators
    bool operator<(const Book& other) const { return tirage < other.tirage; }
    bool operator>(const Book& other) const { return tirage > other.tirage; }
    bool operator<(int tirageValue) const { return tirage < tirageValue; }
    bool operator==(int tirageValue) const { return tirage == tirageValue; }
    bool operator>(int tirageValue) const { return tirage > tirageValue; }

    friend ostream& operator<<(ostream& os, const Book& book);
};

ostream& operator<<(ostream& os, const Book& book) {
    os << "Author: " << book.getAuthorFirstName() << " " << book.getAuthorLastName()
        << ", Title: " << book.getTitle() << ", Publication Year: " << book.getPublicationYear()
        << ", Publisher: " << book.getPublisherName() << ", Page Count: " << book.getPageCount()
        << ", Edition: " << book.getEdition() << ", Tirage: " << book.getTirage();
    return os;
}
bool operator>(const Book& lhs, const Book& rhs)
{
    return lhs.title > rhs.title;
}


template <class T>
class Node {
protected:
    T data;
    Node* left;
    Node* right;
    Node* parent;
    int height;

public:
    virtual void setData(T& d) { data = d; }
    virtual T& getData() { return data; }
    int getHeight() { return height; }
    virtual Node* getLeft() { return left; }
    virtual Node* getRight() { return right; }
    virtual Node* getParent() { return parent; }
    virtual void setLeft(Node* N) { left = N; }
    virtual void setRight(Node* N) { right = N; }
    virtual void setParent(Node* N) { parent = N; }
    Node<T>() {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = T();
        height = 1;
    }
    Node<T>(T& n) {
        data = n;
        left = right = parent = NULL;
        height = 1;
    }

    void print() {
        cout << "\n" << data;
    }

    template <class U>
    friend ostream& operator<<(ostream& stream, const Node<U>& N);
};

template<class T>
ostream& operator<<(ostream& stream, const Node<T>& N) {
    stream << "\nNode data: " << N.data << ", height: " << N.height;
    return stream;
}

// Дерево
template <class T>
class Tree {
protected:
    Node<T>* root;

public:
    // Конструктор
    Tree<T>() {
        root = nullptr;
    }

    // Добавление узла
    void Add(T& book) {
        Node<T>* N = new Node<T>(book);
        root = Add_R(N, root);
    }

    //доступ к корневому элементу
    virtual Node<T>* getRoot() { return root; }
    //конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
    //рекуррентная функция добавления узла. Устроена аналогично, 	но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<T>* Add_R(Node<T>* N)
    {
        return Add_R(N, root);
    }
    virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
    {
        if (N == nullptr)
            return Current;

        if (Current == nullptr)
        {
            return N;
        }

        if (N->getData() < Current->getData())
        {
            Current->setLeft(Add_R(N, Current->getLeft()));
            Current->getLeft()->setParent(Current);
        }
        else if (N->getData() > Current->getData())
        {
            Current->setRight(Add_R(N, Current->getRight()));
            Current->getRight()->setParent(Current);
        }

        return Current;
    }

    //функция для добавления числа. Делаем новый узел с этими 	данными и вызываем нужную функцию добавления в дерево
    virtual Node<T>* Min(Node<T>* Current = NULL)
    {
        //минимум - это самый "левый" узел. Идём по дереву всегда влево
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        while (Current->getLeft() != NULL)
            Current = Current->getLeft();
        return Current;
    }

    virtual Node<T>* Max(Node<T>* Current = NULL)
    {
        //минимум - это самый "правый" узел. Идём по дереву всегда вправо
        if (root == NULL) return NULL;
        if (Current == NULL)
            Current = root;
        while (Current->getRight() != NULL)
            Current = Current->getRight();
        return Current;
    }

    //поиск узла в дереве. Второй параметр - в каком поддереве 	искать, первый - что искать
    virtual Node<T>* Find(int data, Node<T>* Current)
    {
        //база рекурсии
        if (Current == NULL) return NULL;
        if (Current->getData() == data) return Current;
        //рекурсивный вызов
        if (Current->getData() > data) return Find(data, Current->getLeft());
        if (Current->getData() < data) return Find(data, Current->getRight());
    }

    //три обхода дерева
    virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->getLeft() != NULL)
            PreOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PreOrder(N->getRight(), f);
    }

    //InOrder-обход даст отсортированную последовательность
    virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
    {
        if (N != NULL && N->getLeft() != NULL)
            InOrder(N->getLeft(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->getRight() != NULL)
            InOrder(N->getRight(), f);
    }

    virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
    {
        if (N != NULL && N->getLeft() != NULL)
            PostOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PostOrder(N->getRight(), f);
        if (N != NULL)
            f(N);
    }

    // Функция для поиска узла по ключу
    Node<T>* FindByKey(string key) {
        return FindByKey_R(key, root);
    }

    // Функция для поиска узла по значению
    Node<T>* FindByValue(int value) {
        return FindByValue_R(value, root);
    }

private:
    // Рекурсивная функция для поиска узла по ключу
    Node<T>* FindByKey_R(string key, Node<T>* current) {
        if (current == nullptr) {
            return nullptr; // Узел не найден
        }

        if (key == current->getData().title) {
            return current; // Узел найден
        }

        if (key < current->getData().title) {
            return FindByKey_R(key, current->getLeft()); // Идем влево
        }
        else {
            return FindByKey_R(key, current->getRight()); // Идем вправо
        }
    }

    // Рекурсивная функция для поиска узла по значению
    Node<T>* FindByValue_R(int value, Node<T>* current) {
        if (current == nullptr) {
            return nullptr; // Узел не найден
        }

        if (value == current->getData().tirage) {
            return current; // Узел найден
        }

        Node<T>* leftResult = FindByValue_R(value, current->getLeft());
        if (leftResult != nullptr) {
            return leftResult; // Узел найден в левом поддереве
        }

        return FindByValue_R(value, current->getRight()); // Идем вправо
    }
};

// Функция для вывода информации о книге
void printBook(Node<Book>* N) {
    cout << "Author: " << N->getData().authorLastName << " " << N->getData().authorFirstName << endl;
    cout << "Title: " << N->getData().title << endl;
    cout << "Publication Year: " << N->getData().publicationYear << endl;
    cout << "Publisher: " << N->getData().publisherName << endl;
    cout << "Page Count: " << N->getData().pageCount << endl;
    cout << "Edition: " << N->getData().edition << endl;
    cout << "Tirage: " << N->getData().tirage << endl;
}

template <class T>
class MultiTree : public Tree<T> {
public:
    using Tree<T>::Add; // Импортируем метод Add из базового класса

    const vector<T>& operator[](const std::string& key) {
        Node<T>* found = this->FindByKey(key);
        if (found != nullptr) {
            return found->getData();
        }
        else {
            static std::vector<T> emptyVector; // Возвращаем пустой вектор, если ключ не найден
            return emptyVector;
        }
    }
};

int main() {
    Tree<Book> T;
    // Создаем объекты Book и добавляем их в дерево
    Book book1("Doe", "John", "Introduction to C++", 2020, "Publisher A", 300, Book::Paper, 1000);
    Book book2("Smith", "Jane", "Data Structures", 2019, "Publisher B", 400, Book::Electronic, 1500);
    Book book3("Brown", "Alice", "Algorithms", 2022, "Publisher C", 350, Book::Paper, 1200);

    T.Add(book1);
    T.Add(book2);
    T.Add(book3);

    // Поиск по ключу
    Node<Book>* foundByKey = T.FindByKey("Data Structures");
    if (foundByKey != nullptr) {
        cout << "Found by key: " << foundByKey->getData().title << endl;
    }
    else {
        cout << "Not found by key" << endl;
    }

    // Поиск по значению
    Node<Book>* foundByValue = T.FindByValue(1200);
    if (foundByValue != nullptr) {
        cout << "Found by value: " << foundByValue->getData().title << endl;
    }
    else {
        cout << "Not found by value" << endl;
    }

    // Вывод информации о книгах в дереве с помощью InOrder обхода
    cout << "Inorder Traversal:" << endl;
    void (*f_ptr)(Node<Book>*);
    f_ptr = printBook;
    T.InOrder(T.getRoot(), f_ptr);
    MultiTree<Book> M;
    Book book5("Doe", "John", "Introduction to C++", 2020, "Publisher A", 300, Book::Paper, 1000);
    Book book6("Smith", "Jane", "Data Structures", 2019, "Publisher B", 400, Book::Electronic, 1500);

    M.Add(book5);
    M.Add(book6);

    return 0;
}



