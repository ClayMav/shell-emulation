#ifndef MEMORY_H
#define MEMORY_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Entry {
public:
  long m_start;
  long m_size;
  long m_duration;
  long m_pos = -1;
  bool m_done = false;
  Entry(const long &start, const long &size, const long &duration)
      : m_start(start), m_size(size), m_duration(duration) {}
};

class Memory {
protected:
  vector<Entry *> *m_actions = NULL;
  vector<bool> *m_mem = NULL;
  string m_alg = "NULL";
  long m_size = -1;
  long m_last = 0;
  long m_pos = 0;
  long m_time = -1;

public:
  Memory() {}
  ~Memory() { this->clear(); }
  void clear() {
    if (this->m_mem != NULL)
      delete this->m_mem;
    if (this->m_actions != NULL) {
      const long size = this->m_actions->size();
      for (long i = 0; i < size; i++) {
        delete this->m_actions->at(i);
      }
      this->m_actions->clear();
      delete this->m_actions;
    }
  }
  void setSize(const long &size) { this->m_size = size; }
  void setAlg(const string &alg) { this->m_alg = alg; }
  void reset() {
    this->clear();

    this->m_alg = "NULL";
    this->m_size = -1;
    this->m_last = 0;
    this->m_pos = 0;
    this->m_time = -1;
    this->m_mem = NULL;
    this->m_actions = NULL;
  }
  void load(const string &filename) { this->load(filename, 0); }
  void load(const string &filename, const long &skip) {
    if (this->m_size == -1 || this->m_alg == "NULL") {
      cout << "error: cant load" << endl;
      return;
    }
    ifstream file;
    string line;
    file.open(filename);
    if (file.fail()) {
      cout << "error: cant load" << endl;
      return;
    }
    this->m_actions = new vector<Entry *>();
    if (skip) {
      for (long i = 0; i < skip; i++)
        getline(file, line);
    }
    while (getline(file, line)) {
      long start, size, duration;
      stringstream parse(line);
      parse >> start >> size >> duration;
      this->m_actions->push_back(new Entry(start, size, duration));
    }
    file.close();
    this->m_mem = new vector<bool>(this->m_size, 0);
    this->m_time = 0;
  }

  void print() {
    if (this->m_alg == "NULL" || this->m_size == -1 || this->m_mem == NULL) {
      cout << "Please load first" << endl;
      return;
    }
    cout << this->m_alg << " " << this->m_size << endl;
    for (long i = 0; i < this->m_mem->size(); i++) {
      if (this->m_mem->at(i))
        cout << "\033[31m"
             << "+";
      else
        cout << "\033[32m"
             << "_";
    }
    cout << "\033[0m" << endl;
  }

  void run(const string &filename) {
    this->reset();

    ifstream file;
    string line;
    file.open(filename);
    getline(file, line);
    this->setAlg(line);
    getline(file, line);
    this->setSize(atol(line.c_str()));
    file.close();
    this->load(filename, 2);
  }

  void step() {
    for (long i = 0; i < this->m_actions->size(); i++) {
      // For each Entry
      Entry *temp = this->m_actions->at(i);
      if (temp->m_pos == -1) {
        // If Entry has not been placed in memory, disregard
        continue;
      }
      if (!this->m_actions->at(i)->m_done) {
        // If Entry has not yet been deleted
        if (temp->m_start + temp->m_duration == this->m_time) {
          // If Entry needs to be deleted now
          for (long j = 0; j < temp->m_size; j++) {
            this->m_mem->at(temp->m_pos + j) = false;
          }
          temp->m_done = true;
        }
      }
    }

    this->m_time++;

    if (this->m_pos == this->m_actions->size()) {
      return;
    }
    Entry *item = this->m_actions->at(this->m_pos);
    if (item->m_start != this->m_time) {
      return;
    }
    this->m_pos++;

    long pos = -1;
    if (this->m_alg == "first") {
      pos = this->getFirst(item->m_size);
      item->m_pos = pos;
      if (pos == -1) {
        cout << "Command starting at time unit " << item->m_start
             << " cannot be done" << endl;
        return;
      }
      for (long i = 0; i < item->m_size; i++) {
        this->m_mem->at(pos + i) = true;
      }
    } else if (this->m_alg == "next") {
      pos = this->getNext(item->m_size);
      item->m_pos = pos;
      if (pos == -1) {
        cout << "Command starting at time unit " << item->m_start
             << " cannot be done" << endl;
        return;
      }
      for (long i = 0; i < item->m_size; i++) {
        this->m_mem->at(pos + i) = true;
      }
    } else if (this->m_alg == "best") {
      pos = this->getBest(item->m_size);
      item->m_pos = pos;
      if (pos == -1) {
        cout << "Command starting at time unit " << item->m_start
             << " cannot be done" << endl;
        return;
      }
      for (long i = 0; i < item->m_size; i++) {
        this->m_mem->at(pos + i) = true;
      }
    }
    if (pos != -1)
      this->m_last = pos + item->m_size - 1;
  }

  void step(const string &word) {
    if (this->m_time == -1) {
      cout << "Please load first" << endl;
      return;
    }
    if (word == "all") {
      long max = 0;
      const long num = this->m_actions->size();
      for (long i = this->m_pos; i < num; i++) {
        long val = this->m_actions->at(i)->m_start +
                   this->m_actions->at(i)->m_duration;
        if (val > max) {
          max = val + 1;
        }
      }
      for (long i = this->m_pos; i < max; i++) {
        this->step();
      }
      cout << "Completed in " << max << " time units" << endl;
    } else {
      cout << "Not and option" << endl;
    }
  }

  void step(const long &num) {
    for (long i = 0; i < num; i++) {
      this->step();
    }
  }

  long getFirst(const long &size) {
    long place;
    long length;
    for (long i = 0; i < this->m_size; i++) {
      if (!this->m_mem->at(i)) {
        place = i;
        length = 1;
        while (i < this->m_size && !this->m_mem->at(i)) {
          i++;
          length++;
        }
        if (length >= size) {
          return place;
        }
      }
    }
    return long(-1);
  }

  long getNext(const long &size) {
    long place;
    long length;
    for (long i = this->m_last; i < this->m_size + this->m_last; i++) {
      if (!this->m_mem->at(i % this->m_size)) {
        place = i % this->m_size;
        length = 1;
        while (i < this->m_size + this->m_last &&
               !this->m_mem->at(i % this->m_size)) {
          i++;
          length++;
        }
        if (length >= size) {
          return place;
        }
      }
    }
    return long(-1);
  }

  long getBest(const long &size) {
    long place;
    long length;
    map<long, long> positions;
    for (long i = 0; i < this->m_size; i++) {
      if (!this->m_mem->at(i)) {
        place = i;
        length = 1;
        while (i < this->m_size && !this->m_mem->at(i)) {
          i++;
          length++;
        }
        if (length >= size) {
          positions.insert(pair<long, long>(place, length));
        }
      }
    }

    if (positions.empty()) {
      return long(-1);
    }

    auto item = *min_element(positions.begin(), positions.end(),
                             [](decltype(positions)::value_type &l,
                                decltype(positions)::value_type &r) -> bool {
                               return l.second < r.second;
                             });
    auto s = get<0>(item);

    return s;
  }
};

#endif
