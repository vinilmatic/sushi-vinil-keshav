#include "Sushi.hh"

std::string *Sushi::unquote_and_dup(const char* s)
{
  // DZ: This implementation is very inefficient, it is more than 10 times
  // slower than it could be. Also, you do not need 12 size_t variables,
  // one is enough

  //Replaced my inefficient implementation with Professor Zinoviev's implementation
  
  if (!s) { // Not required, but it is safer this way
    return nullptr;
  }
  
  std::string result;
  while (*s) {
    if (*s == '\\') {
      if (*(s + 1)) {
	switch (*(s + 1)) {
	case 'a': result += '\a'; break;
	case 'b': result += '\b'; break;
	case 'e': result += '\x1B'; break;
	case 'f': result += '\f'; break;
	case 'n': result += '\n'; break;
	case 'r': result += '\r'; break;
	case 't': result += '\t'; break;
	case 'v': result += '\v'; break;
	case '\\': result += '\\'; break;
	case '\'': result += '\''; break;
	case '"': result += '"'; break;
	default:
	  result += *s;
	  result += *(s + 1);
	  break;
	}
	s += 2; // Skip escape sequence
      } else { // Dangling \ at the EOS; undefined behavior
	result += '\\';
	return new std::string(result); 
      }
    } else {
      result += *s;
      ++s;
    }
  }
  return new std::string(result);// Must be changed
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
// Implement the function
std::string *Sushi::getenv(const char* s) 
{
  const char* name = std::getenv(s);
  if (name == nullptr) {
    return new std::string("");
  } else {
    return new std::string(name); // Must be changed - eventually
  }
}

// Implement the function
void Sushi::putenv(const std::string* name, const std::string* value)
{
  //UNUSED(name);
  //UNUSED(value);

  const char* env_name = name->c_str();
  const char* env_value = value->c_str();

  if (setenv(env_name, env_value, 1) != 0) {

  }

  delete name;
  delete value;
}

//---------------------------------------------------------------
// Do not modify this function
void yyerror(const char* s) {
  std::cerr << "Parse error: " << s << std::endl;
}

