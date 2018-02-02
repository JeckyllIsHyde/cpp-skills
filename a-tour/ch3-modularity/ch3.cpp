/*
  3. Modularity
 */

#ifdef MODE
/* 1. Separated declaration and definition
   To compile: g++ -std=c++11 -DMODE=1 ch3.cpp && ./a.out
 */
#if MODE==1
double sqrt(double);

class Vector {
public:
  Vector(int s);
  double& operator[](int i);
  int size();
private:
  double *elem;
  int sz;
};

int main() {}

double sqrt(double d) {}

Vector::Vector(int s)
  :elem{new double[s]}, sz{s} {}
double& Vector::operator[](int i) { return elem[i]; }
int Vector::size() { return sz; }
/* To compile: g++ -DMODE=2 -o a.out ch3.cpp Vector.cpp && ./a.out
   2. Separate Compilation
 */
#elif MODE==2
// user.cpp:
#include "Vector.h"
#include <cmath>
using namespace std;

double sqrt_sum(Vector& v) {
  double sum = 0;
  for (int i=0; i!=v.size(); ++i)
    sum+=sqrt(v[i]);
  return sum;
}

int main() {}

/* To compile: g++ -DMODE=3 ch3.cpp && ./a.out
   3. Namespaces
 */
#elif MODE==3
#include <iostream>
namespace My_code {
  class complex {
  private:
    double x,y;
  public:
    complex(double real, double imag)
      :x{real}, y{imag} {}
    double real() const { return x; }
    double imag() const { return y; }
  };
  complex sqrt(complex);
  int main();
}

My_code::complex My_code::sqrt(My_code::complex z) {
  return z;
}

int My_code::main() {
  complex z{1,2};
  auto z2 = sqrt(z);
  std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
}

int main() {
  return My_code::main();
}

/* To compile: g++ -std=c++11 -DMODE=4 ch3.cpp && ./a.out
   4. Error Handling
      Exceptions:
      throw and try-catch mechanisms
 */
#elif MODE==4
#include <iostream>
#include <stdexcept> // out_of_range, length_error, bad_alloc, terminate()
#include <numeric> // iota algorithm

using namespace std;

class Vector {
public:
  Vector(int s);
  double& operator[](int i);
  int size();
private:
  double *elem;
  int sz;
};

void f(Vector& v) {
  try {
    //exceptions here are hangled by the handler defined bellow
    v[v.size()] = 7; // try to access beyond the end of v
  }
  catch (out_of_range) {
    // do something
  }
}

void user(int sz) noexcept {
  Vector v(sz);
  iota(&v[0],&v[sz],1);// fill v with 1,2,3,4,...
  // do something else
}

void test() { // rethrow an exception
  try {
    Vector v(-27);
  }
  catch (length_error) {
    // handle negative size
    cout << "test failed: length error\n";
    throw; // rethrow
  }
  catch (bad_alloc) {
    // handle memory exhaustion
    // Ouch! test() is not designed to handle memory exhaustion
    terminate();
  }
}

int main() {
  
}

Vector::Vector(int s) {
  if (s<0)
    throw length_error{"Vector::Vector() constructor"};
  elem = new double[s];
  sz=s;
}
double& Vector::operator[](int i) {
  if (i<0 || size()<=i)
    throw out_of_range{"Vector::operator[]"};
  return elem[i];
}
int Vector::size() { return sz; }

/* To compile: g++ -DMODE=5 ch3.cpp && ./a.out
   5. Error Handling
      Assertions:
 */
#elif MODE==5
#include <cassert>

constexpr double C = 299792.458; // km/s

void f(double speed) {
  constexpr double local_max = 160.0/(60*60);
  //--> ERROR: static_assert(speed<C,"can't go that fast"); // error: speed must be constant
  static_assert(local_max<C,"can't go that fast"); // OK
}

int main() {
  static_assert(4<=sizeof(int),"integers are to small"); // check integer size
}

#else
#error MODE directive must be defined !!!
#endif

#endif 
