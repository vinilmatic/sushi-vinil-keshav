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
  int count = 0;
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
  std::ifstream file(fname);

  if (!file.is_open()) {
    if (ok_if_missing) {
      return true;
    } else {
      std::perror("Can't open file");
      return false;
    }
  }

  while (file.good()) {
    std::string line = read_line(file);
    if (line.empty()) {
      continue;
    }

    store_to_history(line);
  }

  if (file.bad()) {
    std::perror("Can't open file");
    return false;
  }

  file.close();
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
  for (int i=history.size()-1; i < history.size(); --i) {
    std::cout << std::setw(5)
              << std::setfill(' ')
              << history.size() - i
              << "  "
              << history[i]
              << std::endl;
  }
}


