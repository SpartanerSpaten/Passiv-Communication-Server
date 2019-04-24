#pragma once

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

class Note{
public:
  Note(string&, unsigned int, string&);
  ~Note();
  time_t created;
  string message;
  unsigned int id;
  string category;
};
