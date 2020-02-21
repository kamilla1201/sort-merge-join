#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Employee.h"
#include "Department.h"

using namespace std;

const int M = 22;

template <class T>
void save_run(int run, const string& prefix, const vector<T>& vec) {
  ofstream file;
  string filename = prefix + to_string(run);
  cout << "Creating file " << filename << endl;
  file.open(filename);
  for (T e : vec) {
    file << e.toTuple() << endl;
  }
  file.close();
}

template <class T>
void sort(const string& prefix) {
  cout << "Sorting " << prefix << " data" << endl;
  cout << "Reading " << prefix << ".csv file" << endl;
 	ifstream file(prefix + ".csv");
  if (!file.good()) {
    cout << "File " << prefix << ".csv doesn't exist. Exiting." << endl;
    exit(1);
  }
	string line = "";
  vector<T> memory;
  int run = 0;

  while (getline(file, line)) {
    // make sure we don't use more than M blocks
    if (memory.size() == M) {
      sort(memory.begin(), memory.end());
      save_run(run, prefix, memory);
      run += 1;
      memory.clear();
    }
    vector<string> vec;
    boost::algorithm::split(vec, line, boost::is_any_of(","));
    memory.push_back(T(vec));
  }
  if (memory.size()) {
    sort(memory.begin(), memory.end());
    save_run(run, prefix, memory);
  }
}

template<class T>
T get_insance_from_tuple(const string& line) {
  vector<string> vec;
  boost::algorithm::split(vec, line, boost::is_any_of(","));
  return T(vec);
}

void merge() {
  cout << "Merging tables" << endl;
  vector<ifstream> emp_runs;
  vector<ifstream> dept_runs;
  emp_runs.push_back(ifstream("Emp0"));
  emp_runs.push_back(ifstream("Emp1"));
  dept_runs.push_back(ifstream("Dept0"));

  vector<Employee> employees;
  vector<Department> departments;
  ofstream output;
  string line = "";
  output.open("Result.csv");

  // from each run upload the smallest value
  for (int i = 0; i < emp_runs.size(); ++i) {
    if (getline(emp_runs[i], line)) {
      employees.push_back(get_insance_from_tuple<Employee>(line));
    }
  }
  for (int i = 0; i < dept_runs.size(); ++i) {
    if (getline(dept_runs[i], line)) {
      departments.push_back(get_insance_from_tuple<Department>(line));
    }
  }

  while(employees.size() > 0 && departments.size() > 0) {
    // find the minimum id in the first table
    int minEmpInd = min_element(employees.begin(), employees.end()) - employees.begin();
    int minId = employees[minEmpInd].getId();

    int deptInd = 0;
    // find all id in the second table that match the minId
    while (deptInd < departments.size()) {
      if (minId == departments[deptInd].getManagerId()) {
        output << employees[minEmpInd].toTuple() << "," << departments[deptInd].toMergedTuple() << endl;
      }
      if (minId >= departments[deptInd].getManagerId()) {
        departments.erase(departments.begin() + deptInd);
        if (getline(dept_runs[deptInd], line)) {
          departments.insert(departments.begin() + deptInd, get_insance_from_tuple<Department>(line));
        }
      }
      if (minId < departments[deptInd].getManagerId()) {
        deptInd++;
      }
    }
    // uploading new value instead of minId
    employees.erase(employees.begin() + minEmpInd);
    if (getline(emp_runs[minEmpInd], line)) {
      employees.insert(employees.begin() + minEmpInd, get_insance_from_tuple<Employee>(line));
    }
  }
  emp_runs[0].close();
  emp_runs[1].close();
  dept_runs[0].close();
  output.close();
  cout << "Results are saved to Result.csv" << endl;
}

int main(int argc, char** argv) {
  sort<Employee>("Emp");
  sort<Department>("Dept");
  merge();
  return 0;
}
