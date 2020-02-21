#ifndef _INCL_EMPLOYEE
#define _INCL_EMPLOYEE
#include<iostream>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

class Employee {
  int eid;
  string ename;
  int age;
  double salary;

public:
  Employee(int eid, string ename, int age, double salary)
    : eid(eid),
      ename(ename),
      age(age),
      salary(salary)
  {}

  Employee(const vector<string>& vec) {
    eid = stoi(vec[0]);
    ename = vec[1];
    age = stoi(vec[2]);
    salary = stod(vec[3]);
  }

  int getId() { return eid; }
  string getName() { return ename; }
  int getAge() { return age; }
  double getSalary() { return salary; }

  bool operator < (const Employee & other) const {
    return eid < other.eid;
  }

  void print() {
    cout << "eid: " << eid << ", ename: " << ename <<
      ", age: " << age << ", salary: " << salary << endl;
  }

  string toTuple() {
    ostringstream s;
    s << eid << "," << ename << "," << age << "," << salary;
    return s.str();
  }
};

#endif
