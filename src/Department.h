#ifndef _INCL_DEPARTMENT
#define _INCL_DEPARTMENT
#include<iostream>
#include <vector>
#include<sstream>

using namespace std;

class Department {
  int did;
  string dname;
  double budget;
  int managerId;

public:
  Department(int did, string dname, double budget, int managerId)
    : did(did),
      dname(dname),
      budget(budget),
      managerId(managerId)
  {}

  Department(const vector<string>& vec) {
    did = stoi(vec[0]);
    dname = vec[1];
    budget = stod(vec[2]);
    managerId = stoi(vec[3]);
  }


  int getId() { return did; }
  string getName() { return dname; }
  double getBudget() { return budget; }
  int getManagerId() { return managerId; }

  bool operator < (const Department & other) const {
    return managerId < other.managerId;
  }

  void print() {
    cout << "eid: " << did << ", ename: " << dname <<
      ", budget: " << budget << ", managerId: " << managerId << endl;
  }

  string toTuple() {
    ostringstream s;
    s << did << "," << dname << "," << budget << "," << managerId;
    return s.str();
  }

  string toMergedTuple() {
    ostringstream s;
    s << did << "," << dname << "," << budget;
    return s.str();
  }
};

#endif
