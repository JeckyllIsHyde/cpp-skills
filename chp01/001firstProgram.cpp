#include <iostream>
// input-output is not par of the core lenguage
// it is provided as a library. Input-Output has a stream model
#include <chrono>
#include <thread>

#include <complex>

#include <string>

int main() {

  std::cout << "the answer to the Ultimate Question of Life \n"
	    << "the Universe, and Everything is:"
	    << std::endl << 6*7 << std::endl;

  // portable waiting #include <thread>  and #include <chrono>
  std::this_thread::sleep_for(std::chrono::seconds(2));
  // some variables
  int i1 = 2;              // Alingment for readability only
  int i2, i3 = 5;
  float pi = 3.14159;
  double x = -1.5e6;       // -1500000
  double y = -1.5e-6;      // -0.0000015
  char c1 = 'a', c2 = 35;
  bool cmp = i1 < pi,      // -> true
		  happy = true;
  // c++11 can deduce the type of variables
  auto i4 = i3+7;

  // const attribute
  { 
    const int ci1 = 2;
    // const int ci3; // Error: no value
    const float pi = 3.14159;
    const char cc = 'a';
    const bool cmp = ci1 < pi;
  }
  // literals
  {
    2; // int
    2u; // unsigned int
    2l; // long
    2ul; // unsigned long
    2ll; // long long
    2ull; // long long
    2.0; // double
    2.0f; // float
    2.0l; // long double
    // using complex templates
    std::complex<float> z(1.3,2.4), z2; // #include <complex>
    // arthmetic is only between same type
    // z2 = 2*z; // error no int*complex<float>
    // z2 = 2.0*z; // error no double*complex<float>
    z2 = 2.0f*z; // error no float*complex<float>
    // accurancy
    long double third1 = 0.3333333333333333333;
    long double third2 = 0.3333333333333333333l;
  }
  // non-decimal numbers
  // octal numbers
  int o1 = 042;
  // int o2 = 084; // Error! no 8 in octals
  // hexadecimals
  int h1 = 0x42;
  int h2 = 0xfa;
  // c++14 binary, g++ -std=c++11 works!
  int b1 = 0b11111010; // int b1 = 250;
  // c++14 apostrophes
  // long d = 6'546'678'616'861'129l;
  // string literals
  char s1[] = "Old C style"; // better not
  std::string s2 = "In C++ beter like this"; // #include <string>
  std::string s3 = "This is a very long and clumsy text"
    "that is too long for one line.";
  {
    // non-narrowing initialization
    int i1 = 3.14; // compiles despite narrowing (our risk)
    // int i1n = {3.14}; // narrowing error fractional part lost
    unsigned u2 = -3;
    // unsigned u2n = {-3}; // narrowing error negative part
    double d = 7.0;
    // float f2 = {d}; // warning narrowing conversion
    unsigned u3 = {3};
    int i2 = {2};
    // unsigned u4 = {i2}; // narrowing warning: no negative values
    // int i3 = {u3}; // narrowing warning: not all large values
  }
  // HIDING and SCOPES
  {
    int a=5; // define a#1
    {
      a=3; // assign a#1
      int a; // define a#2
      a=8; // assign a#2
      {
	a=7; // assing a#2
      }
    }
    a = 11; // assign a#1
  }
  
  return 0;
}
