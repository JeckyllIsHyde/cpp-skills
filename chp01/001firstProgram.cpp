#include <iostream>
// input-output is not par of the core lenguage
// it is provided as a library. Input-Output has a stream model
#include <chrono>
#include <thread>

int main() {

  std::cout << "the answer to the Ultimate Question of Life \n"
	    << "the Universe, and Everything is:"
	    << std::endl << 6*7 << std::endl;

  // portable waiting
  std::this_thread::sleep_for(std::chrono::seconds(2));
  // some variables
  int i1 = 2;              // Alingment for readability only
  int i2, i3 = 5;
  float pi = 3.14159;
  double x = -1.5e6;       // -1500000
  double y = -1.5e-6;      // -0.0000015
  char c1 = 'a', c2 = 35;
  bool cmp = i1 < pi;      // -> true
  happy = true;
  
  return 0;
}
