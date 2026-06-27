#pragma once

#include <string>

namespace erp {

class Department {
public:
    Department(int id, std::string name, int managerEmployeeId = -1);

    int getId() const;
    const std::string& getName() const;
    int getManagerEmployeeId() const;

    void setManagerEmployeeId(int managerId);

    std::string toString() const;

private:
    int id_;
    std::string name_;
    int managerEmployeeId_;
};

}  // namespace erp
