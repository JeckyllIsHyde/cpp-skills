#ifdef MODE

/*  4.2 CONCRETE TYPES
    to compile
    g++ -std=c++11 -DMODE=1 ch4.cpp
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

/*  4.2 CONCRETE TYPES
    to compile
    g++ -std=c++11 -DMODE=2 ch4.cpp
    4.2.2 A container Type
    using dynamic memory management
    4.2.3 Initializing containers
    using std::intializer_list<double>
    
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
/*  4.3 ABSTRACT TYPES
    to compile
    g++ -std=c++11 -DMODE=3 ch4.cpp
    virtual classes (e.g a class with method virtual double& operator[](int) = 0;)
    polymorphic type
    inheritance (e.g class Son: public Parent {}; )

    4.4 VIRTUAL FUNCTIONS 
    (e.g a method with virtual double& operator[](int) = 0;)
    virtual function table (vtbl) a funciton pointer array for inheritance
       Container
       |__ virtual interface
           |__ operator[](int) = 0;
	   |__ size() const = 0;
	   |__ ~Container() = 0;
       Vector_container <- Container
       |__ vtbl -> |___ Vector_container::operator[](int) const;
       |           |___ Vector_container::size() const;
       |	   |___ Vector_container::~Vector_container():
       |__ (v) Vector

       List_container <- Container
       |__ vtbl -> |___ List_container::operator[](int) const;
                   |___ List_container::size() const;
		   |___ List_container::~List_container():
       |__ (ld) std::list

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
/*  4.5 CLASS HIERARCHIES
    to compile
    g++ -std=c++11 -DMODE=4 -DUNIQUEPTR=1 ch4.cpp

    Shape |-> Triangle
          |-> Circle -> Smiley 
    4.5.1 override: explicit overriding for inheritance
    override keyword must be put only on declaration
    4.5.2 two kind of benefits
      1. Interface inheritance: 
         e.g Cicle can be used as a Shape pointer
      2. Implementation inheritance: 
         e.g Smile can use Cicle::draw() method
    hint: small concrete classes are like built-in types
    that is local variables, acces them using their manes,
    copy them around. Classes in class hierarchies are 
    different, we tend to allow them on free store using
    new, and using pointers or references. 
    4.5.3 hierarchy navigation
      1. dynamic_cast<> operator: recovering original type
      2. nullptr return
      3. bad_cast thrown exception
      4. unique_ptr<> for avoiding resource leaks 
 */
#elif MODE==4
#include <iostream>
#include <typeinfo>
#include <vector>
#include <memory>
using namespace std;

class Point {
};

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
  Point center() const override{return x;}
  void move(Point to) override {x=to;}
  void draw() const override;
  void rotate(int) override {}
private:
  Point x; // center
  int r; // radius
};

class Smiley : public Circle { // use the circle as the base for a face
public:
  Smiley(Point p, int r): Circle(p,r), mouth(nullptr) {}
  ~Smiley()
  {
    delete mouth;
    for (auto p:eyes)
      delete p;
  }
  void move(Point to) override;
  void draw() const override;
  void rotate(int) override;
  void add_eye(Shape* s) {eyes.push_back(s);}
  void set_mouth(Shape* s);
  virtual void wink(int i); // wink eye number i

private:
  vector<Shape*> eyes; // usually tow eyes
  Shape* mouth;
};

class Triangle : public Shape {
public:
  Triangle(Point p1, Point p2, Point p3);
  ~Triangle() {
    for (auto p:points)
      delete p;
  }
  Point center() const override;
  void move(Point to) override;
  void draw() const override;
  void rotate(int) override;
private:
  vector<Point*> points;
};

void Smiley::draw() const {
  Circle::draw();
  for (auto p: eyes)
    p->draw();
  mouth->draw();
}

enum class Kind {circle, triangle, smiley};

#if DUNIQUEPTR==0
Shape* read_shape(istream& is) // read shape descriptions from input strea is
{
  Kind k;
  switch(k) {
  case Kind::circle:
    // read circle data {Point, int} into p and r
    Point p; int r;
    // std::cin >> p >> r;
    return new Circle{p,r};
  case Kind::triangle:
    // read triangle data {Point, Point, Point} into p1, p2 and p3
    Point p1, p2, p3;
    // std::cin >> p1 >> p2 >> p3;
    return new Triangle{p1,p2,p3};
  case Kind::smiley:
    // read smiley data {Point, int, Shape, Shape, Shape} into p, r, e1, e2 and m
    Smiley* ps =  new Smiley{p,r};
    Shape *e1, *e2, *m;
    ps->add_eye(e1);
    ps->add_eye(e2);
    ps->set_mouth(m);
    return ps;
  }
}

#elif DUNIQUEPTR==1
unique_ptr<Shape> read_shape(istream &is)
// read shape header from is and find its Kind k
{
  Kind k;
  switch(k) {
  case Kind::circle:
    // read circle data {Point, int} into p and r
    Point p; int r;
    // std::cin >> p >> r;
    return unique_ptr<Shape>{new Circle{p,r}};
  case Kind::triangle:
    // read triangle data {Point, Point, Point} into p1, p2 and p3
    Point p1, p2, p3;
    // std::cin >> p1 >> p2 >> p3;
    return unique_ptr<Shape>{new Triangle{p1,p2,p3}};
  case Kind::smiley:
    // read smiley data {Point, int, Shape, Shape, Shape} into p, r, e1, e2 and m
    Smiley* ps =  new Smiley{p,r};
    Shape *e1, *e2, *m;
    ps->add_eye(e1);
    ps->add_eye(e2);
    ps->set_mouth(m);
    return unique_ptr<Shape>{ps};
  }  
}

