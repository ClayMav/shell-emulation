#include "file.h"

Folder::Folder(string name) : File(name), last(NULL) {}

Folder::~Folder() {
  if (files.size() != 0) {
    for (int i = 0; i < files.size(); i++) {
      delete files[i];
    }
  }
  if (folders.size() != 0) {
    for (int i = 0; i < folders.size(); i++) {
      delete folders[i];
    }
  }
  last = NULL;
}

bool Folder::addFile(File* newFile) {
  for (int i = 0; i < files.size(); i++) {
    if (files[i]->getName() == newFile->getName()) {
      files[i]->updateTime();
      return false;
    }
  }
  for (int i = 0; i < folders.size(); i++) {
    if (folders[i]->getName() == newFile->getName()) {
      folders[i]->updateTime();
      return false;
    }
  }
  newFile->updateTime();
  newFile->setSize();
  newFile->changePerms("644");
  newFile->changeOwner("clay");
  files.push_back(newFile);
  return true;
}

bool Folder::addFolder(Folder* newFolder) {
  string name = newFolder->getName();
  for (int i = 0; i < files.size(); i++) {
    if (files[i]->getName() == name) {
      files[i]->updateTime();
      return false;
    }
  }
  for (int i = 0; i < folders.size(); i++) {
    if (folders[i]->getName() == name) {
      folders[i]->updateTime();
      cout << "mkdir: " << name << ": File exists" << endl;
      return false;
    }
  }
  newFolder->updateTime();
  newFolder->setSize();
  newFolder->changePerms("755");
  newFolder->changeOwner("clay");
  folders.push_back(newFolder);
  return true;
}

bool Folder::removeFile(string target) {
  for (int i = 0; i < files.size(); i++) {
    if (files[i]->getName() == target) {
      delete files[i];
      files.erase(files.begin() + i);
      return true;
    }
  }
  
  return false;
}

bool Folder::removeFolder(string target) {
  for (int i = 0; i < folders.size(); i++) {
    if (folders[i]->getName() == target) {
      delete folders[i];
      folders.erase(folders.begin() + i);
      return true;
    }
  }
  for (int i = 0; i < files.size(); i++) {
    if (files[i]->getName() == target) {
      cout << "rmdir: " << target << ": Not a directory" << endl;
      return true;
    }
  }
  cout << "rmdir: " << target << ": Directory not empty" << endl;
  return false;
}

void Folder::list() {
  if (files.size() != 0) {
    vector<string> names;
    for(int i=0; i<files.size(); ++i) {
      names.push_back(files[i]->getName());
    }
    for(int i=0; i<folders.size(); ++i) {
      names.push_back(folders[i]->getName());
    }
    sort( names.begin(), names.end() );
    for(int i=0; i<names.size(); ++i) {
      cout << names[i] << "\t\t";
    }
    cout << endl;
  }
}

void Folder::longList() {
  if (files.size() != 0) {
    cout << "total " << files.size() + folders.size() << endl;
    vector<File*> sortedFiles = files;
    sort( sortedFiles.begin(), sortedFiles.end() );
    for(int i=0; i < sortedFiles.size(); ++i) {
      cout << '-' + sortedFiles[i]->getPerms() << "\t"
        << "2" << "\t"
        << sortedFiles[i]->getOwner() << "\t"
        << "staff" << "\t"
        << sortedFiles[i]->getSize() << "\t"
        << sortedFiles[i]->getMonth() << "\t"
        << sortedFiles[i]->getDay() << "\t"
        << sortedFiles[i]->getTime() << "\t"
        << sortedFiles[i]->getName() << endl;
    }
    vector<Folder*> sortedFolders = folders;
    sort( sortedFolders.begin(), sortedFolders.end() );
    for(int i=0; i < sortedFolders.size(); ++i) {
      cout << 'd' + sortedFolders[i]->getPerms() << "\t"
        << "2" << "\t"
        << sortedFolders[i]->getOwner() << "\t"
        << "staff" << "\t"
        << sortedFolders[i]->getSize() << "\t"
        << sortedFolders[i]->getMonth() << "\t"
        << sortedFolders[i]->getDay() << "\t"
        << sortedFolders[i]->getTime() << "\t"
        << sortedFolders[i]->getName() << endl;
    }
  }
}

Folder* Folder::goTo(string folderName) {
  if (folderName == ".." || folderName == "../") {
    return last;
  }
  for (int i = 0; i < folders.size(); i++) {
    if (folders[i]->getName() == folderName) {
      folders[i]->last = this;
      return folders[i];
    }
  }
  cout << "bash: cd: " << folderName << ": Not a directory" << endl;
  return this;
}

string Folder::getPathTo() {
  string out = this->getName();
  Folder* onwards = this->last;
  if (this->last == NULL) {
    return out;
  }
  while ( onwards->last != NULL ) {
    out = onwards->getName() + "/" + out;
    onwards = onwards->last;
  }
  out = onwards->getName() + out;
  return out;
}

void Folder::setPerms(string numStr, string target) {
  if (numStr[0] < 0 || numStr[0] > 7 || numStr[1] < 0 || numStr[1] > 7 || numStr[2] < 0 || numStr[2] > 7) {
    cout << "chmod: Invalid file mode: " << numStr << endl;
    return;
  }
  for(int i=0; i<files.size(); ++i) {
    if (files[i]->getName() == target) {
      files[i]->changePerms(numStr);
    }
  }
  for(int i=0; i<folders.size(); ++i) {
    if (folders[i]->getName() == target) {
      folders[i]->changePerms(numStr);
    }
  }
}
