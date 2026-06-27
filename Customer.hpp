#pragma once

#include <string>

namespace erp {

class Customer {
public:
    Customer(int id, std::string name, std::string email, std::string phone);

    int getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;

    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);

    std::string toString() const;

private:
    int id_;
    std::string name_;
    std::string email_;
    std::string phone_;
};

}  // namespace erp
