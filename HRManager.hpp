#pragma once

#include "Department.hpp"
#include "Employee.hpp"

#include <memory>
#include <string>
#include <vector>

namespace erp {

class HRManager {
public:
    Employee& addEmployee(std::string name, std::string department, std::string position,
                          double baseSalary, std::string hireDate);
    Department& addDepartment(std::string name, int managerEmployeeId = -1);

    Employee* findEmployee(int id);
    const Employee* findEmployee(int id) const;
    Department* findDepartment(int id);
    const Department* findDepartment(int id) const;
    Department* findDepartmentByName(const std::string& name);

    const std::vector<std::unique_ptr<Employee>>& getEmployees() const;
    const std::vector<std::unique_ptr<Department>>& getDepartments() const;

    void displayEmployees() const;
    void displayDepartments() const;
    void displayEmployeesByDepartment(const std::string& department) const;

    bool updateEmployeeDepartment(int employeeId, const std::string& department);
    bool deactivateEmployee(int employeeId);

private:
    std::vector<std::unique_ptr<Employee>> employees_;
    std::vector<std::unique_ptr<Department>> departments_;
    int nextEmployeeId_ = 1001;
    int nextDepartmentId_ = 1;
};

}  // namespace erp
