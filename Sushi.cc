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
#include <csignal>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits>
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

  char* const* argv = exe->vector2array();

  int child_pid;

  switch(child_pid = fork()) {
    case -1:
      std::perror("fork");
      exit(EXIT_FAILURE);
    case 0:
      execvp(argv[0], argv);
      std::perror("execvp");
      exe->free_array(argv);
      exit(EXIT_FAILURE);
    default:
      if(waitpid(child_pid, NULL, 0)==-1){
        std::perror("waitpid");
        return EXIT_FAILURE;
      }
  }

  return EXIT_SUCCESS;
}

//bool Sushi::exit_requested = false;

void Sushi::prevent_interruption() {
  // Must be implemented
  struct sigaction cancel_action;
  //memset(&cancel_action, 0, sizeof(cancel_action));
  cancel_action.sa_handler = refuse_to_die;
  cancel_action.sa_flags=SA_RESTART;
  //sigemptyset(&cancel_action.sa_mask);
  sigaction(SIGINT, &cancel_action, NULL);
}

void Sushi::refuse_to_die(int signo) {
  // Must be implemented
  UNUSED(signo);
  std::cerr << "Type exit to exit the shell" << std::endl;
  //std::cin.clear();  // Clears the error flag
  //std::cin.ignore(); 
}

char* const* Program::vector2array() {
  // Must be implemented
  if (!args || args->empty()) return nullptr;  // Handle empty input

  size_t size = args->size();
  char** argv = new char*[size + 1];  // Allocate array of char* (one extra for NULL)

  for (size_t i = 0; i < size; i++) {
      argv[i] = const_cast<char*>((*args)[i]->c_str());  // Convert std::string* to char*
  }

  argv[size] = nullptr;  // Null-terminate the array
  return argv;
  //return nullptr; 
}

void Program::free_array(char *const argv[]) {
  // Must be implemented
  UNUSED(argv);
  delete[] argv;
}

Program::~Program() {
  // Do not implement now
}
