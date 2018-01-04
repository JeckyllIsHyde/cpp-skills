/*
  Gradient Descent from Preface example
 */
#include <cmath>

using namespace std;

// old C-style
// function pointers makes optimization difficult
void gradient_descent( double *x, double *y,
		       double s, double eps,
		       double (*f)( double, double ),
		       double (*gx)( double, double ),
		       double (*gy)( double, double ) ) {

  double val = f(*x,*y), delta;
  do {
    *x -= s*gx(*x,*y);
    *y -= s*gy(*x,*y);
    double new_val = f(*x,*y);
    delta = abs( new_val - val );
    val = new_val;
  } while ( delta>eps );
}

// needs -std=c++11 flag
// the function call {f,g} overhead is saved, cause they are inlined.
template <typename Value,
	  typename P1, typename P2,
	  typename F, typename G>
Value gradient_descent( Value x, P1 s, P2 eps, F f, G g ) {
  auto val = f(x), delta = val;
  do {
    x -= s*g(x);
    auto new_val = f(x);
    delta = abs( new_val-val );
    val = new_val;
  } while( delta>eps );
  return x;
}
