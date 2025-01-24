#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdio>
#include "Sushi.hh"

std::string Sushi::read_line(std::istream &in)
{
  std::string buffer;
  char ch;
  int count = 0;
  bool exceeded = false;

  //read characters from an input stream
  while (in.get(ch)) {
    if (ch == '/n') {
      break;
    }
    if (count < MAX_INPUT) {
      buffer += ch;
    } else {
      exceeded = true;
    }
    ++count;

    if (in.bad()) {
      std::perror("Input error");
      return nullptr;
    }

    if (exceeded) {
      std::cerr << "Line too long, truncated." << std::endl;
    }
  }
  return nullptr; // A placeholder
}

bool Sushi::read_config(const char *fname, bool ok_if_missing)
{
  return false; // A placeholder
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
  for (size_t i=0; i < history.size(); ++i) {
    std::cout << std::setw(5)
              << std::setfill('0')
              << i + 1
              << "  "
              << history[i]
              << std::endl;
  }
}

