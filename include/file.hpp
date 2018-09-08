#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
class File {
  protected:
    short m_ownerperm, m_groupperm, m_publicperm;
    string m_owner;
    string m_name;
  public:
    File(string name) {
      m_name = name;
    }
    string getName() {
      return m_name;
    }
    void changePerms(short num, string owner) {
      string numStr = to_string(num);
      m_ownerperm = numStr[0];
      m_groupperm = numStr[1];
      m_publicperm = numStr[2];
      m_owner = owner;
    }
};

class Folder: public File {
  protected:
    vector<File> files;
  public:
    Folder(string name) : File(name) {}
    bool addFile(File newFile) {
      for (int i = 0; i < files.size(); i++) {
        if (files[i].getName() == newFile.getName()) {
          return false;
        }
      }
      files.push_back(newFile);
      return true;
    }
    bool removeFile(File target) {
      for (int i = 0; i < files.size(); i++) {
        if (files[i].getName() == target.getName()) {
          files.erase(files.begin() + i);
          return true;
        }
      }
      return false;
    }
    void list() {
      if (files.size() == 0) {
        cout << endl;
      } else {
        for(int i=0; i<files.size(); ++i) {
          cout << files[i].getName() << "\t\t";
        }
        cout << endl;
      }
    }
};
