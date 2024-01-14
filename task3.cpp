#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Student {
	private:
		string name;
		string familia;
		string otchestvo;
		string group;
		int grades[3];
	public:
		//construct
		Student(): name("Ivan"), familia("Ivanov"), otchestvo("Ivanovich"), group("000"), grades{3, 3, 3} {}
		
		double GetAvGrade() const{
			double sum = 0;
			for (int i = 0; i<3; i++){
				sum += grades[i];
			}
			return sum/3.0;
		}
		
		//sravnenie
		bool operator==(const Student& other) const {
			return GetAvGrade() == other.GetAvGrade(); 
		}
		bool operator<(const Student& other) const{
			return GetAvGrade() < other.GetAvGrade();
		}
		bool operator>(const Student& other) const{
			return GetAvGrade() > other.GetAvGrade();
		}
		bool operator<=(const Student& other) const{
			return GetAvGrade() <= other.GetAvGrade();
		}
		bool operator>=(const Student& other) const{
			return GetAvGrade() >= other.GetAvGrade();
		}
		bool operator!=(const Student& other) const{
			return GetAvGrade() != other.GetAvGrade();
		}
		friend istream& operator>>(istream& is, Student& s);
		friend ostream& operator<<(ostream& os, const Student& s);
};

istream& operator>>(istream& is, Student& s) {
    is >> s.familia >> s.name >> s.otchestvo
        >> s.group >> s.grades[0] >> s.grades[1] >> s.grades[2];
    return is;
}

ostream& operator<<(ostream& os, const Student& s) {
    os << s.familia << " " << s.name << " " << s.otchestvo
        << " " << s.group << " " << s.grades[0] << " " << s.grades[1] << " " << s.grades[2];
    return os;
}


int main(int argc, char** argv) {
	const int stud_amount = 5;
	Student s[stud_amount];
	
	ifstream input("students.txt");
	for (int i = 0; i < stud_amount; i++) {
        input >> s[i];
    }
    
    sort(s, s + stud_amount, greater<Student>());
    
    ofstream output("sorted.txt");
    
    for (const auto& ss : s) {
        output << ss << "\n";
    }
	return 0;
}