void rotate_all_unique_ptr(vector< unique_ptr<Shape> >& v, int angle)
// rotate v's elements by angle degrees
{
  for (auto p:v)
    p->rotate(angle);
}

void user() {
  vector< unique_ptr<Shape> > v;
  while (cin)
    v.push_back(read_shape(cin));
  // draw_all_unique_ptr(v); // call draw() for each element
  rotate_all_unique_ptr(v,45); // call rotate(45) for each element
} // all Shapes implicit destroyed
#endif

int main() {

  { // using generic read_shape and recover original type
    Shape* ps{read_shape(cin)};
    if (Smiley* p = dynamic_cast<Smiley*>(ps)) { //
      // is the Smiley pointer to by ps
    }
    else { // if dynamic_cast<T*> doesn't match, then returns nullptr
      // not a Smiley, try something else ...
    }
  }
  { // code is cleaner when dynamic_cast<> is used with restraint 
    try {
      Shape* ps{read_shape(cin)};
      Smiley& r{dynamic_cast<Smiley&>(*ps)};
    } catch (bad_cast) {
      // catching the std::bad_cast
    }
  }

#if DUNIQUEPTR==1
  {
    user();
  }
#endif  
}

/*
  4.6 Copy and Move
  to compile
  g++ -std=c++11 -DMODE=5 ch4.cpp
  
  4.6.1 Copying containers
    Copy constructor
    Copy assignment
  4.6.2 Moving containers
    using T&& to avoid copying a Vector twice for
    T w = x+y+z;
    rvalues and pasing a function returning T like "T fcn()";
  4.6.3 Essential operations
    constructors for default, copy, move
    assignments for copy and move
*/
#elif MODE==5
#include <iostream>
#include <initializer_list>
using namespace std;

class complex {
  double re, im; // representation: two doubles
public:
  complex() : re{0},im{0} {}                   // default comple: {0,0}
  complex(double r, double i) : re{r},im{i} {} // construct complex from two scalars
};

void test(complex z1)
{
  complex z2{z1}; // copy initialization
  complex z3;

  z3=z2; // copy assignment
  // ...
}

class Vector {
private:
  double* elem;
  int sz;
public:
  Vector(int s);
  ~Vector() { delete[] elem; }

  Vector(const Vector& a);  // Copy constructor
  Vector& operator=(const Vector& a); // Copy assignment
  
  Vector(Vector&& a);  // Move constructor
  Vector& operator=(Vector&& a); // Move assignment

  double& operator[](int i);
  const double& operator[](int i) const;

  int size() const;
};

Vector::Vector(int s)
  :elem{new double[s]}, sz{s}
{
  for (int i=0;i!=s;++i)
    elem[i]=0;
}
Vector::Vector(const Vector& a)
  :elem{new double[a.sz]}, sz{a.sz}
{
  for (int i=0;i!=sz;++i)
    elem[i]=a.elem[i];
}
Vector& Vector::operator=(const Vector& a) // copy assignment
{
  double* p = new double[a.sz];
  for (int i=0; i!=a.sz; ++i)
    p[i] = a.elem[i];
  delete[] elem;
  elem = p;
  sz = a.sz;
  return *this;
}
Vector::Vector(Vector&& a)
  :elem{a.elem}, sz{a.sz}
{
  a.elem = nullptr;
  a.sz = 0;
}

void bad_copy(Vector v1)
// without redefine copy constructor and copy assignment
{
  Vector v2 = v1; // copy v1's representation ingo v2
  v1[0] = 2; // v2[0] is now also 2!
  v2[1] = 3; // v1[1] is now also 3!
}

struct Vector_size_mismatch{};

Vector operator+(const Vector& a, const Vector& b) {
  if (a.size()!=b.size())
    throw Vector_size_mismatch{};

  Vector res(a.size());

  for (int i=0;i!=a.size(); ++i)
    res[i] = a[i]+b[i];
  return res;
}

void f(const Vector& x, const Vector& y, const Vector&z) {
  Vector r(x.size());
  //..
  r = x+y+z; // use move constructors to avoid copy loads
  //..
}

Vector f() {
  Vector x(1000);
  Vector y(1000);
  Vector z(1000);
  z=x; // we get a copy
  y = std::move(x); // we get a move
  return z; // we get a move
}

class Sometype{};

class X {
public:
  X(Sometype);            // "ordinary constructor": create an object
  X();                    // default constructor
  X(const X&);            // copy constructor
  X(X&&);                 // move constructor
  X& operator=(const X&); // copy assigment: clean up target and copy
  X& operator=(X&&);      // move assigment: clean up target and move
  ~X();                   // destructor: clean up
};
    
int main() {
  test(complex{1,2});
 
}

#endif

#endif
