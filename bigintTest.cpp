//Marley Schneider
//CECS 325-02
//Prog 6 - BigInt
//
//5/9/2024
//
//I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program

#include <iostream>
#include <vector>
#include <iomanip>
#include <limits.h>
using namespace std;

class BigInt{
  private:
    vector<char> digits;
    BigInt fibohelper(BigInt n = 0, BigInt a = 0, BigInt b = 1);
    BigInt facthelper(BigInt product, BigInt n);

  public:
    BigInt();
    BigInt(int);
    BigInt(string);

    BigInt operator+ (BigInt);
    BigInt operator+ (int);
    BigInt operator- (BigInt);
    BigInt operator- (int);
    BigInt operator* (BigInt);
    BigInt operator/ (BigInt);
    BigInt operator% (BigInt);
    BigInt operator++ (int);
    BigInt operator++ ();
    BigInt operator[] (int);
    bool operator< (BigInt);
    bool operator== (BigInt);

    void print();
    int size();
    BigInt fibo();
    BigInt fact();

    friend ostream& operator<<(ostream&, const BigInt);
    friend BigInt operator+(int, BigInt);
};

// CONSTRUCTOR
BigInt::BigInt(){
  vector<char> digits;
}

// INT CONSTRUCTOR
BigInt::BigInt(int n){
  if (n == 0)
    digits.push_back(0);
  else
  while (n > 0){
    char digit = n % 10;
    digits.push_back(digit);
    n /= 10;
  }
}

// STRING CONSTRUCTOR
BigInt::BigInt(string s){
  for (auto it1 = s.rbegin();it1 != s.rend();it1++){
    digits.push_back(int(*it1 - 48));
  }
}

// ADDITION BIGINT
BigInt BigInt::operator+(BigInt b){
  vector<char> temp;
  auto it1 = digits.begin();
  auto it2 = b.digits.begin();
  bool it1_done = false, it2_done = false;
  int carry = 0;
  while(!it1_done || !it2_done){
    int d2,d1;
    if (it2 < b.digits.end())
      d2 = int(*it2);
    else
      d2 = 0;
    if (it1 < digits.end())
      d1 = int(*it1);
    else
      d1 = 0;
    int result = d1 + d2 + carry;
    if (result == 10){
      carry = 1;
      result = 0;    
    }  
    else if (result > 9){
      carry = 1;
      result = result % 10;
    }

    else
      carry = 0;
    char digit = result;
    temp.push_back(digit);
    if (it1 == digits.end())
      it1_done = true;
    if (it2 == b.digits.end())
      it2_done = true;
    it1++;it2++;
    if (it1 == digits.end())
      it1_done = true;
    if (it2 == b.digits.end())
      it2_done = true;
  }

  if (carry > 0){
    char char_carry = carry;
    temp.push_back(char_carry);
  }

  string chars = "";
  for (auto it3 = temp.rbegin();it3 != temp.rend();it3++){  
     chars += *it3 + 48;
  }

  BigInt x(chars);
  return x;

}

// ADDITION BIGING + INT
BigInt BigInt::operator+(int n){
  BigInt temp(n);
  return *this + temp;
}

// ADDITION BIGING + INT
BigInt operator+(int n, BigInt b){
  BigInt temp(n);
  return b + temp;
}

// SUBTRACTION BIGINT
BigInt BigInt::operator-(BigInt b){
  vector<char> v1_copy (digits.size());
  vector<char> v2_copy (b.digits.size());
  copy(digits.begin(), digits.end(), v1_copy.begin());
  copy(b.digits.begin(), b.digits.end(), v2_copy.begin());
  vector<char> temp;
  auto it1 = v1_copy.begin();
  auto it2 = v2_copy.begin();

  while(it2 != v2_copy.end()){
    int d1 = int(*it1), d2 = int(*it2);

    if (d1 < d2){
      auto it3 = it1 + 1;
      while (int(*it3) == 0 && it3 != v1_copy.end()){
        *it3 = 9;
        it3++;
      }
      int temp_int = int(*it3) - 1;
      char temp_char = temp_int;
      *it3 = temp_char;
      d1 += 10;
    }

    int result = d1 - d2;
    char digit = result;
    temp.push_back(digit);
    it1++;it2++;
    }

  while (it1 != v1_copy.end()){
    temp.push_back(*it1);
    it1++;
  }

  auto it5 = temp.end() - 1;
  while (int(*it5) == 0 && it5 != temp.begin()){
    temp.erase(it5);
    it5--;
  }
  
  string chars = "";
  for (auto it4 = temp.rbegin();it4 != temp.rend();it4++)
     chars += *it4 + 48;

  BigInt x(chars);
  return x;
}

// SUBTRACTION INT
BigInt BigInt::operator-(int n){
  BigInt temp(n);
  return *this - temp;
}

// BIGINT MULTIPLICATION
BigInt BigInt::operator*(BigInt b){
  BigInt product(0);
  BigInt a;
  BigInt c;
  if (b < *this){
    a = *this;
    c = b;
  }
  else{
    a = b;
    c = *this;
  }
  for (BigInt i = 0;i < c; i++){
    product = product + a;
//    cout << "i < c: " << i << " < " << c << endl;
  }
  return product;
}
// BIGINT DIVISION
BigInt BigInt::operator/(BigInt b){
  BigInt temp(*this);
  BigInt quotient(0);
  while (b - 1 < temp){
    // cout << "again" << endl;
    temp = temp - b;
    // cout << "b - 1 < temp: " << (b - 1) << " < " << temp << endl;
    quotient++;
    // cout << "quotient: " << quotient << endl << endl;
  }
  // cout << "done" << endl;
  return quotient;
}

