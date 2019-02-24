#include <iostream>
#include <string>
#include <exception>
#include <sstream>

using namespace std;

// Ensure, that delimiter in dateString is '-'
void EnsureSkipNextSymbol(stringstream& stream) {
	if (stream.peek() != '-') {
		throw runtime_error("");
	}

	stream.ignore(1);
}

// Ensure, that date parsing is OK and format is right
void EnsureGoodStream(stringstream& stream) {
	if (stream.fail()) {
		throw runtime_error("");
	}
}

class Date {
public:
	Date(const string& dateString) {

		try {
			stringstream stream(dateString);
			stream >> year;
			EnsureGoodStream(stream);
			EnsureSkipNextSymbol(stream);
			stream >> month;
			EnsureGoodStream(stream);
			EnsureSkipNextSymbol(stream);
			stream >> day;
			EnsureGoodStream(stream);

			if (stream.peek() != EOF) {
				throw runtime_error("");
			}
		}
		catch(runtime_error& e) {
			cout << "Wrong date format: " << dateString;
			exit(1);
		}
	}

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int  DeleteDate(const Date& date);

	/* ??? */ Find(const Date& date) const;
  
	void Print() const;
};

int main() {
	Database db;
    
	string command;
	while (getline(cin, command)) {
	// Считайте команды с потока ввода и обработайте каждую
	}

	system("pause");
	return 0;
}