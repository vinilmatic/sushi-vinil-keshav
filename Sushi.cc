#include <iostream>
#include <iomanip>
#include "Sushi.hh"

std::string Sushi::read_line(std::istream &in)
{
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

