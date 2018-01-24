/* User defined types
 */
#ifdef MODE
/* Structures
   To compile: g++ -DMODE=1 ch2.cpp && ./a.out
*/
#if MODE==1
#include <iostream>
using namespace std;

struct Vector {
  int sz; // number of elements
  double* elem; //pointer to elements
};

void vector_init(Vector& v, int s) {
  v.elem = new double[s]; // allocate an array of doubles
  v.sz = s;
}

double read_and_sum(int s)
// read s integers from cin and return their sum;
// s is assumed to be positive
{
  Vector v;
  vector_init(v,s);
  for (int i=0; i!=s; ++i)
    cin >> v.elem[i];

  double sum = 0;
  for (int i=0; i!=s; ++i)
    sum += v.elem[i];
  return sum;
}

void f(Vector v, Vector& rv, Vector* pv)
// accessing memebers of a struct
{
  int i1 = v.sz;    // through name
  int i2 = rv.sz;   // through reference
  int i4 =  pv->sz; // through pointer
}
int main() {
  Vector v;
  cout << "Enter a vector of 3 doubles\n";
  double sum{read_and_sum(3)};
  cout << "The sum is: " << sum << std::endl;

  f(v,v,&v);
}
#elif MODE==2
/* Classes
   initialation class
*/
#include <iostream>
using namespace std;

class Vector {
public:
  Vector(int s) :elem{new double[s]}, sz{s} {} // construct a Vector
  double& operator[](int i) { return elem[i]; } // elem access: subscripting
  int size() {return sz;}
private:
  double* elem;
  int sz;
};

double read_and_sum(int s) {
  Vector v(s);
  for (int i=0;i!=v.size();++i)
    cin >> v[i];

  double sum=0;
  for (int i=0; i!=v.size(); ++i)
    sum += v[i];
  return sum;
}

int main() {
  Vector v(6); // a Vector of 6 elements
  cout << "Enter a vector of 3 doubles\n";
  double sum{read_and_sum(3)};
  cout << "The sum is: " << sum << std::endl;
}
#elif MODE==3
/* Unions
*/
#include <iostream>
using namespace std;

enum Type{str,num};

struct Entry {
  char* name;
  Type t;
  char* s; // use s if t==str
  int i; // use i if t==num
};

void f(Entry* p) {
  if (p->t == str)
    cout << p->s;
  else if (p->t == num)
    cout << p->t;
}

// a better way is,
union Value {
  char* s;
  int i;
};

struct Entry_with_union {
  char* name;
  Type t;
  Value v; 
};

void f(Entry_with_union* p) {
  if (p->t == str)
    cout << p->v.s;
  else if (p->t == num)
    cout << p->v.i;
}

int main() {}
#elif MODE==4
/* Enumerations */

#else
#error MODE directive must be defined !!!
#endif

#endif 
