#include <iostream>

using namespace std;

class Rectangle{
	private:
		double x = 0;
		double y = 0;
		double height;
		double width;
	public:
		//construct
		Rectangle(): height(1), width(1) {}
		Rectangle(double h, double w): height(h), width(w){}
		
		//destructor
		~Rectangle() {}
		
		//area
		double GetS() const{
			return height*width;
		}
		
		//left, right, top, bottom
		double GetLeft() const{
			return x;
		}
		double GetRight() const{
			return x + width;
		}
		double GetTop() const{
			return y + height;
		}
		double GetBottom() const{
			return y;
		}
		
		//*operator
		Rectangle operator*(const Rectangle& other) const {
			double xmaxl = max(GetLeft(), other.GetLeft());
			double ymaxb = max(GetBottom(), other.GetBottom());
			double xmaxr = min(GetRight(), other.GetRight());
			double ymaxt = min(GetTop(), other.GetTop());
			
			if ((xmaxr <= xmaxl) or (ymaxt <= ymaxb)){
				return Rectangle(0, 0);
			}
			
			return Rectangle(ymaxt - ymaxb, xmaxr - xmaxl);
		}
		
		//comparison operators
		bool operator>(const Rectangle & other) const {
        	return GetS() > other.GetS();
    	}
    	bool operator<(const Rectangle & other) const {
        	return GetS() < other.GetS();
    	}
    	bool operator==(const Rectangle & other) const {
        	return GetS() == other.GetS();
    	}
    	bool operator!=(const Rectangle & other) const {
        	return GetS() != other.GetS();
    	}
    	bool operator<=(const Rectangle & other) const {
        	return GetS() <= other.GetS();
    	}
    	bool operator>=(const Rectangle & other) const {
        	return GetS() >= other.GetS();
    	}
    	
    	friend ostream& operator<<(ostream& out, const Rectangle& r);
    	friend istream& operator>>(istream& in, Rectangle& r);
};

std::ostream& operator<<(std::ostream& out, const Rectangle& r) {
    out << "Rectangle((" << r.GetLeft() << "," << r.GetBottom() << "), ("
        << r.GetRight() << "," << r.GetTop() << "))";
    return out;
}

std::istream& operator>>(std::istream& in, Rectangle& r) {
    in >> r.x >> r.y >> r.width >> r.height;
    return in;
}

int main(int argc, char** argv) {
	Rectangle r1(5, 1), r2(2, 3);
	
	cout << r1 << endl;
	cout << r2 << endl;
	
	Rectangle r3 = r1*r2;
	
	cout << "Intersection between r1 and r2" << endl;
	
	cout << r3 << endl;
	
	cout << "r1 area: " << r1.GetS() << endl;
	cout << "r2 area: " << r2.GetS() << endl;
	
	if (r1 == r2) {
		cout << "r1 and r2 are equal!!" << endl;
	} else {
		if (r1 > r2){
			cout << "r1 area is bigger!" << endl;
		} else {
			cout << "r2 area is bigger!" << endl;
		}
	}
	
	return 0;
}
