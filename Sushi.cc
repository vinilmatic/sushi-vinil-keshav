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
  //std::string response = "Read";
  //return response;
  std::string buffer;
  char ch;
  size_t count = 0;
  bool exceeded = false;

  //read characters from an input stream
  while (in.get(ch)) {
    if (ch == '\n') {
      break;
    }
    if (count < MAX_INPUT) {
      buffer += ch;
    } else {
      exceeded = true;
    }
    ++count;
  }

  if (in.bad()) {
    std::perror("Input error");
    return "";
  }

  if (exceeded) {
    std::cerr << "Line too long, truncated." << std::endl;
  }

  if (buffer.empty() || std::all_of(buffer.begin(), buffer.end(), [](unsigned char c) { return std::isspace(c); })) {
    return "";
  }
  return buffer; // A placeholder
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
      std::perror("Can't open file");
      return false;
    }
  }

  //Reads the lines in the config file
  while (file.good()) {
    std::string line = read_line(file);

    //Skips empty lines
    if (line.empty()) {
      continue;
    }

    //Stores the lines in history
    store_to_history(line);
  }

  //Prints error message if file could not be opened
  if (file.bad()) {
    std::perror("Can't open file");
    return false;
  }

  //Clear all previous flags set
  file.clear();
  //Close file
  file.close();

  //Print error if file is unable to be closed
  if (file.fail()) {
    std::perror("Can't close file");
    return false;
  }

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
  int deque_size = history.size();
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


