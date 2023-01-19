#define BIGINT_H
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include "bigInt.h"
using namespace std;
#define MAX 10000
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

BigInt::BigInt() { //empty constructor
	number = "0";
	sign = false;
}

BigInt::BigInt(string s) { // string constructor
	if (isdigit(s[0])) {
		number = s;
		sign  = false;
	} else {
		number = s.substr(1);
		sign = (s[0] == '-');
	}
}

BigInt::BigInt(int n) { //int constructor
	stringstream ss;
	string s;
	ss << n;
	ss >> s;
	if (isdigit(s[0])) {
		number = s;
		sign  = false;
	} else {
		number = s.substr(1);
		sign = (s[0] == '-');
	}
}

void BigInt::setNumber(string s) {
	number = s;
}

void BigInt::setSign(bool s) {
	sign = s;
}


const string& BigInt::getNumber() { // get number
	return number;
}

const bool& BigInt::getSign() { //get sign
	return sign;
}

BigInt BigInt::absolute() { // return abs
	return BigInt(number);
}

//Operators

void BigInt::operator = (BigInt b) {
	number = b.getNumber();
	sign = b.getSign();
}

bool BigInt::operator == (BigInt b) {
	return equals((*this), b);
}

bool BigInt::operator != (BigInt b) {
	return !equals((*this), b);
}

bool BigInt::operator > (BigInt b) {
	return greater((*this), b);
}

bool BigInt::operator < (BigInt b) {
	return less((*this), b);
}

bool BigInt::operator >= (BigInt b) {
	return equals((*this), b) or greater((*this), b);
}

bool BigInt::operator <= (BigInt b) {
	return equals((*this), b) or less((*this), b);
}

BigInt& BigInt::operator ++() { //prefix
	(*this) = (*this) + 1;
	return (*this);
}

BigInt BigInt::operator ++(int) { //postfix
	BigInt before = *this;
	(*this) = (*this) + 1;
	return before;
}

BigInt& BigInt::operator --() { //prefix
	(*this) = (*this) - 1;
	return (*this);
}

BigInt BigInt::operator --(int) { //postfix
	BigInt before = *this;
	(*this) = (*this) - 1;
	return before;
}

// -------------------------------------------- //

BigInt BigInt::operator + (BigInt b) {
	BigInt ans;
	if (getSign() == b.getSign()) { // both +ve or -ve
		ans.setNumber(add(getNumber(), b.getNumber()));
		ans.setSign(getSign());
	} else { //sign diff
		if (absolute() > b.absolute()) {
			ans.setNumber(subtract(getNumber(), b.getNumber()));
			ans.setSign(getSign());
		} else {
			ans.setNumber(subtract(b.getNumber(), getNumber()));
			ans.setSign(b.getSign());
		}
	}
	if (ans.getNumber() == "0")
		ans.setSign(false);

	return ans;
}

BigInt BigInt::operator - (BigInt b) {
	b.setSign(!b.getSign()); // x-y = x + (-y)
	return *this + b;
}

BigInt BigInt::operator * (BigInt b) {
	BigInt ans;
	ans.setNumber(multiply(getNumber(), b.getNumber()));
	ans.setSign(getSign() != b.getSign());

	if (ans.getNumber() == "0")
		ans.setSign(false);

	return ans;
}

// IMP IMP PROBLEM !!!!!!!!!!
//denomerator need to be long long size

BigInt BigInt::operator / (BigInt b) {
	long long den = toInt(b.getNumber()); //O(N)
	BigInt div;

	div.setNumber(divide(getNumber(), den).first); //cause it return pair
	div.setSign(getSign() != b.getSign());

	if (div.getNumber() == "0")
		div.setSign(false);

	return div;

}

//denomerator need to be in long long type
BigInt BigInt::operator % (BigInt b) {
	long long den = toInt(b.getNumber());

	BigInt rem;
	rem.setNumber(toString(divide(getNumber(), den).second));
	rem.setSign(getSign() != b.getSign());

	if (rem.getNumber() == "0")
		rem.setSign(false);

	return rem;
}

BigInt& BigInt::operator += (BigInt b) {
	*this = *this + b;
	return *this;
}

BigInt& BigInt::operator -= (BigInt b) {
	*this = *this - b;
	return *this;
}

