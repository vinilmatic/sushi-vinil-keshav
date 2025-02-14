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
  UNUSED(argc);
  UNUSED(argv);
  
  
  //Check that user is in $HOME directory
  const char *directory = std::getenv("HOME");
  // DZ: No need to exit because "ok if missing"
  if (!directory) {
    std::cerr << "Error: Not in HOME environment variable";
    return EXIT_FAILURE;
  }

  //Build path to sushi.conf
  std::string config_path = std::string(directory) + "/sushi.conf";
  //Convert string to char *
  const char *configFile = config_path.c_str();
  
  //const char *configFile = "sushi.conf";

  //Check if system was able to read config file
  if (my_shell.read_config(configFile, true)) {

  } else {
    return EXIT_FAILURE;
  }
  /*
  //std::string st_test = "Hello\nWorld";
  std::string input = "Hello\\nWorld\\nyurr\\tmyguyyy\\a!!!!!!";
  //std::string input = "\\a\\b\\e\\f\\n\\r\\t\\v\\\\\\'\\\"\\?";

  std::cout << "Before unquoting and duplicating:" << std::endl;
  std::cout << input << std::endl;

  // Call the function
  std::string* result = my_shell.unquote_and_dup(input.c_str());

  std::cout << "\nAfter unquoting and duplicating:" << std::endl;
  std::cout << *result << std::endl;

    // Clean up the dynamically allocated memory
  delete result;
  //std::cout << "Hello" << std::endl;
  // A placeholder*/

  while (my_shell.get_exit_flag() == false) {

    std::cout << Sushi::DEFAULT_PROMPT;
    
    //Read line entered by user
    std::string line = my_shell.read_line(std::cin);
    //my_shell.parse_command(line);
    //Store line in history
    if (my_shell.parse_command(line) == 0) {
      my_shell.store_to_history(line);
    }
  }
  
  return EXIT_SUCCESS;
}
