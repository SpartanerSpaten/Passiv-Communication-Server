#include "./note.h"
#include <ctime>

Note::Note(std::string& input, unsigned int iid, std::string& icategory){
  message = input;
  created = std::time(nullptr);
  id = iid;
  category = icategory;
}

Note::~Note(){}
