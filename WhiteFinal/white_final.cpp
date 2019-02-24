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

			// Check month value [1, 12]
			if (month < 1 || month > 12) {
				string curMonth = "Month value is invalid: " + to_string(month);
				throw invalid_argument(curMonth);
			}

			stream >> day;
			EnsureGoodStream(stream);

			if (stream.peek() != EOF) {
				throw runtime_error("");
			}

			// Check day value [1, 31]
			if (day < 1 || day > 31) {
				string curDay = "Day value is invalid: " + to_string(day);
				throw invalid_argument(curDay);
			}
		}
		catch(runtime_error& e) {
			cout << "Wrong date format: " << dateString;
			exit(1);
		}
		catch (invalid_argument& e) {
			cout << e.what();
			exit(1);
		}
	}

	int GetYear() const {
		return year;
	}
	int GetMonth() const {
		return month;
	}
	int GetDay() const {
		return day;
	}

private:
	int year;
	int month;
	int day;
};

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() != rhs.GetYear()) {
		return lhs.GetYear() < rhs.GetYear();
	}
	else if (lhs.GetMonth() != rhs.GetMonth()) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	else if (lhs.GetDay() != rhs.GetDay()) {
		return lhs.GetDay() < rhs.GetDay();
	}

	return false;
}

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

	/*string str;
	cin >> str;

	Date date(str);

	cout << date.GetDay() << " " << date.GetMonth() << " " << date.GetYear() << endl;*/

	system("pause");
	return 0;
}