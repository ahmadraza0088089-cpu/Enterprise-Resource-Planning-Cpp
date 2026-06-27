#include "Department.hpp"

#include <sstream>

namespace erp {

Department::Department(int id, std::string name, int managerEmployeeId)
    : id_(id), name_(std::move(name)), managerEmployeeId_(managerEmployeeId) {}

int Department::getId() const { return id_; }
const std::string& Department::getName() const { return name_; }
int Department::getManagerEmployeeId() const { return managerEmployeeId_; }

void Department::setManagerEmployeeId(int managerId) { managerEmployeeId_ = managerId; }

std::string Department::toString() const {
    std::ostringstream stream;
    stream << "[" << id_ << "] " << name_;
    if (managerEmployeeId_ >= 0) {
        stream << " (Manager ID: " << managerEmployeeId_ << ")";
    }
    return stream.str();
}

}  // namespace erp
