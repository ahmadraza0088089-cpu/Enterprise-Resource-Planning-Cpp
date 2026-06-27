#include "HRManager.hpp"

#include <algorithm>
#include <iostream>

namespace erp {

Employee& HRManager::addEmployee(std::string name, std::string department, std::string position,
                                 double baseSalary, std::string hireDate) {
    const int id = nextEmployeeId_++;
    employees_.push_back(
        std::make_unique<Employee>(id, std::move(name), std::move(department), std::move(position),
                                   baseSalary, std::move(hireDate)));
    return *employees_.back();
}

Department& HRManager::addDepartment(std::string name, int managerEmployeeId) {
    const int id = nextDepartmentId_++;
    departments_.push_back(std::make_unique<Department>(id, std::move(name), managerEmployeeId));
    return *departments_.back();
}

Employee* HRManager::findEmployee(int id) {
    for (auto& employee : employees_) {
        if (employee->getId() == id) {
            return employee.get();
        }
    }
    return nullptr;
}

const Employee* HRManager::findEmployee(int id) const {
    for (const auto& employee : employees_) {
        if (employee->getId() == id) {
            return employee.get();
        }
    }
    return nullptr;
}

Department* HRManager::findDepartment(int id) {
    for (auto& department : departments_) {
        if (department->getId() == id) {
            return department.get();
        }
    }
    return nullptr;
}

const Department* HRManager::findDepartment(int id) const {
    for (const auto& department : departments_) {
        if (department->getId() == id) {
            return department.get();
        }
    }
    return nullptr;
}

Department* HRManager::findDepartmentByName(const std::string& name) {
    for (auto& department : departments_) {
        if (department->getName() == name) {
            return department.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Employee>>& HRManager::getEmployees() const { return employees_; }
const std::vector<std::unique_ptr<Department>>& HRManager::getDepartments() const { return departments_; }

void HRManager::displayEmployees() const {
    std::cout << "\n  Employees (" << employees_.size() << ")\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    if (employees_.empty()) {
        std::cout << "  No employees on record.\n";
        return;
    }
    for (const auto& employee : employees_) {
        std::cout << "  " << employee->toString() << "\n";
    }
}

void HRManager::displayDepartments() const {
    std::cout << "\n  Departments (" << departments_.size() << ")\n";
    std::cout << "  " << std::string(50, '-') << "\n";
    if (departments_.empty()) {
        std::cout << "  No departments on record.\n";
        return;
    }
    for (const auto& department : departments_) {
        std::cout << "  " << department->toString() << "\n";
    }
}

void HRManager::displayEmployeesByDepartment(const std::string& department) const {
    std::cout << "\n  Employees in " << department << "\n";
    std::cout << "  " << std::string(50, '-') << "\n";
    bool found = false;
    for (const auto& employee : employees_) {
        if (employee->getDepartment() == department && employee->isActive()) {
            std::cout << "  " << employee->toString() << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No active employees in this department.\n";
    }
}

bool HRManager::updateEmployeeDepartment(int employeeId, const std::string& department) {
    Employee* employee = findEmployee(employeeId);
    if (employee == nullptr) {
        std::cout << "  Error: Employee not found.\n";
        return false;
    }
    employee->setDepartment(department);
    std::cout << "  Department updated successfully.\n";
    return true;
}

bool HRManager::deactivateEmployee(int employeeId) {
    Employee* employee = findEmployee(employeeId);
    if (employee == nullptr) {
        std::cout << "  Error: Employee not found.\n";
        return false;
    }
    employee->setActive(false);
    std::cout << "  Employee deactivated.\n";
    return true;
}

}  // namespace erp
