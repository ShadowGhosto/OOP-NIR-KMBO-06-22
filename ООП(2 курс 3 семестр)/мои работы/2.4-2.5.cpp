#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class SportsTeam {
private:
    string name;
    string city;
    int wins;
    int losses;
    int draws;
    int points;

public:
    SportsTeam() {}
    SportsTeam(const string& n, const string& c, int w, int l, int d) :
        name(n), city(c), wins(w), losses(l), draws(d), points(w * 3 + d) {}

    bool operator<(const SportsTeam& other) const {
        return (wins != other.wins) ? (wins < other.wins) :
            (draws != other.draws) ? (draws < other.draws) :
            (losses != other.losses) ? (losses < other.losses) :
            (name < other.name);
    }
    bool operator==(const SportsTeam& other) const {
        return (name == other.name) && (city == other.city);
    }

    // Binary operator <
    // Binary operator >
    bool operator>(const SportsTeam& other) const {
        return (wins != other.wins) ? (wins > other.wins) :
            (draws != other.draws) ? (draws > other.draws) :
            (losses != other.losses) ? (losses > other.losses) :
            (name > other.name);
    }
    bool operator>(int a) const {
        return wins > a;
    }
    bool operator< (int a) const {
        return wins < a;
    }
    bool operator==(int a) const {
        return wins == a;
    }

    string getName() const { return name; }

    string getCity() const { return city; }

    int getWins() const { return wins; }

    int getLosses() const { return losses; }

    int getDraws() const { return draws; }

    int getPoints() const { return points; }

    friend ostream& operator<<(ostream& os, const SportsTeam& team);
};

ostream& operator<<(ostream& os, const SportsTeam& team) {
    os << "Name: " << team.getName() << ", City: " << team.getCity()
        << ", Wins: " << team.getWins() << ", Losses: " << team.getLosses()
        << ", Draws: " << team.getDraws() << ", Points: " << team.getPoints();
    return os;
}

// Узел
template <class T>
class Node {
protected:
    T data;
    Node* left;
    Node* right;
    Node* parent;
    int height;

public:
    virtual void setData(T d) { data = d; }
    virtual T getData() { return data; }
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
    Node<T>(T n) {
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
    void Add(T& SportsTeam) {
        Node<T>* N = new Node<T>(SportsTeam);
        root = Add_R(N, root);
    }

    //доступ к корневому элементу
    virtual Node<T>* getRoot() { return root; }
    //конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
    //рекуррентная функция добавления узла. Устроена аналогично, 	но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<T>* Add_R(Node<T>* N) {
        return Add_R(N, root);
    }
    virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current) {
        if (N == nullptr) {
            return Current;
        }
        if (Current == nullptr) {

            return N;
        }
        if (N->getData() < Current->getData()) {
            Current->setLeft(Add_R(N, Current->getLeft()));
            Current->getLeft()->setParent(Current);
        }
        else if (N->getData() > Current->getData()){
            Current->setRight(Add_R(N, Current->getRight()));
            Current->getRight()->setParent(Current);
        }
        return Current;
    }
    //функция для добавления числа. Делаем новый узел с этими 	данными и вызываем нужную функцию добавления в дерево

    virtual Node<T>* Min(Node<T>* Current = NULL) {
        //минимум - это самый "левый" узел. Идём по дереву всегда влево
        if (root == NULL) { 
            return NULL; 
        }
        if (Current == NULL) {
            Current = root;
        }
        while (Current->getLeft() != NULL) {
            Current = Current->getLeft();
        }
        return Current;
    }
    virtual Node<T>* Max(Node<T>* Current = NULL) {
        //минимум - это самый "правый" узел. Идём по дереву всегда вправо
        if (root == NULL) {
            return NULL;
        }
        if (Current == NULL) {
            Current = root;
        }
        while (Current->getRight() != NULL) {
            Current = Current->getRight();
        }
        return Current;
    }
    //поиск узла в дереве. Второй параметр - в каком поддереве 	искать, первый - что искать
    virtual Node<T>* Find(int data, Node<T>* Current) {
        //база рекурсии
        if (Current == NULL) { return NULL; }
        if (Current->getData() == data) { return Current; }
        //рекурсивный вызов
        if (Current->getData() > data) { return Find(data, Current->getLeft()); }
        if (Current->getData() < data) { return Find(data, Current->getRight()); }
    }
    //три обхода дерева
    virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*)) {
        if (N != NULL) {
            f(N);
        }
        if (N != NULL && N->getLeft() != NULL) {
            PreOrder(N->getLeft(), f);
        }
        if (N != NULL && N->getRight() != NULL) {
            PreOrder(N->getRight(), f);
        }
    }
    //InOrder-обход даст отсортированную последовательность
    virtual void InOrder(Node<T>* N, void (*f)(Node<T>*)) {
        if (N != NULL && N->getLeft() != NULL) {
            InOrder(N->getLeft(), f);
        }
        if (N != NULL) {
            f(N);
        }
        if (N != NULL && N->getRight() != NULL) {
            InOrder(N->getRight(), f);
        }
    }
    virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*)) {
        if (N != NULL && N->getLeft() != NULL) {
            PostOrder(N->getLeft(), f);
        }
        if (N != NULL && N->getRight() != NULL) {
            PostOrder(N->getRight(), f);
        }
        if (N != NULL) {
            f(N);
        }
    }

    // Функция для поиска узла по ключу
    Node<T>* FindByKey(string key) { return FindByKey_R(key, root); }

    // Функция для поиска узла по значению
    Node<T>* FindByValue(int value) { return FindByValue_R(value, root); }

