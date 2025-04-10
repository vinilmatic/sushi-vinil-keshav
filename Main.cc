/*Name: Vinil Keshav
  Assignment: Reading and Storing Commands
  Description: This program contains the main function that tests all the Sushi class methods 
  described in the implementation file
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include "Sushi.hh"

Sushi my_shell; // New global var
// Initialize the static constants
const size_t Sushi::MAX_INPUT = 256;
const size_t Sushi::HISTORY_LENGTH = 10;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

int main(int argc, char *argv[])
{
  // Use argc and argv!
  // DZ: This is not an error
  /*
  if (argc == 1) {
    std::cerr << "Missing script file" << std::endl;
    exit(EXIT_FAILURE);
  }
  */
  for (int i=1; i < argc; i++) {
    // DZ: This is really BAD. Suggested:
    // if(!my_shell.read_config(argv[i], false)) {
    //   exit(EXIT_FAILURE);
    // }
    bool success = my_shell.read_config(argv[i], false);
    if (success==true) {
      continue;
    } else {
      // DZ: already reported
      // std::cerr << "Error reading script file" << std::endl;
      exit(EXIT_FAILURE);
     }
    
  }

  my_shell.mainloop();
  
  return EXIT_SUCCESS;
}
