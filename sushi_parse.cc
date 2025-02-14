#include "Sushi.hh"

std::string *Sushi::unquote_and_dup(const char* s)
{
  //Initialize variables
  std::string conversion = s;
  size_t alert(0);
  size_t backspace(0);
  size_t escape(0);
  size_t formfeed(0);
  size_t newline(0);
  size_t carr_return(0);
  size_t hor_tab(0);
  size_t ver_tab(0);
  size_t backslash(0);
  size_t apostrophe(0);
  size_t quotation(0);
  size_t question(0);

  //Replace escape sequences with actual values
  while ((alert = conversion.find("\\a", alert)) != std::string::npos){
    conversion.replace(alert, 2, "\a");
    alert++;
  }
  while ((backspace = conversion.find("\\b", backspace)) != std::string::npos){
    conversion.replace(backspace, 2, "\b");
    backspace++;
  }
  while ((escape = conversion.find("\\e", escape)) != std::string::npos){
    conversion.replace(escape, 2, "\e");
    escape++;
  }
  while ((formfeed = conversion.find("\\f", formfeed)) != std::string::npos){
    conversion.replace(formfeed, 2, "\f");
    formfeed++;
  }
  while ((newline = conversion.find("\\n", newline)) != std::string::npos){
    conversion.replace(newline, 2, "\n");
    newline++;
  }
  while ((carr_return = conversion.find("\\r", carr_return)) != std::string::npos){
    conversion.replace(carr_return, 2, "\r");
    carr_return++;
  }
  while ((hor_tab = conversion.find("\\t", hor_tab)) != std::string::npos){
    conversion.replace(hor_tab, 2, "\t");
    hor_tab++;
  }
  while ((ver_tab = conversion.find("\\v", ver_tab)) != std::string::npos){
    conversion.replace(ver_tab, 2, "\v");
    ver_tab++;
  }
  while ((backslash = conversion.find("\\\\", backslash)) != std::string::npos){
    conversion.replace(backslash, 2, "\\");
    backslash++;
  }
  while ((apostrophe = conversion.find("\\'", apostrophe)) != std::string::npos){
    conversion.replace(apostrophe, 2, "\'");
    apostrophe++;
  }
  while ((quotation = conversion.find("\\\"", quotation)) != std::string::npos){
    conversion.replace(quotation, 2, "\"");
    quotation++;
  }
  while ((question = conversion.find("\\?", question)) != std::string::npos){
    conversion.replace(question, 2, "\?");
    question++;
  }

  return new std::string(conversion); // Must be changed
}

void Sushi::re_parse(int i) {
  UNUSED(i);
// Must be implemented
  int max_size = history.size();
  if (i == 0 || i > max_size) {
    std::cerr << "Error: !" << i << ": event not found" << std::endl;
  } else {
    std::string command = history[history.size()-i];
    int result = parse_command(command);
    if (result != 0) {
      store_to_history(command);
    }
  }  
}

//---------------------------------------------------------------
// Do not modify this function YET
std::string *Sushi::getenv(const char* s) 
{
  return new std::string(s); // Must be changed - eventually
}

//---------------------------------------------------------------
// Do not modify this function
void yyerror(const char* s) {
  std::cerr << "Parse error: " << s << std::endl;
}

