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

  Sushi sushi;

  /*std::cout << "Enter a line: ";
  std::string line = sushi.read_line(std::cin);
  sushi.store_to_history(line);
  std::cout << "Command history: " << std::endl;
  sushi.show_history();*/

  const char *configFile = "sushi.conf";
  std::cout << "Testing read_config with file: " << configFile << "\n";
  if (sushi.read_config(configFile, false)) {
    std::cout << "Config file successfully read.\n";
  } else {
    std::cerr << "Failed to read config file.\n";
  }

  std::cout << "History after reading config file:\n";
  sushi.show_history();
  

  // A placeholder
  std::cout << Sushi::DEFAULT_PROMPT << "Hello, world!" << std::endl;
  
  return EXIT_SUCCESS;
}
