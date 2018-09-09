#include "file.h"

using namespace std;

bool parseCommand(string);
void ls(string[]);
void pwd(string[]);
void cd(string[]);
void mkdir(string[]);
void rmdir(string[]);
void touch(string[]);
void rm(string[]);
void chmod(string[]);
void yikes(string[]);
void exit();

Folder* root = new Folder("/");
Folder* location = root;

int main() {
  bool exitTime = false;
  while (!exitTime) {
    string command;
    cout << "clay@freyja:~$ ";
    getline(cin, command);
    exitTime = parseCommand(command);
  }
  exit(0);
}

bool parseCommand(string command) {
  string params[4];
  short i = 0;
  stringstream ssin(command);
  while (ssin.good()) {
    ssin >> params[i];
    i++;
  }
  bool ret = false;
  if (params[0] == "ls") { ls(params); }
  else if (params[0] == "pwd") { pwd(params); }
  else if (params[0] == "cd") { cd(params); }
  else if (params[0] == "mkdir") { mkdir(params); }
  else if (params[0] == "rmdir") { rmdir(params); }
  else if (params[0] == "touch") { touch(params); }
  else if (params[0] == "rm") { rm(params); }
  else if (params[0] == "chmod") { chmod(params); }
  else if (params[0] == "exit" || params[0] == "quit") {
    exit();
    ret = true;
  }
  else { yikes(params); }
  return ret;
}

void ls(string params[4]) {
  if (params[1] != "") {
    location->longList();
  } else {
    location->list();
  }
}

void pwd(string params[4]) {
  cout << location->getPathTo() << endl;
}

void cd(string params[4]) {
  location = location->goTo(params[1]);
}

void mkdir(string params[4]) {
  Folder* newDir = new Folder(params[1]);
  location->addFolder(newDir);
}

void rmdir(string params[4]) {
  if (!location->removeFolder(params[1])) {
    cout << "rmdir: " << params[1] << ": No such file or directory" << endl;
  }
}

void touch(string params[4]) { 
  File* newFile = new File(params[1]);
  location->addFile(newFile);
}

void rm(string params[4]) {
  if (!location->removeFile(params[1])) {
    cout << "rm: " << params[1] << ": No such file or directory" << endl;
  }
}

void chmod(string params[4]) {
  location->setPerms(params[1], params[2]);
}

void yikes(string params[4]) {
  cout << "bash: " << params[1] << ": command not found" << endl;
}

void exit() {
  cout << "exit" << endl;
}
