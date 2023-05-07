#include <iostream>

using namespace std;

class BaseString {
protected:
	char* p;
	int len;
	int capacity;
public:

	BaseString(char* ptr) {
		cout << "\nBase Constructor 1\n";
		capacity = 256;
		p = new char[capacity];
		len = 0;
		int i = 0;
		p[0] = '\0';
		if (ptr != nullptr) {
			while (ptr[i] != '\0' && i < capacity - 1) {
				p[i] = ptr[i];
				++i;
			}
			p[i] = '\0';
			len = i;
		}
	}

	BaseString(const char* ptr) {
		cout << "\nBase Constructor 1\n";
		capacity = 256;
		p = new char[capacity];
		len = 0;
		int i = 0;
		p[0] = '\0';
		if (ptr != nullptr) {
			while (ptr[i] != '\0' && i < capacity - 1) {
				p[i] = ptr[i];
				++i;
			}
			p[i] = '\0';
			len = i;
		}
	}

	BaseString(int Capacity = 256) {
		cout << "\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
	}

	int Length() { return len; }
	int Capacity() { return capacity; }
	char& operator[](int i) { return p[i]; }


	BaseString& operator=(BaseString& s) {
		cout << "\nBase Operator = \n";
		if (capacity >= s.capacity) {
			len = s.len;
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}
		else {
			delete[] p;
			capacity = s.capacity;
			len = s.len;
			p = new char[capacity];
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}

		return *this;
	}

	BaseString(const BaseString& s) {
		cout << "\nBase Copy Constructor\n";
		capacity = s.capacity;
		len = s.len;
		p = new char[capacity];

		for (int i = 0; i < len; ++i) {
			p[i] = s.p[i];
		}
		p[len] = '\0';
	}

	virtual void print() {
		int i = 0;
		while (p[i] != '\0') {
			cout << p[i];
			i++;
		}
	}
};


class String : public BaseString {

public:
	String(char* s) : BaseString(s) {}
	String(const char* s) : BaseString(s) {}
	String(int Capacity = 256) : BaseString(Capacity) {}

	String operator=(const String& s) {
		cout << "\nBase Operator = \n";
		if (capacity >= s.capacity) {
			len = s.len;
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}
		else {
			delete[] p;
			capacity = s.capacity;
			len = s.len;
			p = new char[capacity];
			for (int i = 0; i <= len; ++i) {
				p[i] = s.p[i];
			}
		}

		return *this;
	}

	String(const String& s) {
		cout << "\nBase Copy Constructor\n";
		capacity = s.capacity;
		len = s.len;
		p = new char[capacity];

		for (int i = 0; i < len; ++i) {
			p[i] = s.p[i];
		}
		p[len] = '\0';
	}

	void getDigitsArray(String s) {
		int* arr = new int[s.Length()];
		int j = 0;
		int arr1 = 0;
		for (int i = 0; i < s.Length(); i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				arr[j] = s[i] - '0';
				j++;
			}

		
		}
		int size = j;
		
		cout << "Result getDigitsArray: ";
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";	
		}
	}
};


int main() {
	String a;
	String s1 = ("Hello 123 World 456");
	String s2 = s1;
	String s3 = ("Hello 789 World 123");
	String s4(s3);
	
	a.getDigitsArray(s1);
	a.getDigitsArray(s2);
	a.getDigitsArray(s3);
	a.getDigitsArray(s4);

	return 0;
}
