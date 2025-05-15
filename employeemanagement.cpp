#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Employee class
class Employee {
private:
    int employeeID;
    string name;
    double salary;
    string department;

public:
    // Constructor
    Employee(int id, string n, double sal, string dept)
        : employeeID(id), name(n), salary(sal), department(dept) {}

    // Getter and Setter methods
    int getID() const { return employeeID; }
    string getName() const { return name; }
    double getSalary() const { return salary; }
    string getDepartment() const { return department; }

    void setSalary(double sal) { salary = sal; }
    void setDepartment(string dept) { department = dept; }

    // Display employee info
    void display() const {
        cout << "ID: " << employeeID << "\nName: " << name
             << "\nSalary: $" << fixed << setprecision(2) << salary
             << "\nDepartment: " << department << endl;
        cout << "Net Salary (after 10% tax): $" << fixed << setprecision(2) << calculateNetSalary() << endl;
        cout << "----------------------------------" << endl;
    }

    // Calculate salary after 10% tax
    double calculateNetSalary() const {
        return salary * 0.90;
    }
};

// Function declarations
void addEmployee(vector<Employee>& employees);
void viewEmployees(const vector<Employee>& employees);
void updateEmployee(vector<Employee>& employees);
void deleteEmployee(vector<Employee>& employees);

// Search helper
int findEmployeeIndex(const vector<Employee>& employees, int id);

// Main function
int main() {
    vector<Employee> employees;
    int choice;

    do {
        cout << "\n========= Employee Management System =========\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addEmployee(employees);
                break;
            case 2:
                viewEmployees(employees);
                break;
            case 3:
                updateEmployee(employees);
                break;
            case 4:
                deleteEmployee(employees);
                break;
            case 5:
                cout << "Exiting... Thank you!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

// Function to add a new employee
void addEmployee(vector<Employee>& employees) {
    int id;
    string name;
    double salary;
    string department;

    cout << "\nEnter Employee ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Salary: ";
    cin >> salary;
    cin.ignore();
    cout << "Enter Department: ";
    getline(cin, department);

    // Check for duplicate ID
    if (findEmployeeIndex(employees, id) != -1) {
        cout << "Error: Employee with this ID already exists.\n";
        return;
    }

    Employee emp(id, name, salary, department);
    employees.push_back(emp);
    cout << "Employee added successfully!\n";
}

// Function to display all employees
void viewEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "\nNo employees to display.\n";
        return;
    }

    cout << "\n--- Employee List ---\n";
    for (const auto& emp : employees) {
        emp.display();
    }
}

// Function to update an employee
void updateEmployee(vector<Employee>& employees) {
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;

    int index = findEmployeeIndex(employees, id);
    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    int option;
    cout << "Update:\n1. Salary\n2. Department\nChoose option: ";
    cin >> option;

    if (option == 1) {
        double newSalary;
        cout << "Enter new salary: ";
        cin >> newSalary;
        employees[index].setSalary(newSalary);
        cout << "Salary updated successfully.\n";
    } else if (option == 2) {
        string newDept;
        cin.ignore();
        cout << "Enter new department: ";
        getline(cin, newDept);
        employees[index].setDepartment(newDept);
        cout << "Department updated successfully.\n";
    } else {
        cout << "Invalid option.\n";
    }
}

// Function to delete an employee
void deleteEmployee(vector<Employee>& employees) {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    int index = findEmployeeIndex(employees, id);
    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    employees.erase(employees.begin() + index);
    cout << "Employee deleted successfully.\n";
}

// Search employee by ID and return index or -1
int findEmployeeIndex(const vector<Employee>& employees, int id) {
    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].getID() == id) {
            return i;
        }
    }
    return -1;
}
