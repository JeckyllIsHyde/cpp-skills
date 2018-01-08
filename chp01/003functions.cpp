#include <iostream>
#include <cmath>

int divide(int a, int b) {
  return a/b;
}

float divide(float a, float b) {
  return std::floor(a/b);
}

int main( int argc, char* argv[]) {
  int x = 5, y = 2;
  float n = 5.0, m = 2.0;
  std::cout << divide(x,y) << std::endl;
  std::cout << divide(n,m) << std::endl;
  // std::cout << divide(x,m) << std::endl; // error ambiguous
  { // reading inputs for main
    for (int i=0;i<argc;i++)
      std::cout << argv[i] << std::endl;
  }
}
