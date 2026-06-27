#include "Account.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace erp {

std::string accountTypeToString(AccountType type) {
    switch (type) {
        case AccountType::Asset:
            return "Asset";
        case AccountType::Liability:
            return "Liability";
        case AccountType::Equity:
            return "Equity";
        case AccountType::Revenue:
            return "Revenue";
        case AccountType::Expense:
            return "Expense";
    }
    return "Unknown";
}

Account::Account(std::string code, std::string name, AccountType type, double balance)
    : code_(std::move(code)), name_(std::move(name)), type_(type), balance_(balance) {}

const std::string& Account::getCode() const { return code_; }
const std::string& Account::getName() const { return name_; }
AccountType Account::getType() const { return type_; }
double Account::getBalance() const { return balance_; }

void Account::debit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Debit amount must be non-negative");
    }
    if (type_ == AccountType::Asset || type_ == AccountType::Expense) {
        balance_ += amount;
    } else {
        balance_ -= amount;
    }
}

void Account::credit(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Credit amount must be non-negative");
    }
    if (type_ == AccountType::Asset || type_ == AccountType::Expense) {
        balance_ -= amount;
    } else {
        balance_ += amount;
    }
}

std::string Account::toString() const {
    std::ostringstream stream;
    stream << code_ << " | " << name_ << " (" << accountTypeToString(type_) << ") | Balance: "
           << std::fixed << std::setprecision(2) << balance_;
    return stream.str();
}

}  // namespace erp