BigInt& BigInt::operator *= (BigInt b) {
	*this = *this * b;
	return *this;
}

BigInt& BigInt::operator /= (BigInt b) {
	*this = *this / b;
	return *this;
}

BigInt& BigInt::operator %= (BigInt b) {
	*this = *this % b;
	return *this;
}

// BigInt& BigInt::operator [] (int n)
// {
// 	return *(this + (n*sizeof(BigInt)));
// }

// BigInt BigInt::operator -() // unary minus sign
// {
// 	return (*this) * -1;
// }

BigInt::operator string() {
	string signedString = getSign() ? "-" : "";
	signedString += getNumber();
	return signedString;
}


//----------------------------------------------
bool BigInt::equals(BigInt n1, BigInt n2) {
	return n1.getNumber() == n2.getNumber() and n1.getSign() == n2.getSign();
}

bool BigInt::less(BigInt n1, BigInt n2) {
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if (sign1 and !sign2) return true;
	else if (!sign1 and sign2) return false;
	else if (!sign1) { //both postive
		if (n1.getNumber().length() < n2.getNumber().length() )
			return true;
		if (n1.getNumber().length() > n2.getNumber().length() )
			return false;
		return n1.getNumber() < n2.getNumber();
	} else { //both negtive
		if (n1.getNumber().length() > n2.getNumber().length())
			return true;
		if (n1.getNumber().length() < n2.getNumber().length())
			return false;
		return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
	}
}

bool BigInt::greater(BigInt n1, BigInt n2) {
	return !equals(n1, n2) and !less(n1, n2);
}


//add to string
string BigInt::add(string number1, string number2) { //O(N)
	string add = number1.length() > number2.length() ? number1 : number2;
	char carry = '0';
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if (number1.size() > number2.size()) // add 0 from left for smaller one
		number2.insert(0, differenceInLength, '0');
	else if (number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for (int i = number1.size() - 1; i >= 0; i--) {
		add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';
		if (i != 0) {
			if (add[i] > '9') {
				add[i] -= 10;
				carry = '1';
			} else carry = '0';
		}
	}
	if (add[0] > '9') {
		add[0] -= 10;
		add.insert(0, 1, '1');
	}

	return add;
}

string BigInt::subtract(string number1,string number2) {
	string sub = number1.length() > number2.length() ? number1 : number2;
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if(number1.size() > number2.size())
		number2.insert(0,differenceInLength,'0');
	if(number1.size() < number2.size())
		number1.insert(0,differenceInLength,'0');

	for(int i=number2.size()-1;i>=0;i--) {
		if(number[i] < number2[i]) {
			number1[i] += 10;
			number1[i-1]--;
		}
		sub[i] = ((number1[i]-'0') - (number2[i]-'0')) + '0';
	}

	while(sub[0] == '0' and sub.length() != 1) //erasing leading zeros
		sub.erase(0,1);
	return sub;
}


string BigInt::multiply(string n1,string n2) {
	if(n1.length() > n2.length())
		swap(n1,n2);

	string res = "0";
	for(int i=n1.length()-1;i>=0;--i) {
		string temp = n2;
		int currentDigit = n1[i] - '0';
		int carry = 0;

		for(int j=temp.length()-1;j>=0;--j) {
			temp[j] = ((temp[j] - '0') * currentDigit) + carry;

			if(temp[j] > 9) {
				carry = temp[j]/10;
				temp[j] -= (carry*10);
			}else{
				carry = 0;
			}

			temp[j] += '0';
		}

		if(carry > 0)
			temp.insert(0,1,(carry+'0'));

		temp.append((n1.length()-i-1),'0');

		res = add(res,temp);
	}

	while(res[0] == '0' and res.length() != 1) {
		res.erase(0,1);
	}

	return res;
}

// divides string on long long, returns pair(qutiont, remainder)
pair<string, long long> BigInt::divide(string n, long long den)
{
	long long rem = 0;
	string result; result.resize(MAX);

	for(int indx=0, len = n.length(); indx<len; ++indx)
	{
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

//-------------------------------------------------------------
// converts long long to string
string BigInt::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

//-------------------------------------------------------------
// converts string to long long
long long BigInt::toInt(string s)
{
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}
