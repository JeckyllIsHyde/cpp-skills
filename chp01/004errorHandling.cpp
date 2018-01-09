/** 1.6 HANDLING ERRORS
    1.6.1 Assertions: for detecting programming errors.
      Defensive Programming !!!
      Use as many propertities as you can
    1.6.2 Exceptions: exceptional situation tha prevent 
    proper continuation of de program.
 **/
#include <iostream>
#include <fstream>
#include <cassert> // use -DNDEBUG to use assertions
// g++ -std=c++11 -DNDEBUG 004errorHandling.cpp
#include <cstdlib> // exit(EXIT_FAILURE);

double square_root( double x ) {
  // assertions for the input
  // check_somehow(x>=0);
  double result = x;
  
  // assertions for the output
  assert(result >= 0.0);
  return result;
}

// old style to handle errors
int read_matrix_file(const char* fname) {
  std::fstream f(fname);
  if (!f.is_open())
    return 1;
  return 0;
}

// (throw, try-catch) style to handle errors
int read_matrix_file_with_exceptions(const char* fname) {
  std::fstream f(fname);
  if (!f.is_open())
    throw "Cannot open the file. CAUSE: not exists the file";
  return 0;
}

// (throw, try-catch and exception types) style to handle errors
struct cannot_open_file {};
int read_matrix_file_with_exceptions_and_exception_types(const char* fname) {
  std::fstream f(fname);
  if (!f.is_open())
    throw cannot_open_file{};
  return 0;
}

int main() {

  square_root(1);
  // square_root(-2); // with -DNDEBUG a silent error

  // old style to handle errors
  if (read_matrix_file("non_existing_file.txt")!=0)
    std::cout << "cannot open the file, cause not exists!!" << std::endl;
  
  // (throw, try-catch) style to handle errors
  try {
    read_matrix_file_with_exceptions("non_existing_file.txt");
  } catch (...) {
    std::cout << "we can continue for now!!" << std::endl;
  }

  // (throw, try-catch and exception types) style to handle errors
  try {
    read_matrix_file_with_exceptions_and_exception_types("non_existing_file.txt");
  } catch (cannot_open_file& e) {
    std::cerr << "cerr: we can continue for now!!" << std::endl;
    // exit(EXIT_FAILURE); // #include <cstdlib>
  }

  // really handling errors
  bool keep_trying=true;
  do {
    char fname[80]; // std::string is better
    std::cout << "Please enter the file name: ";
    std::cin >> fname;
    try {
      read_matrix_file_with_exceptions_and_exception_types(fname);
      keep_trying = false;
    } catch (cannot_open_file& e) {
      std::cout << "Could not open the file. Try another one!\n";
    } catch (...) {
      std::cout << "Something is fishy here. Try another file!\n";
    }
  } while(keep_trying);

  // there is a type of assertions for compilation time
  // with the keyword: static_assert
  
  return 0;
}
