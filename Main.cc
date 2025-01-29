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

// Initialize the static constants
const size_t Sushi::MAX_INPUT = 256;
const size_t Sushi::HISTORY_LENGTH = 10;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);

  //Create Sushi object
  Sushi sushi;

  //Check that user is in $HOME directory
  const char *directory = std::getenv("HOME");
  if (!directory) {
    std::cerr << "Error: Not in HOME environment variable";
    return EXIT_FAILURE;
  }

  //Build path to sushi.conf
  std::string config_path = std::string(directory) + "/sushi.conf";
  //Convert string to char *
  const char *configFile = config_path.c_str();
  std::cout << "Testing read_config with file: " << config_path << "\n";

  //Check if system was able to read config file
  if (sushi.read_config(configFile, false)) {
    std::cout << "Config file successfully read.\n";
  } else {
    std::cerr << "Failed to read config file.\n";
    return EXIT_FAILURE;
  }
  
  // A placeholder
  std::cout << Sushi::DEFAULT_PROMPT << "Enter a line: ";

  //Read line entered by user
  std::string line = sushi.read_line(std::cin);
  //Store line in history
  sushi.store_to_history(line);
  //Print out history of read lines
  std::cout << "Command history: " << std::endl;
  sushi.show_history();
  
  return EXIT_SUCCESS;
}
