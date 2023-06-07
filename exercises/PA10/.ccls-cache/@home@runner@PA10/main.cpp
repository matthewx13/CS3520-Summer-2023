#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employee {
private:
    string name;
    string email;
    string designation;
    int groupId;
    double salary; // Added salary member variable

public:
    Employee() {}

    Employee(string name, string email, string designation, int groupId, double salary)
        : name(name), email(email), designation(designation), groupId(groupId), salary(salary) {}

    friend istream& operator>>(istream& in, Employee& employee);

    friend ostream& operator<<(ostream& out, const Employee& employee);

    void setGroupId(int newGroupId) {
        groupId = newGroupId;
    }

    double getSalary() const {
        return salary;
    }
};

istream& operator>>(istream& in, Employee& employee) {
    in >> employee.name >> employee.email >> employee.designation >> employee.groupId >> employee.salary;
    return in;
}

ostream& operator<<(ostream& out, const Employee& employee) {
    out << "Name: " << employee.name << ", Email: " << employee.email
        << ", Designation: " << employee.designation << ", Group ID: " << employee.groupId
        << ", Salary: $" << employee.salary;
    return out;
}

class Group {
private:
    string name;
    int groupNumber;
    string focusArea;
    vector<Employee> employees;

public:
    Group() {}

    Group(string name, int groupNumber, string focusArea, const vector<Employee>& employees)
        : name(name), groupNumber(groupNumber), focusArea(focusArea), employees(employees) {}

    friend istream& operator>>(istream& in, Group& group);

    friend ostream& operator<<(ostream& out, const Group& group);

    Group operator-(int num) const;

    Group operator+(const Group& other) const;

    Group operator/(int dummyValue) const;
};

istream& operator>>(istream& in, Group& group) {
    in >> group.name >> group.groupNumber >> group.focusArea;
    return in;
}

ostream& operator<<(ostream& out, const Group& group) {
    out << "Group Name: " << group.name << ", Group Number: " << group.groupNumber
        << ", Focus Area: " << group.focusArea << endl;
    out << "Employees:" << endl;
    for (const auto& employee : group.employees) {
        out << " - " << employee << endl;
    }
    return out;
}

Group Group::operator-(int num) const {
    Group copy = *this;
    int numToRemove = min(num, static_cast<int>(employees.size()));
    copy.employees.erase(copy.employees.end() - numToRemove, copy.employees.end());
    return copy;
}

Group Group::operator+(const Group& other) const {
    Group mergedGroup = *this;
    mergedGroup.employees.insert(mergedGroup.employees.end(), other.employees.begin(), other.employees.end());
    return mergedGroup;
}

Group Group::operator/(int dummyValue) const {
    Group newGroup = *this;
    int newGroupNumber = groupNumber + 100;
    newGroup.groupNumber = newGroupNumber;
    newGroup.name += "Split";
    vector<Employee> newEmployees;

    for (int i = 0; i < employees.size(); i++) {
        if (i % 2 == 1) { // Select employees with odd indices
            Employee employee = employees[i];
            employee.setGroupId(newGroupNumber);
            newEmployees.push_back(employee);
        }
    }

    newGroup.employees = newEmployees;
    return newGroup;
}

int main() {
    vector<Employee> employees1 = {
        Employee("Matthew", "matthew@apple.com", "Engineer", 1, 90000.0),
        Employee("Rachel", "rachel@apple.com", "Project Manager", 1, 75000.0)
    };
    Group group1("Group A", 1, "Responsibility A", employees1);

    vector<Employee> employees2 = {
        Employee("Michael", "michael@apple.com", "Designer", 2, 65000.0),
        Employee("Chia", "chia@apple.com", "Engineer", 2, 85000.0)
    };
    Group group2("Group B", 2, "Responsibility B", employees2);

    cout << "The original groups:" << endl;
    cout << endl;
    cout << "Group #1: " << group1 << endl;
    cout << "Group #2: " << group2 << endl;
    cout << endl;

    int x;
    cout << "Please enter the number of employees to remove from Group 1: ";
    cin >> x;

    Group updatedGroup1 = group1 - x;
    cout << "Updated Group 1 (-" << x << " employees): " << updatedGroup1 << endl;
    cout << endl;

    Group mergedGroup = group1 + group2;
    cout << "Merging Groups (Group 1 + Group 2): " << mergedGroup << endl;
    cout << endl;

    cout << "Splitting Group 1: " << (group1 / 2) << endl;
    cout << endl;

    cout << "Output group 1 after split: " << group1 << endl;

    return 0;
}


