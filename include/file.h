#ifndef FILE_H
#define FILE_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

class File {
protected:
  // m_modified is an array of three strings. month in Mmm format, day of the
  // month, and time, formatted as hh:mm
  string m_modified[3];
  string m_ownerperm, m_groupperm, m_publicperm, m_owner, m_name;
  int m_size;

public:
  File(const string &name);
  ~File();
  string getName() const;
  string getMonth() const;
  string getDay() const;
  string getTime() const;
  string getPerms() const;
  string getOwner() const;
  int getSize() const;
  void setSize();
  void updateTime();
  void changePerms(const string &numStr);
  void changeOwner(const string &owner);
};

class Folder : public File {
protected:
  vector<File *> files;
  vector<Folder *> folders;
  Folder *last;

public:
  Folder(const string &name);
  ~Folder();
  void list() const;
  void longList() const;
  string getPathTo() const;
  bool addFile(File *newFile);
  bool addFolder(Folder *newFolder);
  bool removeFile(const string &target);
  bool removeFolder(const string &target);
  Folder *goTo(const string &folderName);
  void setPerms(const string &numStr, const string &target);
};

#endif
