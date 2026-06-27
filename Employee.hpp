#pragma once

#include <string>

namespace erp {

class Employee {
public:
    Employee(int id, std::string name, std::string department, std::string position,
             double baseSalary, std::string hireDate, bool active = true);

    int getId() const;
    const std::string& getName() const;
    const std::string& getDepartment() const;
    const std::string& getPosition() const;
    double getBaseSalary() const;
    const std::string& getHireDate() const;
    bool isActive() const;

    void setDepartment(const std::string& department);
    void setPosition(const std::string& position);
    void setBaseSalary(double salary);
    void setActive(bool active);

    std::string toString() const;

private:
    int id_;
    std::string name_;
    std::string department_;
    std::string position_;
    double baseSalary_;
    std::string hireDate_;
    bool active_;
};

}  // namespace erp