// BIGINT MODULUS
BigInt BigInt::operator%(BigInt b){
  BigInt quotient(*this / b);
  BigInt x(*this - (quotient * b));
  return x;
}

//BIGINT++ PRE
BigInt BigInt::operator++(){
  *this = *this + 1;
  return (*this);
}

// BIGINT++ POST
BigInt BigInt::operator++(int){
  BigInt temp = *this;

  *this = *this + 1;

  return temp;
}

// BIGINT FACTHELPER
BigInt BigInt::facthelper(BigInt product, BigInt n){ 
  if (n == 0)
    return product;
  else{
    return facthelper(BigInt (product * n), BigInt (n - 1));
  }
}

// BIGINT FACT
BigInt BigInt::fact(){
  return facthelper(BigInt (*this), BigInt (*this - 1));
}

//BIGINT FIBOHELPER
BigInt BigInt::fibohelper(BigInt n, BigInt a, BigInt b){
  if (n == *this)
    return a;
  else{
    return fibohelper(n + 1, b, (a + b));  
  }
}

//BIGINT FIBO
BigInt BigInt::fibo(){
  return fibohelper();
}

// BIGINT <
bool BigInt::operator<(BigInt b){
  // cout << "digits.size < b.digits.size: " << digits.size() << " < " << b.digits.size() << endl << endl;
  if (digits.size() < b.digits.size())
    return true;
  else if (b.digits.size() < digits.size())
    return false;
  else{
    int i1 = digits.size() - 1, i2 = b.digits.size() - 1;
    // cout << "digits[i1] == digits[i2]" << int(digits[i1]) << " == " << int(b.digits[i2]) << endl << endl;
    while (int(digits[i1]) == int(b.digits[i2])){
      i1=i1 - 1;i2=i2 - 1;
      // cout << "i1 == -1: " << i1 << " == -1" << endl << endl;
      if (i1 == -1)
        break;
      // cout << "digits[i1] == digits[i2]" << int(digits[i1]) << " == " << int(b.digits[i2]) << endl << endl;
    }
    // cout << "digits[i1] < digits[i2]: " << int(digits[i1]) << " < " << int(b.digits[i2]) << endl << endl;
    if (int(digits[i1]) < int(b.digits[i2]))
      return true;
    else
      return false;
  }
}

// BIGINT ==
bool BigInt::operator==(BigInt b){
  if (digits.size() != b.digits.size())
    return false;
  else{
    for (auto it1 = digits.begin(), it2 = b.digits.begin(); it1 != digits.end(); it1++){
      if (int(*it1) == int(*it2))
        it2++;
      else
        return false;
    }
    return true;
  }
}

// INDEX 
BigInt BigInt::operator[](int n){
  BigInt x(digits[digits.size() - 1 - n]);
  return x;
}

// BIGINT PRINT
void BigInt::print(){
  for (auto it = digits.rbegin(); it != digits.rend(); it++)
    cout << int(*it);
}

// SIZE
int BigInt::size(){
  return digits.size();
}

//BIGINT COUT
ostream& operator<<(ostream& out, BigInt b){
  vector<char>::reverse_iterator it1 = b.digits.rbegin();
  if (b.digits.size() < 13){
    while (it1 != b.digits.rend())
      out << int(*it1++);
    return out;
  }
  else{
    out << int(*it1);
    it1++;
    out << '.';
    for (int i = 0; i<6; i++){
      out << int(*it1);
      it1++;
    }
    out << "e" << b.digits.size() - 1;
    return out;
  }
}

void testUnit()
{
int space = 10;
cout << "\a\nTestUnit:\n"<<flush;
system("whoami");
system("date");
// initialize variables
BigInt n1(25);
BigInt s1("25");
BigInt n2(1234);
BigInt s2("1234");
BigInt n3(n2);
BigInt fibo(12345);
BigInt fact(50);
BigInt imax = INT_MAX;
BigInt big("9223372036854775807");
// display variables
cout << "n1(int) :"<<setw(space)<<n1<<endl;
cout << "s1(str) :"<<setw(space)<<s1<<endl;
cout << "n2(int) :"<<setw(space)<<n2<<endl;
cout << "s2(str) :"<<setw(space)<<s2<<endl;
cout << "n3(n2) :"<<setw(space)<<n3<<endl;
cout << "fibo(12345):"<<setw(space)<<fibo<<endl;
cout << "fact(50) :"<<setw(space)<<fact<<endl;
cout << "imax :"<<setw(space)<<imax<<endl;
cout << "big :"<<setw(space)<<big<<endl;
cout << "big.print(): "; big.print(); cout << endl;
cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
cout << "fact("<<fact<<") = "<<fact.fact() << endl;
cout << "10 + n1 = " << 10+n1 << endl;
cout << "n1 + 10 = " << n1+10 << endl;
cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;
cout << "s2 * big = ? --> "<< s2 * big<<endl;
cout << "big * s2 = ? --> "<< big * s2<<endl;
}

int main() {
  testUnit();
}
