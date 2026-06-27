#pragma once

#include "Account.hpp"
#include "PayrollRecord.hpp"

#include <memory>
#include <string>
#include <vector>

namespace erp {

struct JournalEntry {
    int id;
    std::string date;
    std::string description;
    std::string debitAccountCode;
    std::string creditAccountCode;
    double amount;
};

class AccountsManager {
public:
    Account& addAccount(std::string code, std::string name, AccountType type, double balance = 0.0);

    Account* findAccount(const std::string& code);
    const Account* findAccount(const std::string& code) const;

    bool postJournalEntry(const std::string& date, const std::string& description,
                          const std::string& debitCode, const std::string& creditCode, double amount);

    const std::vector<std::unique_ptr<Account>>& getAccounts() const;
    const std::vector<JournalEntry>& getJournal() const;

    void displayChartOfAccounts() const;
    void displayJournal() const;
    void displayTrialBalance() const;
    void displayIncomeStatement() const;

    void initializeDefaultAccounts();

private:
    std::vector<std::unique_ptr<Account>> accounts_;
    std::vector<JournalEntry> journal_;
    int nextJournalId_ = 1;
};

}  // namespace erp
