#include <iostream>
#include <fstream>
using namespace std;
template <class T>
class Element {
private:
	Element* next;
	Element* prev;		
	T field;
public:
	Element(T value = 0, Element<T>* const next_ptr = NULL, Element<T>* const prev_ptr = NULL): field(value), next(next_ptr), prev(prev_ptr) {}
	
	virtual Element* getNext() const { return next; }

	virtual void setNext( Element* value) { next = value; }

	virtual Element* getPrevious() const { return prev; }

	virtual void setPrevious(Element* value) { prev = value; }

	virtual T getValue() const { return field; }

	virtual void setValue(const T& value) { field = value; }

	template<class T> friend ostream& operator<< (  ostream& ustream, const Element<T>& obj);
};


template<class T>
ostream& operator << (ostream& ustream, const Element<T>& obj) {
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent {
protected:
	Element<T>* head;
	Element<T>* tail;
	int num;

public:
	virtual int Number() const { return num; }

	virtual Element<T>* getBegin() const { return head; }

	virtual Element<T>* getEnd() const { return tail; }

	LinkedListParent() {
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL;
		num = 0;
	}

	virtual Element<T>* push(const T& value) = 0;

	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent() {
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
	}
	//получение элемента по индексу - какова асимптотическая 
	virtual Element<T>* operator[](int i) {
		//индексация
		if (i<0 || i>num) { 
			return NULL; 
		}

		int k = 0;
		//ищем i-й элемент - вставем в начало и отсчитываем i 
		//шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream&  ustream, const LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream&	ustream, LinkedListParent<T>& obj);
};


template<class T>
ostream& operator << (ostream& ustream, const LinkedListParent<T>& obj) {
	if (typeid(ustream).name() == typeid(ofstream).name()) {
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); 
			current != NULL;
			current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++) {
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";
	}
	return ustream;
}


template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj) {
	int len;
	ustream >> len;
	double v = 0;
	for (int i = 0; i < len; i++) {
		ustream >> v;
		obj.emplace_back(v);
	}
	return ustream;
}

template<typename ValueType>
class ListIterator {
private:
	Element<ValueType>* ptr;
public:
	ListIterator() { ptr = NULL; }

	ListIterator(Element<ValueType>* p) { ptr = p; }

	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }

	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }

	Element<ValueType>& operator*(){ return *ptr; }

	ListIterator& operator++() { ptr = ptr->getNext(); return *this; }

	ListIterator& operator++(int v) { ptr = ptr->getNext(); return *this; }

	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }

	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }
};


template <class T>
class IteratedLinkedList : public LinkedListParent<T> {
public:

	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }

	virtual ~IteratedLinkedList() {	cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> iterator;
	ListIterator<T> begin() const { 
		ListIterator<T> it = LinkedListParent<T>::head;
		return it;
	}
	ListIterator<T> end() const {
		ListIterator<T> it = LinkedListParent<T>::tail;
		return it;
	}
};


template <class T>
class QueueList : public IteratedLinkedList<T> {
public:
	Element<T>* push(const T& value) {
		Element<T>* newElement = new Element<T>(value);
		if (newElement == nullptr) {
			// Обработка ошибки выделения памяти
			cout << "Ошибка выделения памяти" << endl;
			return nullptr;
		}
		if (!this->head) {
			this->head = this->tail = newElement;
		}
		else {
			newElement->setPrevious(this->tail);
			this->tail->setNext(newElement);
			this->tail = newElement;
		}
		return newElement;
	}

	Element<T>* pop() {
		if (this->head) {
			Element<T>* temp = this->head;
			this->head = this->head->getNext();
			if (this->head)
				this->head->setPrevious(nullptr);
			else
				this->tail = nullptr;
			return temp;
		}
		return nullptr;
	}

	QueueList<T> filter(int a) {
		Element<T>* el = this->head;
		QueueList<T>queueList;
		if (el != nullptr) {
			T item = el->getValue();
			while (el != nullptr) {
				if (abs(item) > a)
					queueList.push(item);
				el = el->getNext();
				if (el != nullptr)
					item = el->getValue();
			}
		}
		return queueList;
	}
};


