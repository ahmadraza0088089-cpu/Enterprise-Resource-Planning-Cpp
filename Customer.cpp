#include "Customer.hpp"

#include <sstream>

namespace erp {

Customer::Customer(int id, std::string name, std::string email, std::string phone)
    : id_(id), name_(std::move(name)), email_(std::move(email)), phone_(std::move(phone)) {}

int Customer::getId() const { return id_; }
const std::string& Customer::getName() const { return name_; }
const std::string& Customer::getEmail() const { return email_; }
const std::string& Customer::getPhone() const { return phone_; }

void Customer::setEmail(const std::string& email) { email_ = email; }
void Customer::setPhone(const std::string& phone) { phone_ = phone; }

std::string Customer::toString() const {
    std::ostringstream stream;
    stream << "[" << id_ << "] " << name_ << " | " << email_ << " | " << phone_;
    return stream.str();
}

}  // namespace erp
