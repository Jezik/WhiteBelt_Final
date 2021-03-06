#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <set>
#include <map>
#include <iomanip>

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

		/* Read string from beginning to the end. Check expected format "year-month-day".
		   Year, month and day must be integers. Month within [1, 12], day within [1, 31] */
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

			// Check month value [1, 12]
			if (month < 1 || month > 12) {
				string curMonth = "Month value is invalid: " + to_string(month);
				throw invalid_argument(curMonth);
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
	// Add event to database, using constructed Date as key in a map
	void AddEvent(const Date& date, const string& event) {
		eventsDBmap[date].insert(event);
	}
	/* Delete event if given date is in a database.
	   If success returns true and false otherwise */
	bool DeleteEvent(const Date& date, const string& event) {
		if (eventsDBmap.count(date) > 0) {
			bool isRemoved = eventsDBmap[date].erase(event) == 1;
			return isRemoved;
		}
		return false;
	}
	/* Delete given date from database.
	   Returns number of deleted events in given date. */
	int  DeleteDate(const Date& date) {
		int numberDeleted = 0;
		if (eventsDBmap.count(date) > 0) {
			numberDeleted = eventsDBmap[date].size();
			eventsDBmap.erase(date);
		}

		return numberDeleted;
	}
	/* Returns set for given date with events.
	   Will be printed in a main method. */
	set<string> Find(const Date& date) const {
		set<string> tempSet;
		if (eventsDBmap.count(date) > 0) {
			tempSet = eventsDBmap.at(date);
		}

		return tempSet;
	}
	/* Prints the entire database in a format "date event".  
	   YYYY-MM-DD event */
	void Print() const {
		for (const auto& pair : eventsDBmap) {
			for (const auto& event : pair.second) {
				cout << setfill('0') << setw(4) << pair.first.GetYear()
					<< '-' << setfill('0') << setw(2) << pair.first.GetMonth()
					<< '-' << setfill('0') << setw(2) << pair.first.GetDay()
					<< " " << event << endl;
			}
		}
	}

private:
	map<Date, set<string>> eventsDBmap;
};

int main() {
	Database db;
    
	string command;
	while (getline(cin, command)) {
		// Считайте команды с потока ввода и обработайте каждую
		if (command != "") {

			string operation, dateString, eventString;
			stringstream stream(command);
			while (stream.peek() != EOF) {
				stream >> operation >> dateString >> eventString;
			}

			if (operation == "Add") {
				db.AddEvent(Date(dateString), eventString);
			}
			else if (operation == "Del") {
				if (eventString == "") {
					int deleted = db.DeleteDate(Date(dateString));
					cout << "Deleted " << deleted << " events" << endl;
				}
				else {
					bool isSuccess = db.DeleteEvent(Date(dateString), eventString);
					if (isSuccess) {
						cout << "Deleted successfully" << endl;
					}
					else {
						cout << "Event not found" << endl;
					}
				}
			}
			else if (operation == "Find") {
				set<string> events = db.Find(Date(dateString));
				for (const auto& str : events) {
					cout << str << endl;
				}
			}
			else if (operation == "Print") {
				db.Print();
			}
			else {
				cout << "Unknown command: " << command;
				exit(1);
			}
		}
	}
	
	return 0;
}