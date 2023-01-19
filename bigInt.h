#include<string>

using namespace std;

#define MAX 10000 // this will be the max size of bigInt

class BigInt {
private:
	string number;
	bool sign;

	bool equals(BigInt n1, BigInt n2);
	bool less(BigInt n1, BigInt n2);
	bool greater(BigInt n1, BigInt n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string n1, string n2);
	pair<string, long long> divide(string n, long long den);
	string toString(long long n);
	long long toInt(string s);
public:
	BigInt();  //empty constructor
	BigInt(string s); //string constructor
	BigInt(int n); //int constructor
	void setNumber(string s);
	void setSign(bool s);
	const string& getNumber(); //get Number
	const bool& getSign(); //get Sign
	BigInt absolute(); // return ansolute value

	//operations
	void operator = (BigInt b);
	bool operator == (BigInt b);
	bool operator != (BigInt b);
	bool operator > (BigInt b);
	bool operator < (BigInt b);
	bool operator >= (BigInt b);
	bool operator <= (BigInt b);
	BigInt& operator ++(); //prefix
	BigInt operator ++(int); //postfix
	BigInt& operator --(); //prefix
	BigInt operator --(int); //postfix
	BigInt operator + (BigInt b);
	BigInt operator - (BigInt b);
	BigInt operator * (BigInt b);
	BigInt operator / (BigInt b);
	BigInt operator % (BigInt b);
	BigInt& operator += (BigInt b);
	BigInt& operator -= (BigInt b);
	BigInt& operator *= (BigInt b);
	BigInt& operator /= (BigInt b);
	BigInt& operator %= (BigInt b);

	// BigInt operator [] (int n);
	// BigInt operator -(); //unary minus sign
	operator string(); //to convert BigInt to string
};
