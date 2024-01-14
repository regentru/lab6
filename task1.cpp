#include <iostream>
#include <iomanip>

using namespace std;

class Date {
	private:
		int day;
		int month;
		int year;
	
	public:
	
	//construct
	Date(): day(1), month(1), year(2007) {}
	Date(int dt, int mn, int yr): day(dt), month(mn), year(yr) {}
	
	//destructor
	~Date() {}
	
	//access to fields	
	int OutDay() const {
		return day;
	}
	int OutMonth() const {
		return month;
	}
	int OutYear() const{
		return year;
	}
	
	//input day/month/year
	void InputDay(int d) {
		day = d;
	}
	void InputMonth(int m) {
		month = m;
	}
	void InputYear(int y) {
		year = y;
	}
	
	//add to date
	Date operator+(int d) const;
	
	//remove from date
	Date operator-(int d) const;
	
	//comparison of two dates
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>=(const Date& other) const;
	bool operator>(const Date& other) const;
	
	//input/output
	friend std::istream& operator>>(std::istream& in, Date& date);
    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

//add to date realization
Date Date::operator+(int d) const{
	Date result = *this;
	result.day += d;
	while (result.day > 31) {
		result.day -= 31;
		result.month++;
		if (result.month > 12) {
			result.year++;
			result.month = 1;
		}
	}
	return result;
}

//remove from date realization
Date Date::operator-(int d) const{
	Date result = *this;
	result.day -= d;
	while (result.day < 1) {
		result.day += 31;
		result.month--;
		if (result.month < 0) {
			result.year--;
			result.month = 12;
		}
	}
	return result;
}

//comparison realization
bool Date::operator==(const Date& other) const {
    return (day == other.day) && (month == other.month) && (year == other.year);
}

bool Date::operator!=(const Date& other) const {
	return (day != other.day) or (month != other.month) or (year != other.year);
}

bool Date::operator<(const Date& other) const {
    if (year < other.year) {
        return true;
    } else if (year > other.year) {
        return false;
    }

    if (month < other.month) {
        return true;
    } else if (month > other.month) {
        return false;
    }

    return day < other.day;
}

bool Date::operator>(const Date& other) const {
	if (year > other.year) {
        return true;
    } else if (year < other.year) {
        return false;
    }

    if (month > other.month) {
        return true;
    } else if (month < other.month) {
        return false;
    }

    return day > other.day;
}

bool Date::operator<=(const Date& other) const {
    return (*this < other) or (*this == other);
}

bool Date::operator>=(const Date& other) const {
    return (*this > other) or (*this == other);
}

std::istream& operator>>(std::istream& in, Date& date) {
    std::cout << "Input Date in format DD MM YYYY: ";
    in >> date.day >> date.month >> date.year;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
    out << std::setw(2) << std::setfill('0') << date.day << ' '
        << std::setw(2) << std::setfill('0') << date.month << ' '
        << date.year;
    return out;
}

int main(int argc, char** argv) {
	
	cout << "Realization of class Date." << endl;
	int k = 10;
	while(k!=0){
		cout << "Enter 1 to add to the date." << endl;
		cout << "Enter 2 to subtract from the date." << endl;
		cout << "Enter 3 for strict(<, >, ==, !=) date comparison." << endl;
		cout << "Enter 4 for non-strict(<=, >=) date comparison." << endl;
		cout << "Enter 0 to exit." << endl;
		cin >> k;
		switch(k){
			case 1:{
				Date a;
				cout << "Enter your date." << endl;
				cin >> a;
				cout << "Enter the number to add." << endl;
				int add = 0;
				cin >> add;
				cout << "Result = " << a + add << endl;
				break;
			}
			case 2:{
				Date a;
				cout << "Enter your date." << endl;
				cin >> a;
				cout << "Enter the number to subtract." << endl;
				int add = 0;
				cin >> add;
				cout << "Result = " << a - add << endl;
				break;
			}
			case 3:{
				Date a,b;
				cout << "Enter your first date." << endl;
				cin >> a;
				cout << "Enter your second date." << endl;
				cin >> b;
				if (a == b){
					cout << "They are equal." << endl;
				} else {
					cout << "They are not equal." << endl;
					if (a > b){
						cout << a << " is bigger." << endl;
					} else{
						cout << b << " is bigger." << endl;
					}
				}
				break;
			}
			case 4:{
				Date a,b;
				cout << "Enter your first date." << endl;
				cin >> a;
				cout << "Enter your second date." << endl;
				cin >> b;
				if (a >= b){
						cout << a << " is bigger or equal." << endl;
					} else{
						cout << b << " is bigger or equal." << endl;
					}
				break;
			}
			default:
				break;
		}
	}
	return 0;
}
