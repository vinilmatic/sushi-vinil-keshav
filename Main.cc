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

  const char *home_dir = std::getenv("USERPROFILE");
  if (!home_dir) {
    std::cerr << "Error: Not in HOME environment variable";
    return EXIT_FAILURE;
  }

  std::string config_path = std::string(home_dir) + "/sushi.conf";

  const char *configFile = config_path.c_str();
  std::cout << "Testing read_config with file: " << config_path << "\n";
  if (sushi.read_config(configFile, false)) {
    std::cout << "Config file successfully read.\n";
  } else {
    std::cerr << "Failed to read config file.\n";
  }
  
  // A placeholder
  std::cout << Sushi::DEFAULT_PROMPT << "Enter a line: ";

  //std::cout << "Enter a line: ";
  std::string line = sushi.read_line(std::cin);
  sushi.store_to_history(line);
  std::cout << "Command history: " << std::endl;
  sushi.show_history();
  
  return EXIT_SUCCESS;
}
