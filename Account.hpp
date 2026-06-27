#pragma once

#include <string>

namespace erp {

enum class AccountType { Asset, Liability, Equity, Revenue, Expense };

std::string accountTypeToString(AccountType type);

class Account {
public:
    Account(std::string code, std::string name, AccountType type, double balance = 0.0);

    const std::string& getCode() const;
    const std::string& getName() const;
    AccountType getType() const;
    double getBalance() const;

    void debit(double amount);
    void credit(double amount);

    std::string toString() const;

private:
    std::string code_;
    std::string name_;
    AccountType type_;
    double balance_;
};

}  // namespace erp
