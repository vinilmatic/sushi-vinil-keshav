/*Name: Vinil Keshav
  Assignment: Reading and Storing Commands
  Description: This is the implementation file that contains the implementation of the Sushi class 
  methods found in the header file.
*/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include "Sushi.hh"

std::string Sushi::read_line(std::istream &in)
{
  //Used Zinoviev's read_line solution to make it more efficient
  std::string line;
  if(!std::getline (in, line)) {// Has the operation failed?
    if(!in.eof()) { 
      std::perror("getline");
    }
    return "";
  }
    
  // Is the line empty?
  if(std::all_of(line.begin(), line.end(), isspace)) {
    return "";
  }

  // Is the line too long?
  if(line.size() > MAX_INPUT) {
    line.resize(MAX_INPUT);
    std::cerr << "Line too long, truncated." << std::endl;
  }
  
  return line; // A placeholder
}

bool Sushi::read_config(const char *fname, bool ok_if_missing)
{
  //Open file for reading
  std::ifstream file(fname);

  //Handles two situations if the file is unable to be opened
  if (!file.is_open()) {
    if (ok_if_missing) {
      return true;
    } else {
      std::perror(fname);
      return false;
    }
  }

  //Reads the lines in the config file
  while (file.good()) {
    std::string line = read_line(file);
    int result = parse_command(line);

    // DZ: This check will be done in `store_to_history`
    //Skips empty lines
    if (line.empty()) {
      continue;
    }

    // DZ: This operation does not belong in this function
    //Stores the lines in history
    if (result == 0) {
      store_to_history(line);
    }
  }

  //Prints error message if file could not be opened
  if (file.bad()) {
    std::perror(fname);
    return false;
  }

  // DZ: C++ closes all local ifstreams automatically
  //Clear all previous flags set
  file.clear();
  //Close file
  file.close();

  return true; // A placeholder
}

void Sushi::store_to_history(std::string line)
{
  //If the line is nullptr, don't insert anything
  if (line.empty()) {
    return;
  }

  //insert new line at top of history
  history.push_front(line);

  //if history is full, remove oldest entry
  if (history.size() > HISTORY_LENGTH) {
    history.pop_back(); //removes oldest entry
  }
}

void Sushi::show_history()
{
  //Iterate through the deque backwards because the first line is at the back of the deque
  for (int i=history.size()-1; i >= 0; i--) {
    std::cout << std::setw(5)
              << std::setfill(' ')
              << history.size() - i
              << "  "
              << history[i] 
              << std::endl;
  }
}


void Sushi::set_exit_flag()
{
  // To be implemented
  exit_flag = true;
}

bool Sushi::get_exit_flag() const
{
  return exit_flag; // To be fixed
}

//---------------------------------------------------------
// New methods
int Sushi::spawn(Program *exe, bool bg)
{
  // Must be implemented
  UNUSED(exe);
  UNUSED(bg);

  return EXIT_SUCCESS;
}

void Sushi::prevent_interruption() {
  // Must be implemented
}

void Sushi::refuse_to_die(int signo) {
  // Must be implemented
  UNUSED(signo);
}

char* const* Program::vector2array() {
  // Must be implemented
  return nullptr; 
}

void Program::free_array(char *const argv[]) {
  // Must be implemented
  UNUSED(argv);
}

Program::~Program() {
  // Do not implement now
}
