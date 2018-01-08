/**
   Operators:
   Arithmetics: ++,+,*,%
   Boolean:
   * Comparison: <=, !=,...
   * Logic: && and ||
   Bitwise: ~, <<, >>, &, ^ and |
   Asignment: =, +=,...
   Program flow: funtion call, ?:, and ,
   Memory handling: new and delete
   Access: ., ->, [], *,...
   Type handling: dynamic_cast, typeid, sizeof, alignof ...
   Error handling: throw
 **/

#include <iostream>

#include <typeinfo> // for handing types

int main() {

  int i=3; // =: assign operator
  i++; // post-increment, modify i after line was computed
  const int j=5;
  // j++; // error j is constant, addressable data item is Lvalue
  // (3+5)++; // eoror, 3+5 is noly a temprary

  { // pre- and post- increment operator
    int i=3, j=3;
    int k = ++i + 4; // i is 4, k is 8
    int l = j++ + 4; // j is 4, k is 7
  }
  { // unary operators
    int i = 3;
    int j = -i; // j is -3
  }

  {
    const float r1 = 3.5, r2 = 7.3, pi = 3.14159;

    float area1 = pi*r1*r1;

    std::cout << "A circle of radius " << r1 << " has area "
	      << area1 << "." << std::endl;
    std::cout << "The aveage of " << r1 << " and " << r2 << " is "
	      << (r1+r2)/2 << "." << std::endl;
  }
  { // automatic conversions
    long l =  1234567890123;
    long l2 = l+1.0f-1.0; // imprecise
    long l3 = l+(1.0f-1.0); // correct
    std::cout << "l:" << l << std::endl;
    std::cout << "l2:" << l2 << std::endl;
    std::cout << "l3:" << l3 << std::endl;
  }
  {
    // type handling, it must be used #include <typeinfo>
    char c = 'a';
    std::cout << "typeid(c): " << typeid(c).name()
	      << ", sizeof(c): " << sizeof c << std::endl;
    unsigned short int usi = 1;
    std::cout << "typeid(usi): " << typeid(usi).name()
	      << ", sizeof(usi): " << sizeof usi << std::endl;
    short int si = 1;
    std::cout << "typeid(si): " << typeid(si).name()
	      << ", sizeof(si): " << sizeof si << std::endl;
    int i = 1;
    std::cout << "typeid(i): " << typeid(i).name()
	      << ", sizeof(i): " << sizeof i << std::endl;
    long int li = 1;
    std::cout << "typeid(li): " << typeid(li).name()
	      << ", sizeof(li): " << sizeof li << std::endl;
    long long int lli = 1;
    std::cout << "typeid(lli): " << typeid(lli).name()
	      << ", sizeof(lli): " << sizeof lli << std::endl;
    unsigned int ui = 1;
    std::cout << "typeid(ui): " << typeid(ui).name()
	      << ", sizeof(ui): " << sizeof ui << std::endl;
    float f = 1.0f;
    std::cout << "typeid(f): " << typeid(f).name()
	      << ", sizeof(f): " << sizeof f << std::endl;
    double d = 1.0;
    std::cout << "typeid(d): " << typeid(d).name()
	      << ", sizeof(d): " << sizeof d << std::endl;
    long double ld = {1.0};
    std::cout << "typeid(ld): " << typeid(ld).name()
	      << ", sizeof(ld): " << sizeof ld << std::endl;
  }
  {
    double x = 2.0, xn = 1.0, exp_x = 1.0;
    unsigned long fac = 1;
    for (unsigned long i=1; i<=10; ++i) {
      xn*=x;
      fac*=i;
      exp_x+=xn/fac;
      std::cout << "e^x is " << exp_x << '\n';
    }
  }
  { // c++11
    // range-based for-loop 
    int primes[] = {2,3,5,7,11,13,17,19};
    for (int i : primes)
      std::cout << i << " " ;
    std::cout << std::endl;
  }
  
  return 0;
}