template <class T>
class QueueListSportsTeam : public IteratedLinkedList<T> {
public:
	Element<T>* push(const T& value) {
		Element<T>* newElement = new Element<T>(value);
		if (newElement == nullptr) {
			// Обработка ошибки выделения памяти
			cout << "Ошибка выделения памяти" << endl;
			return nullptr;
		}
		if (!this->head) {
			this->head = this->tail = newElement;
		}
		else {
			Element<T>* current = this->head;
			Element<T>* prev = nullptr;
			while (current != nullptr && value < current->getValue()) {
				prev = current;
				current = current->getNext();
			}

			if (!prev) {
				newElement->setNext(this->head);
				this->head->setPrevious(newElement);
				this->head = newElement;
			}
			else {
				prev->setNext(newElement);
				newElement->setPrevious(prev);
				newElement->setNext(current);

				if (current) {
					current->setPrevious(newElement);
				}
				else {
					this->tail = newElement;
				}
			}
		}
		return newElement;
	}

	Element<T>* pop() {
		if (this->head) {
			Element<T>* temp = this->head;
			this->head++;
			if (this->head)
				this->head->setPrevious(nullptr);
			else
				this->tail = nullptr;
			return temp;
		}
		return nullptr;
	}

	QueueList<T> filter(int a) {
		Element<T>* el = this->head;
		QueueList<T>queueList;
		if (el != nullptr) {
			T item = el->getValue();
			while (el != nullptr) {
				if (abs(item) > a)
					queueList.push(item);
				el = el->getNext();
				if (el != nullptr)
					item = el->getValue();
			}
		}
		return queueList;
	}
};


template <class T, template <typename...> class Container>
Container<T> filter2(const Container<T>& list, int a) {
	Element<T>* el = list.getBegin();
	Container<T> queueList;
	if (el != nullptr) {
		T item = el->getValue();
		while (el != nullptr) {
			if (abs(item) > a)
				queueList.push(item);
			el = el->getNext();
			if (el != nullptr)
				item = el->getValue();
		}
	}
	return queueList;
}



class Fraction {
private:
	int numerator;
	int denominator;
public:

	Fraction(int num, int denom) {
		numerator = num;
		denominator = denom;
	}

	// Геттер для числителя
	int getNumerator() const {
		return numerator;
	}

	// Геттер для знаменателя
	int getDenominator() const {
		return denominator;
	}

	// Перегрузка оператора "<" для сравнения дробей
	bool operator<(const Fraction& other) const {
		return (numerator * other.denominator) < (other.numerator * denominator);
	}

	// Перегрузка оператора "==" для сравнения дробей
	bool operator==(const Fraction& other) const {
		return (numerator == other.numerator) && (denominator == other.denominator);
	}

};


class SportsTeam {
private:
	string name;
	string city;
	int wins;
	int losses;
	int draws;
	int points;

public:
	SportsTeam(const string& n, const string& c, int w, int l, int d) :
		name(n), city(c), wins(w), losses(l), draws(d), points(w * 3 + d) {}


	bool operator==(const SportsTeam& other) const {
		return (name == other.name) && (city == other.city);
	}

	bool operator<(const SportsTeam& other) const {
		return (wins != other.wins) ? (wins < other.wins) :
			(draws != other.draws) ? (draws < other.draws) :
			(losses != other.losses) ? (losses < other.losses) :
			(name < other.name);
	}

	string getName() const { return name; }

	string getCity() const { return city; }

	int getWins() const { return wins; }

	int getLosses() const { return losses; }

	int getDraws() const { return draws; }

	int getPoints() const { return points; }

	friend ostream& operator<<(ostream& os, const SportsTeam& team);
};

int main() {
	QueueList<int> intQueueList;


	intQueueList.push(10);
	intQueueList.push(20);
	intQueueList.push(30);
	intQueueList.push(40);
	intQueueList.push(50);
	

	cout << "List:" << endl;
	for (ListIterator<int> it = intQueueList.begin(); it != intQueueList.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	
	int filterValue = 34;
	QueueList<int> filteredList = intQueueList.filter(filterValue);

	cout << "Filtered List " << filterValue << ":" << endl;
	for (ListIterator<int> it = filteredList.begin(); it != filteredList.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}