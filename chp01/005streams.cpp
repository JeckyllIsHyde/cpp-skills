#include <iostream>
#include <fstream>
#include <sstream>

#include <iomanip>

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

  // manipulators
  double pi = M_PI;
  int old_precision = std::cout.precision();
  // output format
  std::cout << "pi is " << pi << '\n';
  std::cout << "pi is " << std::setprecision(16) << pi << '\n';
  std::cout << "pi is " << std::setw(30) << pi << '\n';
  std::cout << "pi is " << std::setfill('-') << std::left
	    << std::setw(30) << pi << '\n';
  std::cout << "pi is " << std::scientific << pi << '\n';
  std::cout.setf(std::ios_base::showpos);
  std::cout << "pi is " << std::scientific << pi << '\n';
  // in a different base
  std::cout << "63 octal is " << std::oct << 63 << '\n';
  std::cout << "63 hexadecimal is " << std::hex << 63 << '\n';
  std::cout << "63 decimal is " << std::dec << 63 << '\n';
  // output format for booleans
  std::cout << "pi < 3 is " << (pi < 3) << '\n';
  std::cout << "pi < 3 is " << std::boolalpha << (pi < 3) << '\n';

  // saving old format configurations
  std::cout << "General Format: set and unset\n";
  std::cout << "pi is " << pi << '\n'
	    << "pi < 3 is " << (pi < 3) << '\n';
  std::cout << std::setprecision(16);
  std::cout << "pi is " << pi << '\n'
	    << "pi < 3 is " << (pi < 3) << '\n';
  std::cout.unsetf(std::ios_base::adjustfield |
		   std::ios_base::basefield |
		   std::ios_base::floatfield |
		   std::ios_base::showpos |
		   std::ios_base:: boolalpha);
  std::cout << "pi is " << pi << '\n'
	    << "pi < 3 is " << (pi < 3) << '\n';
  std::cout.precision(old_precision);
  std::cout << "pi is " << pi << '\n'
	    << "pi < 3 is " << (pi < 3) << '\n';

  // dealing with I/O errors
  { // read non-existing file, the program goes on
    std::ifstream infile("some_missing_file.xyz"); // not throw exception

    int i;
    double d;
    infile >> i >> d;

    std::cout << "i is " << i << ", d is " << d << '\n';
    infile.close();
  }
  { // to be sure about the input, checking until, for a real file
    std::ifstream infile;
    std::string filename{"some_missing_file.xyz"};
    bool opened = false;
    while (!opened) {
      infile.open(filename);
      if (infile.good())
	opened = true;
      else
	std::cout << "The file '" << filename
		  << "' doesn't exist, give a new file name: ",
	  std::cin >> filename;
      
    }
    int i;
    double d;
    infile >> i >> d;

    if (infile.good())
      std::cout << "i is " << i << ", d is " << d << '\n';
    else
      std::cout << "Could not correctly read the content.\n";
    infile.close();
  }
  { // enabling exceptions

  }
  
  return 0;
}
