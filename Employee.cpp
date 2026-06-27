#include "Employee.hpp"

#include <iomanip>
#include <sstream>

namespace erp {

Employee::Employee(int id, std::string name, std::string department, std::string position,
                   double baseSalary, std::string hireDate, bool active)
    : id_(id),
      name_(std::move(name)),
      department_(std::move(department)),
      position_(std::move(position)),
      baseSalary_(baseSalary),
      hireDate_(std::move(hireDate)),
      active_(active) {}

int Employee::getId() const { return id_; }
const std::string& Employee::getName() const { return name_; }
const std::string& Employee::getDepartment() const { return department_; }
const std::string& Employee::getPosition() const { return position_; }
double Employee::getBaseSalary() const { return baseSalary_; }
const std::string& Employee::getHireDate() const { return hireDate_; }
bool Employee::isActive() const { return active_; }

void Employee::setDepartment(const std::string& department) { department_ = department; }
void Employee::setPosition(const std::string& position) { position_ = position; }
void Employee::setBaseSalary(double salary) { baseSalary_ = salary; }
void Employee::setActive(bool active) { active_ = active; }

std::string Employee::toString() const {
    std::ostringstream stream;
    stream << "[" << id_ << "] " << name_ << " | " << position_ << " @ " << department_
           << " | Salary: " << std::fixed << std::setprecision(2) << baseSalary_
           << " | Hired: " << hireDate_ << " | " << (active_ ? "Active" : "Inactive");
    return stream.str();
}

}  // namespace erp
