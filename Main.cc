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

  // DZ: Moved to globals (not a mistake)
  //Create Sushi object
  // Sushi sushi;

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

  // DZ: Unneeded message
  // std::cout << "Testing read_config with file: " << config_path << "\n";

  //Check if system was able to read config file
  // DZ: Must be `true`, not `false`
  if (my_shell.read_config(configFile, false)) {
    // DZ: Unneeded message
    // std::cout << "Config file successfully read.\n";
  } else {
    // DZ: Duplicate error message
    // std::cerr << "Failed to read config file.\n";
    return EXIT_FAILURE;
  }
  
  // A placeholder
  // DZ: Unneeded message after the prompt
  std::cout << Sushi::DEFAULT_PROMPT /*<< "Enter a line: "*/;

  //Read line entered by user
  std::string line = my_shell.read_line(std::cin);
  //Store line in history
  my_shell.store_to_history(line);
  //Print out history of read lines
  // DZ: Unneeded message after the prompt
  // std::cout << "Command history: " << std::endl;
  my_shell.show_history();
  
  return EXIT_SUCCESS;
}
