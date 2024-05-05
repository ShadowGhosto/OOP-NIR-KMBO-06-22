#include <iostream>
#include <queue>
using namespace std;

template <class T>
class Node {
private:
    T value;

public:
    T* getValue() { return &value; }
    void setValue(T v) { value = v; }

    bool operator<(Node<T>& N) {
        return value < N.getValue();
    }

    bool operator>(Node<T>& N) {
        return value > N.getValue();
    }
    bool operator>(const Node<T>& other) const {
        return value > other.getValue();
    }
    void print() const {
        cout << value;
    }
};
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
    Book(string const& lastName, string const& firstName, string const& bookTitle, int year, string const& publisher, int pages, EditionType ed, int copies)
        : authorLastName(lastName), authorFirstName(firstName), title(bookTitle),
        publicationYear(year), publisherName(publisher), pageCount(pages), edition(ed), tirage(copies) {}

    Book() : authorLastName(""), authorFirstName(""), title(""), publicationYear(0),
        publisherName(""), pageCount(0), edition(Electronic), tirage(0) {}


    string getAuthorLastName() const { return authorLastName; }
    string getAuthorFirstName() const { return authorFirstName; }
    string getTitle() const { return title; }
    int getPublicationYear() const { return publicationYear; }
    string getPublisherName() const { return publisherName; }
    int getPageCount() const { return pageCount; }
    EditionType getEdition() const { return edition; }
    int getTirage() const { return tirage; }


    void setAuthorLastName(string const& lastName) { authorLastName = lastName; }
    void setAuthorFirstName(string const& firstName) { authorFirstName = firstName; }
    void setTitle(string const& bookTitle) { title = bookTitle; }
    void setPublicationYear(int year) { publicationYear = year; }
    void setPublisherName(string const& publisher) { publisherName = publisher; }
    void setPageCount(int pages) { pageCount = pages; }
    void setEdition(EditionType ed) { edition = ed; }
    void setTirage(int copies) { tirage = copies; }

    bool operator<(const Book& other) const { return tirage < other.tirage; }
    bool operator>(const Book& other) const { return tirage > other.tirage; }
    bool operator<(int tirageValue) const { return tirage < tirageValue; }
    bool operator==(int tirageValue) const { return tirage == tirageValue; }
    bool operator>(int tirageValue) const { return tirage > tirageValue; }

    friend ostream& operator<<(ostream& os, const Book& book);
};

ostream& operator<<(ostream& os, const Book& book) {
    os << "Author: " << book.authorFirstName << " " << book.authorLastName << endl;
    os << "Title: " << book.title << endl;
    os << "Publication Year: " << book.publicationYear << endl;
    os << "Publisher: " << book.publisherName << endl;
    os << "Page Count: " << book.pageCount << endl;
    os << "Edition: ";
    switch (book.edition) {
    case Book::Electronic:
        os << "Electronic";
        break;
    case Book::Paper:
        os << "Paper";
        break;
    case Book::Audio:
        os << "Audio";
        break;
    }
    os << endl;
    os << "Tirage: " << book.tirage << endl;

    return os;
}

template <class T>
void print(Node<T>* N) {
    cout << N->getValue() << "\n";
};

template <class T>
class Heap {
private:
    Node<T>* arr;
    int len;
    int size;

public:
    int getCapacity() const { return size; }
    int getCount() const { return len; }
    Node<T>& operator[] (int index) {
        return arr[index];
    }

    Heap<T>(int MemorySize = 100) {
        arr = new Node<T>[MemorySize];
        len = 0;
        size = MemorySize;
    }

    void Swap(int index1, int index2) {
        Node<T> temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }

    void Copy(Node<T>* dest, Node<T>* source) {
        dest->setValue(source->getValue());
    }

    Node<T>* GetLeftChild(int index) const {
        return &arr[index * 2 + 1];
    }

    Node<T>* GetRightChild(int index) const {
        return &arr[index * 2 + 2];
    }

    Node<T>* GetParent(int index) const {
        if (index % 2 == 0)
            return &arr[index / 2 - 1];
        return &arr[index / 2];
    }

    int  GetLeftChildIndex(int index) const {
        return index * 2 + 1;
    }

    int GetRightChildIndex(int index) const {
        return index * 2 + 2;
    }

    int const GetParentIndex(int index) const {
        if (index <= 0 || index >= len)
            ;
        if (index % 2 == 0)
            return index / 2 - 1;
        return index / 2;
    }


    void SiftUp(int index = -1) {

        if (index == -1) index = len - 1;
        int parent = GetParentIndex(index);
        int index2 = GetLeftChildIndex(parent);
        if (index2 == index) index2 = GetRightChildIndex(parent);
        int max_index = index;
        if (index < len && index2 < len && parent >= 0) {
            if (arr[index] > arr[index2])
                max_index = index;
            if (arr[index] < arr[index2])
                max_index = index2;
        }
        if (parent < len && parent >= 0 && arr[max_index] > arr[parent]) {
            Swap(parent, max_index);
            SiftUp(parent);
        }
    }

    void Add(T& v) {
        Node<T>* N = new Node<T>;
        if (N == NULL)
            throw exception("empty  node");
            N->setValue(v);
        Add(N);
    }

    void Add(Node<T>* N) {
        if (len < size) {
            Copy(&arr[len], N);
            len++;
            SiftUp();
        }
    }

    void ExtractMax() {
        if (len == 0) return; // Heap is empty
        Swap(0, len - 1);
        len--;
        SiftUp(0);
    }

    void Remove(int index) {
        if (index < 0 || index >= len) return;
        Swap(index, len - 1);
        len--;
        SiftUp(index);
    }

    void Straight(void (*f)(Node<T>*)) {
        int i;
        for (i = 0; i < len; i++) {
            f(&arr[i]);
        }
    }

    void InOrder(void (*f)(Node<T>*), int index = 0) {
        if (GetLeftChildIndex(index) < len)
            InOrder(f, GetLeftChildIndex(index));
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetRightChildIndex(index) < len)
            InOrder(f, GetRightChildIndex(index));
    }

};


struct BookComparator {
    bool operator()(const Book& b1, const Book& b2) const {
        return b1.getTirage() < b2.getTirage();
    }
};

int main() {

    priority_queue<Book, vector<Book>, BookComparator> PriorityQueue;

    Heap<Book> Tree;
    Book book1("Doe", "John", "Introduction to C++", 2020, "Publisher A", 300, Book::Paper, 1000);
    Book book2("Smith", "Jane", "Data Structures", 2019, "Publisher B", 400, Book::Electronic, 1500);
    Book book3("Brown", "Alice", "Algorithms", 2022, "Publisher C", 350, Book::Paper, 1200);

    PriorityQueue.push(book1);
    PriorityQueue.push(book2);
    PriorityQueue.push(book3);

    cout << "Original Heap (Straight):\n";
    void (*f_ptr)(Node<Book>*);
    f_ptr = print;




    return 0;
}
