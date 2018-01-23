#ifdef MODE

#if MODE==1
/* The basics of C++
   1. run the minimal C++ program
      to compile $ g++ -DMODE=1 ch1.cpp && ./a.out
*/

int main() {}

#elif MODE==2
/* 2. to include I/O system use standar library
      to compile $ g++ -DMODE=2 ch1.cpp && ./a.out
*/

#include <iostream>

int main() {
  std::cout << "Hello, World!\n";
}
#elif MODE==3
/* 3. modularize your code
      to compile $ g++ -DMODE=3 ch1.cpp && ./a.out
      NOTE: Use namespaces and using
 */

#include <iostream>
using namespace std;

double square(double x) {
  return x*x;
}

void print_square(double x) {
  cout << "the squared of " << x << " is " << square(x) << '\n';
}

int main () {
  print_square(1.234);
}
#elif MODE==4
/* 4. functions
   
 */
#include <iostream>
#include <string>
using namespace std;

void print(int i) {cout << i << endl;}
void print(double d) {cout << d << endl;}
void print(string s) {cout << s << endl;}
void print(int i, double d) {cout << i << " " << d << endl;}
void print(double d, int i) {cout << d << " " << i << endl;}

void user() {
  print(42);
  print(9.65);
  print("D is for Digital");
}

int main() {
  user();
  // --> print(0,0); // ERROR overloaded function
  print(0.0,0); // no error 
}
#elif MODE==5
/* 5. Types, Variables and Arithmetic
      Initializing: narrowing vs non-narrowing
      Using auto: for long type names
      to compile need c++11 standar
         $ g++ -std=c++11 -DMODE=5 ch1.cpp
*/
#include <complex>
#include <vector>
#include <cmath>
using namespace std;
int main() {
  // built-in types
  double d1=2.3;
  double d2{2.3};
  // standar complex type
  complex<double> z=1;
  complex<double> z2{d1,d2};
  complex<double> z3={1,2}; // "=" is optional
  // standar vector container
  vector<int> v{1,2,3,4,5,6};
  // advantages of non-narrowing initializations
  int i1 = 7.2; // i1 becomes a 7 (surprise?)
  //--> int i2{7.2}; // error floating-point to integer conversion 
  //--> int i3 = {7.2}; // the same of last one
  // using auto
  auto b = true; // a bool
  auto ch = 'x'; // a char
  auto i = 123;  // an int
  auto d = 1.2;  // a double
  double y{5};
  auto yy = sqrt(y); // a sqrt(y) returned type 
}
#elif MODE==6
/* 6. Scope and Lifetime
      Local and global variables
*/
#include <vector>
#include <string>
using namespace std;

vector<int> vec; // global variable

struct Record {
  string name;  // name is a member
};

void fct(int arg) // fcn is global, arg is local
{
  string motto{"Who dares wint"}; // motto is local
  auto p = new Record{"Hume"}; // p points to an unamed Record
                               // p must be destroyed
} 

int main() {}

#elif MODE==7
/* 7. Constants
      const :  evaluated at run-time, initialize by compiler
      constexpr : evaluated at compile-time
*/
#include <vector>
using namespace std;
const int dmv = 17;
int var = 17;

constexpr double square(double x) {return x*x;}

constexpr double max1 = 1.4*square(dmv);
//--> constexpr double max2 = 1.4*square(var); // ERROR: var cannot be use on constexpr
const double max3 = 1.4*square(var); // evaluated at run-time

double sum(const vector<double>& v) {return v[0];} // declare a sum function without modify input
vector<double> v{1,2,3,4,5};
const double s1 = sum(v); // OK
//--> constexpr double s2 = sum(v); // ERROR sum(v) is not a constant expression

int main () {}
#elif MODE==8
/* 8. Pointers, Arrays and References
      nullptr
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
void copy_fct() {
  int v1[10] = {1,2,3,4,5,6,7,8,9,10};
  int v2[10]; // to become a copy of v1

  for (auto i=0;i!=10;++i)
    v2[i]=v1[1];
}

void print() {
  int v[] = {0,1,2,3,4,5,6,7,8,9};
  for (auto x : v)
    cout << x << '\n';
  for (auto x : {10,21,32,43,54,65})
    cout << x << '\n';
}

void increment() {
  int v[] = {0,1,2,3,4,5,6,7,8,9};
  for (auto& x :v)
    ++x;
}

// only declarations
void sort(vector<double>& v); // sort v
void sum(const vector<double>& v); // sort v

//
int count_x(char* p, char x)
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-terminated array of char (or to nothing)
{
  if (p==nullptr) return 0;
  int count = 0;
  for (;*p!='\0';++p)
    if (*p==x)
      ++count;
  
  return count;
}

int main() {

  char v[6]; // array of 6 characters
  char *p; // pointer to character WARNING must be initialized
  p = &v[3]; // p points to v's fourth element
  char x = *p; // *p is the object that p point to

  copy_fct();
  print();
  increment();

  char test[] = {'f','f','f','3','f','f','e','\0'};
  cout << count_x(test,'f') << endl;
}

#else
#error Must be defined a valid mode !!!
#endif // MODE==?

#endif // MODE

