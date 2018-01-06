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
  
  return 0;
}
