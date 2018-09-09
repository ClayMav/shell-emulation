#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

class File {
  protected:
    string m_modified[3];
    string m_ownerperm, m_groupperm, m_publicperm, m_owner, m_name;
    int m_size;
  public:
    File(string name);
    ~File();
    string getName();
    string getMonth();
    string getDay();
    string getTime();
    string getPerms();
    string getOwner();
    int getSize();
    void setSize();
    void updateTime();
    void changePerms(string numStr);
    void changeOwner(string owner);
};

class Folder: public File {
  protected:
    vector<File*> files;
    vector<Folder*> folders;
    Folder* last;
  public:
    Folder(string name);
    ~Folder();
    bool addFile(File* newFile);
    bool addFolder(Folder* newFolder);
    bool removeFile(string target);
    bool removeFolder(string target);
    void list();
    void longList();
    Folder* goTo(string folderName);
    string getPathTo();
    void setPerms(string numStr, string target);
};

#endif
