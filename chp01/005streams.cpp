#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>

void write_something(std::ostream& os) {
  os << "Hi stream, did you know that 3*3 = " << 3*3 << std::endl;
}

int main() {

  double x=5;
  std::cout << "The square root of " << x << " is " << sqrt(x) << std::endl;

  // low priority of operators
  std::cout << "11*19 " << 11*19 << std::endl;
    
  // ?: with parentheses
  int age;
  std::cout << "introduce your age [a number]:";
  std::cin >> age;
  std::cout << ( age>65 ? "I'm a wise guy.\n": "I am still half-baked.\n") << std::endl;

  // output files
  // std::ofstream square_file;
  // square_file.open("squares.txt");
  // or just
  std::ofstream square_file("squares.txt");
  for (int i=0; i<10; ++i)
    square_file << i << "^2 = " << i*i << std::endl;
  // square_file.close(); // needed an explicit close() when goes output the scope

  // generic stream concepts: in Boost.Asio for TCP/IP and Boost.IOSream for general
  // in stringsstream for strings with methods str() 

  // generic function for streams
  std::ofstream myfile("example.txt");
  std::stringstream mysstream;

  write_something(std::cout);
  write_something(myfile);
  write_something(mysstream);

  std::cout << "mysstream is: " << mysstream.str(); // newline contained
  
  return 0;
}