private:
    // Рекурсивная функция для поиска узла по ключу
    Node<T>* FindByKey_R(string key, Node<T>* current) {
        if (current == nullptr) { return nullptr; }// Узел не найден
       
        if (key == current->getData().getName()) { return current; }// Узел найден

        if (key < current->getData().getName()) { return FindByKey_R(key, current->getLeft()); } // Идем влево

        else { return FindByKey_R(key, current->getRight()); } // Идем вправо
    }

    // Рекурсивная функция для поиска узла по значению
    Node<T>* FindByValue_R(int value, Node<T>* current) {
        if (current == nullptr) { return nullptr; }// Узел не найден

        if (value == current->getData().getWins()) { return current; }// Узел найден

        Node<T>* leftResult = FindByValue_R(value, current->getLeft());
        if (leftResult != nullptr) { return leftResult; } // Узел найден в левом поддереве 

        return FindByValue_R(value, current->getRight()); // Идем вправо
    }
};

// Функция для вывода информации о книге
// Функция для вывода информации о команде
void printSportsTeam(Node<SportsTeam>* teamNode) {
    SportsTeam team = teamNode->getData();
    cout << "Name: " << team.getName() << ", City: " << team.getCity()
        << ", Wins: " << team.getWins() << ", Losses: " << team.getLosses()
        << ", Draws: " << team.getDraws() << ", Points: " << team.getPoints();
}


template <class T>
class MultiTree : public Tree<T> {
public:
    using Tree<T>::Add; // Импортируем метод Add из базового класса


    Node<T>* operator[](const string& key) {
        Node<T>* found = this->FindByKey(key);
        if (found != nullptr) { return found->getData(); }
    }
};

int main() {
    Tree<SportsTeam> sportsTeamTree;


    SportsTeam team1("Team A", "City X", 10, 5, 2);
    SportsTeam team2("Team B", "City Y", 8, 7, 1);
    SportsTeam team3("Team C", "City Z", 12, 3, 4);


    sportsTeamTree.Add(team1);
    sportsTeamTree.Add(team2);
    sportsTeamTree.Add(team3);

    cout << "InOrder Traversal:" << endl;
    sportsTeamTree.InOrder(sportsTeamTree.getRoot(), printSportsTeam);

    Node<SportsTeam>* foundByKey = sportsTeamTree.FindByKey("Team B");
    if (foundByKey != nullptr) {
        cout << "\nFound by key: " << foundByKey->getData() << endl;
    }
    else {
        cout << "\nNot found by key" << endl;
    }

    Node<SportsTeam>* foundByValue = sportsTeamTree.FindByValue(30);
    if (foundByValue != nullptr) {
        cout << "Found by value: " << foundByValue->getData() << endl;
    }
    else {
        cout << "Not found by value" << endl;
    }

    MultiTree<SportsTeam> multiTeamTree;

    multiTeamTree.Add(team1);
    multiTeamTree.Add(team2);
    multiTeamTree.Add(team3);




    return 0;
}
