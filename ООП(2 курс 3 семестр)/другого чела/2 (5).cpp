#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <queue>

using namespace std;


bool findbyValue(const map<string, int>& tree, int value) {
    for (const auto& pair : tree) {
        if (pair.second == value) {
            return true;
        }
    }
    return false;
}


bool findbyKey(const map<string, int>& tree, const string& key) {
    return tree.find(key) != tree.end();
}

void printTree(const map<string, int>& tree) {
    for (const auto& pair : tree) {
        cout << "Name: " << pair.first << ", ID: " << pair.second << endl;
    }
}
bool findbyKey(const map<string, Book>& tree, const string& key) {
    return tree.find(key) != tree.end();
}

void printTree(const map<string, Book>& tree) {
    for (const auto& pair : tree) {
        cout << "Name: " << pair.first << ", ID: " << pair.second << endl;
    }
}
void printTreeWithParam(const map<string, Book>& tree, string key) {
    for (const auto& pair : tree) {
        if (pair.first == key)
        cout << "Tree: " << pair.first << ", Param: " << pair.second << endl;
    }
}

map<string, int> filter(const map<string, int>& tree, int data) {
    map<string, int> filteredTree;
    for (const auto& pair : tree) {
        if (pair.second > data) {
            filteredTree.insert(pair);
        }
    }
    return filteredTree;
}

multimap<string, Book> filter(const multimap<string, Book>& tree, int data) {
    multimap<string, Book> filteredTree;
    for (const auto& pair : tree) {
        if (pair.second > data) {
            filteredTree.insert(pair);
        }
    }
    return filteredTree;
}


vector<int> uniqueValues(const map<string, int>& tree) {
    set<int> uniqueSet;
    for (const auto& pair : tree) {
        uniqueSet.insert(pair.second);
    }
    vector<int> uniqueVector(uniqueSet.begin(), uniqueSet.end());
    return uniqueVector;
}

class Book {
public:
    string k;
    int v;
    Book(string K, int V) {
        k = K;
        v = V;
    };
    bool operator > (int data) {
        if (v < data)
            return true;
        return false;
    }
    bool operator < (Book& book) {
        if (v < book.v)
            return true;
        return false;
    }
    friend ostream& operator<<(ostream& s, const Book& t)
    {
        s << t.k << ": " << t.v;
        return s;
    }
};
bool operator > (const Book& book, int data) {
    if (book.v > data)
        return true;
    return false;
}
template <typename Key, typename T>
struct MultiMapList {
    bool operator()(const std::pair<Key, T>& a, const std::pair<Key, T>& b) const {
       
        return a.first > b.first; 
    }
};
template<typename T>
void print_queue(T& q) {
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

template <typename Key, typename T>
struct MultiMapComparator {
    bool operator()(const std::pair<Key, T>& a, const std::pair<Key, T>& b) const {
        // Сравниваем элементы по ключу
        return a.first > b.first; // измените знак, если вам нужен другой порядок
    }
};

int main() {
    map<string, int> bookTirage{
        {"Book 1", 1000},
        { "Book 2", 1500 },
        { "Book 3", 800 },
        { "Book 4", 2000 },
        { "Book 5", 1200 },
    };

    multimap<string, int>;
    priority_queue<pair<int, Book>,vector<pair<int,Book >>, MultiMapList<int, Book>> MiltiMapQueue;
    bool foundByValue = findbyValue(bookTirage, 1500);
    cout << "B" << foundByValue << endl;


    bool foundByKey = findbyKey(bookTirage, "Book 4");
    cout << "Data"  << foundByKey << endl;

 
    cout << "Book consits:" << endl;
    printTree(bookTirage);

    int data = 1300;
    map<string, int> filtered = filter(bookTirage, data);
    cout << "Filtered consists:" << endl;
    printTree(filtered);

    vector<int> unique = uniqueValues(bookTirage);
    cout << "Uniq consists" << endl;
    for (int tirage : unique) {
        cout << tirage << " ";
    }
    cout << endl;
}
