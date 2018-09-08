#include <iostream>
#include <sstream>
#include "file.hpp"

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
void exit(string[]);
void yikes();

Folder root("/");

int main() {
  bool exitTime = false;
  while (!exitTime) {
    string command;
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
    exit(params);
    ret = true;
  }
  else { yikes(); }
  return ret;
}

void ls(string command[]) {
  root.list();
}

void pwd(string[]) {
  cout << "You ls'd" << endl;
}
void cd(string[]) {
  cout << "You cd'd" << endl;
}
void mkdir(string params[4]) {
  Folder newDir(params[1]);
  root.addFile(newDir);
}
void rmdir(string[]) {
  cout << "You rmdir'd" << endl;
}
void touch(string params[4]) { 
  File newFile(params[1]);
  root.addFile(newFile);
}
void rm(string[]) {
  cout << "You rm'd" << endl;
}
void chmod(string[]) {
  cout << "You chmod'd" << endl;
}
void exit(string[]) {
  cout << "You exit'd" << endl;
}

void yikes() {
  // TODO make real message
  cout << "Command not found" << endl;
}
