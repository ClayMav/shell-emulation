#include "file.h"

// Map which contains the permission numbers and their corresponding strings
map<string, string> PERM = {{"0", "---"}, {"1", "--x"}, {"2", "-w-"},
                            {"3", "-wx"}, {"4", "r--"}, {"5", "r-x"},
                            {"6", "rw-"}, {"7", "rwx"}};

File::File(const string &name) { m_name = name; }

File::~File() {}

string File::getName() const { return m_name; }

string File::getMonth() const { return m_modified[0]; }

string File::getDay() const { return m_modified[1]; }

string File::getTime() const { return m_modified[2]; }

string File::getPerms() const {
  return PERM[m_ownerperm] + PERM[m_groupperm] + PERM[m_publicperm];
}

string File::getOwner() const { return m_owner; }

int File::getSize() const { return m_size; }

void File::setSize() {
  srand(time(NULL));
  int size = rand() % 2048 + 1;
  m_size = size;
}

void File::updateTime() {
  time_t t = time(0);
  // now stores the current time
  tm *now = localtime(&t);
  char buf[80];

  // Month
  strftime(buf, sizeof(buf), "%b", now);
  m_modified[0] = buf;
  // Day
  strftime(buf, sizeof(buf), "%e", now);
  m_modified[1] = buf;
  // Time
  strftime(buf, sizeof(buf), "%H:%M", now);
  m_modified[2] = buf;
}

void File::changePerms(const string &numStr) {
  m_ownerperm = numStr[0];
  m_groupperm = numStr[1];
  m_publicperm = numStr[2];
}

void File::changeOwner(const string &owner) { m_owner = owner; }
