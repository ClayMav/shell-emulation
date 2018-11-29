#include "file.h"
#include "memory.h"

using namespace std;

bool parseCommand(const string &);
void ls(const string[]);
void pwd(const string[]);
void cd(const string[]);
void mkdir(const string[]);
void rmdir(const string[]);
void touch(const string[]);
void rm(const string[]);
void chmod(const string[]);
void memreset(const string[]);
void memalg(const string[]);
void memset(const string[]);
void memload(const string[]);
void memstep(const string[]);
void memview(const string[]);
void memrun(const string[]);
void yikes(const string[]);
void exit();

// The root folder, and location is the current directory, will be updated with
// cd
Folder *root = new Folder("/");
Folder *location = root;

Memory mem;

int main() {
  bool exitTime = false;
  while (!exitTime) {
    string command;
    cout << "clay@freyja:~$ ";
    getline(cin, command);
    if (command.length()) {
      exitTime = parseCommand(command);
    }
  }
  delete root;
  exit(0);
}

bool parseCommand(const string &command) {
  // Will split the command string into a list of space seperated values
  string params[4];
  short i = 0;
  stringstream ssin(command);
  while (ssin.good()) {
    ssin >> params[i];
    i++;
  }
  bool ret = false;
  // Matches commands to their functions
  if (params[0] == "ls") {
    ls(params);
  } else if (params[0] == "pwd") {
    pwd(params);
  } else if (params[0] == "cd") {
    cd(params);
  } else if (params[0] == "mkdir") {
    mkdir(params);
  } else if (params[0] == "rmdir") {
    rmdir(params);
  } else if (params[0] == "touch") {
    touch(params);
  } else if (params[0] == "rm") {
    rm(params);
  } else if (params[0] == "chmod") {
    chmod(params);
  } else if (params[0] == "memreset") {
    memreset(params);
  } else if (params[0] == "memalg") {
    memalg(params);
  } else if (params[0] == "memset") {
    memset(params);
  } else if (params[0] == "memload") {
    memload(params);
  } else if (params[0] == "memstep") {
    memstep(params);
  } else if (params[0] == "memview") {
    memview(params);
  } else if (params[0] == "memrun") {
    memrun(params);
  } else if (params[0] == "exit" || params[0] == "quit") {
    exit();
    ret = true;
  } else {
    // Not a command
    yikes(params);
  }
  return ret;
}

void ls(const string params[4]) {
  if (params[1] == "-l") {
    location->longList();
  } else if (params[1] == "") {
    location->list();
  } else {
    cout << "ls: illegal option -- " << params[1] << endl;
  }
}

void pwd(const string params[4]) { cout << location->getPathTo() << endl; }

void cd(const string params[4]) { location = location->goTo(params[1]); }

void mkdir(const string params[4]) {
  Folder *newDir = new Folder(params[1]);
  location->addFolder(newDir);
}

void rmdir(const string params[4]) { location->removeFolder(params[1]); }

void touch(const string params[4]) {
  File *newFile = new File(params[1]);
  location->addFile(newFile);
}

void rm(const string params[4]) {
  if (!location->removeFile(params[1])) {
    // If file is not removed it returns false
    cout << "rm: " << params[1] << ": No such file or directory" << endl;
  }
}

void chmod(const string params[4]) { location->setPerms(params[1], params[2]); }

void memreset(const string params[4]) { mem.reset(); }
void memalg(const string params[4]) {
  if (params[1] == "first" || params[1] == "next" || params[1] == "best") {
    mem.setAlg(params[1]);
  } else {
    cout << "Choose first, next, or best" << endl;
  }
}
void memset(const string params[4]) {
  long size = atol(params[1].c_str());
  if (size < 1) {
    cout << "Please enter a valid size (>0)" << endl;
    return;
  }
  mem.setSize(size);
}
void memload(const string params[4]) { mem.load(params[1]); }
void memstep(const string params[4]) {
  if (params[1] == "all") {
    mem.step(params[1]);
    return;
  } else if (params[1] == "") {
    mem.step();
    return;
  }
  long stepSize = atol(params[1].c_str());
  mem.step(stepSize);
  return;
}
void memview(const string params[4]) { mem.print(); }
void memrun(const string params[4]) { mem.run(params[1]); }

void yikes(const string params[4]) {
  cout << "bash: " << params[0] << ": command not found" << endl;
}

void exit() { cout << "exit" << endl; }
