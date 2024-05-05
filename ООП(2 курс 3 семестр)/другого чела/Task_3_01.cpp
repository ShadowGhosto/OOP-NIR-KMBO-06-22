#include <list>
#include <iostream>
#include <stdlib.h>
#include <string> 
using namespace std;

class Serial
{
public:
	string name;
	string producer;
	int seasons;
	int popularity;
	int rating;
	int date;
	string country;
	Serial(string Name = "Name" + to_string(rand() % 10), string Producer = "Producer" + to_string(rand() % 10), int Seasons = rand() % 10, int Popularity = rand() % 1000, int Rating = rand() % 10, int Date = 2000 + rand() % 23, string Country = "Country" + to_string(rand() % 10))
	{
		name = Name;
		producer = Producer;
		seasons = Seasons;
		popularity = Popularity;
		rating = Rating;
		date = Date;
		country = Country;
	}
	Serial(const Serial& S)
	{
		name = S.name;
		producer = S.producer;
		seasons = S.seasons;
		popularity = S.popularity;
		rating = S.rating;
		date = S.date;
		country = S.country;
	}
	bool operator>(const Serial& S)
	{
		if (rating < S.rating) return true;
		if (rating == S.rating)
		{
			if (name > S.name) return true;
		}
		return false;
	}
	bool operator<(const Serial& S)
	{
		if (rating > S.rating) return true;
		if (rating == S.rating)
		{
			if (name < S.name) return true;
		}
		return false;
	}
};
ostream& operator << (ostream& os, const Serial& s)
{
	return os << s.name << " " << s.producer << " Seasons = " << s.seasons << " Popularity = " << s.popularity << " Rating = " << s.rating << " Year = " << s.date << " " << s.country << endl;
}


template<class T>
void insert(list<T>& lst, T element)
{
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		if (*p > element)
			break;
		p++;
	}
	lst.insert(p, element);
}

template<class T>
void push(list<T>& lst, const T& element)
{
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end() && *p < element) ++p;

	lst.insert(p, element);
}

template<class T>
void pop(list<T>& lst, int index = -1)
{
	int i = 1;
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		if (i == index)
			break;
		p++;
		i++;
	}
	if (p == lst.end()) p--;
	lst.erase(p);
}

template<class T>
list<T> filter(list<T>& lst, bool (*P)(const T&))
{
	list<T> result;
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		if (P(*p)) result.push_back(*p);
		p++;
	}
	return result;
}

template<class T>
bool p(const T& item)
{
	if (item > 0) return true;
	return false;
}

template<class T>
void printList(list<T>& lst)
{
	typename list<T>::iterator p = lst.begin();
	while (p != lst.end())
	{
		cout << *p << " ";
		p++;
	}
	cout << endl;
}

int main()
{
	typedef double T;
	list<char> lst;
	int i = 0;
	for (i = 0; i < 10; i += 2)
		lst.push_back('A' + i);
	insert(lst, 'X');
	printList(lst);
	list<T> lst1;
	for (i = -10; i < 10; i += 2)
		push<T>(lst1, i);
	list<T> lst2;
	lst2 = filter(lst1, p);
	printList(lst1);
	printList(lst2);
	list<Serial> lst3;
	for (i = 0; i < 10; i++)
	{
		insert(lst3, Serial());
	}
	printList(lst3);
	pop(lst3);
	printList(lst3);
	return 0;
}
