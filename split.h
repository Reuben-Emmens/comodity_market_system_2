#ifndef GUARD_split_h
#define GUARD_split_h

#include <vector>
#include <list>
#include <string>

using std::string;

bool space(char c) {
  return isspace(c);
}

bool not_space(char c) {
  return !isspace(c);
}

template<class Out>
void split(const std::string& s, Out os) {

  typedef std::string::const_iterator iter;

  iter i = s.begin();

  while(i != s.end()) {

    i = find_if(i, s.end(), not_space);

    iter j = find_if(i, s.end(), space);

    if(i != s.end()) 
      *os++ = string(i, j);

    i = j;
  }
}

#endif
