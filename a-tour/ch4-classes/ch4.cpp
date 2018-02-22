#ifdef MODE

/*  CONCRETE TYPES
    to compile
    g++ -std=c++11 -DMODE=1 ch3.cpp
    4.2.1 An arithmetic Type
 */
#if MODE==1
class complex {
  double re, im; // representation: two doubles
public:
  complex(double r, double i) : re{r},im{i} {} // construct complex from two scalars
  complex(double r) : re{r},im{0} {}           // construct complex from one scalar
  complex() : re{0},im{0} {}                   // default comple: {0,0}

  double real() const {return re;}
  double real(double d) {re=d;}
  double imag() const {return im;}
  double imag(double d) {im=d;}

  // add to re and im and return the result
  complex& operator+=(complex z) {re+=z.re;im+=z.im;return *this;}
  complex& operator-=(complex z) {re-=z.re;im-=z.im;return *this;}

  // defined out-of-class somewhere
  complex& operator*=(complex);
  complex& operator/=(complex);
};

// not required access to representation of complex
complex operator+(complex a, complex b) { return a+=b; }
complex operator-(complex a, complex b) { return a-=b; }
complex operator-(complex a) { return {-a.real(),-a.imag()}; }
complex operator*(complex a, complex b) { return a*=b; }
complex operator/(complex a, complex b) { return a/=b; }
// definitions of == and != are straightforward:
bool operator==(complex a, complex b) { // equal
  return a.real()==b.real() && a.imag()==b.imag();
}
bool operator!=(complex a, complex b) { // not equal
  return !(a==b);
}

complex sqrt(complex); // the definition is elsewhere

void f(complex z) {
  complex a{2.3};
  complex b{1/a}; // compiler do that: opeartor/=( complex{1}, a ) 
  complex c{a+z*complex{1,2.3}};
  // ...
  if (c!=b)
    c=-(b/a)+2*b;
}

/*  CONCRETE TYPES
    to compile
    g++ -std=c++11 -DMODE=2 ch3.cpp
    4.2.2 A container Type
    using dynamic memory management
    4.2.3 Initializing containers
    
 */
#elif MODE==2
#include <iostream>
#include <initializer_list>
using namespace std;
//
class Vector {
private:
  double* elem;
  int sz;
public:
  Vector(int s) :elem{new double[s]}, sz{s} {
    for (int i=0;i!=s;++i)
      elem[i]=0;
  }
  // Initializing containers
  Vector(initializer_list<double>);
  ~Vector() { delete[] elem; }
  double& operator[](int i);
  int size() const;
  // variable size
  void push_back(double); // add element at tend, increasing the size
};
void fct(int n) {
  Vector v(n);
  // use v ...
  {
    Vector v2(2*n);
    // use v and v2
  } // v2 is destroyed here
  // use v ...
} // v is destroyed here

Vector read(istream& is) {
  Vector v(0);
  for (double d;is>>d;)
    v.push_back(d);
  return v;
}

int main() {
  Vector v1 = {1,2,3,4,5}; // v1 has 5 elements
  Vector v2 = {1.23, 3.45, 6.7, 8};
}

Vector::Vector(initializer_list<double> lst) // initialize with a list
  :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
{
  copy(lst.begin(), lst.end(), elem); // copy from lst into elem
}
/*  ABSTRACT TYPES
    to compile
    g++ -std=c++11 -DMODE=3 ch3.cpp
    virtual classes
    polymorphic type
    inheritance
    virtual funcitons
    vtable
 */
#elif MODE==3
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <list>
#include <vector>
using namespace std;

class Container {
public:
  virtual double& operator[](int) = 0; // pure virtual function
  virtual int size() const = 0;        // const member function
  virtual ~Container() {}              // destructor
};

void use(Container& c) {
  const int sz=c.size();
  for (int i=0;i!=sz;++i)
    cout << c[i] << '\n';
}

class Vector {
  double* elem;
  int sz;
public:
  Vector(int s) :elem{new double[s]}, sz{s} {
    for (int i=0;i!=s;++i)
      elem[i]=0;
  }
  // Initializing containers
  Vector(initializer_list<double> lst)
    :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
    copy(lst.begin(), lst.end(), elem); // copy from lst into elem
  }
  ~Vector() { delete[] elem; }
  double& operator[](int i) {return elem[i];} 
  int size() const {return sz;}
};

class Vector_container : public Container { // Vector_container implements Container
  Vector v;
public:
  Vector_container(int s):v(s) {} // Vector of s elements
  Vector_container(initializer_list<double> lst) : v{lst} {} // Vector of s elements
  ~Vector_container() {}

  double& operator[](int i) {return v[i];}
  int size() const {return v.size();}
};

void g() {
  Vector_container vc{10,9,8,7,6,5,4,3,2,1,0};
  use(vc);
}

class List_container : public Container { // List_container implements Container
  std::list<double> ld; // (standard-library) list of doubles
public:
  List_container(){} // empty List
  List_container(initializer_list<double> il) : ld{il} {}
  ~List_container() {}

  double& operator[](int i);
  int size() const {return ld.size();}
};

double& List_container::operator[](int i) {
  for (auto& x:ld) {
    if (i==0) return x;
    --i;
  }
  throw std::out_of_range("List container");
}
void h() {
  List_container lc={1,2,3,4,5,6,7,8,9};
  use(lc);
}
/*  CLASS HIERARCHIES
    to compile
    g++ -std=c++11 -DMODE=4 ch3.cpp
 */
#elif MODE==4
class Point;

class Shape {
public:
  virtual Point center() const = 0; // pure virtual
  virtual void move(Point to) = 0;

  virtual void draw() const = 0; // draw on current "Canvas"
  virtual void rotate(int angle) = 0;

  virtual ~Shape() {}
  // ...
};

void rotate_all(vector<Shape*>& v, int angle)
// rotate v's elements by angle degrees
{
  for (auto p:v)
    p->rotate(angle);
}

class Circle : public Shape {
public:
  Circle(Point p, int rr);
  Point center() const {return x;}
  void move(Point to) {x=to;}
  void draw() const;
  void rotate(int){}
private:
  Point x; // center
  int r; // radius
};
#endif

#endif
