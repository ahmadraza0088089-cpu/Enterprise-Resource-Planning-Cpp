#include "AccountsManager.hpp"

#include <iomanip>
#include <iostream>

namespace erp {

Account& AccountsManager::addAccount(std::string code, std::string name, AccountType type, double balance) {
    accounts_.push_back(std::make_unique<Account>(std::move(code), std::move(name), type, balance));
    return *accounts_.back();
}

Account* AccountsManager::findAccount(const std::string& code) {
    for (auto& account : accounts_) {
        if (account->getCode() == code) {
            return account.get();
        }
    }
    return nullptr;
}

const Account* AccountsManager::findAccount(const std::string& code) const {
    for (const auto& account : accounts_) {
        if (account->getCode() == code) {
            return account.get();
        }
    }
    return nullptr;
}

bool AccountsManager::postJournalEntry(const std::string& date, const std::string& description,
                                       const std::string& debitCode, const std::string& creditCode,
                                       double amount) {
    if (amount <= 0) {
        std::cout << "  Error: Amount must be positive.\n";
        return false;
    }

    Account* debitAccount = findAccount(debitCode);
    Account* creditAccount = findAccount(creditCode);
    if (debitAccount == nullptr || creditAccount == nullptr) {
        std::cout << "  Error: Invalid account code.\n";
        return false;
    }

    debitAccount->debit(amount);
    creditAccount->credit(amount);

    journal_.push_back(JournalEntry{nextJournalId_++, date, description, debitCode, creditCode, amount});
    std::cout << "  Journal entry posted: " << description << " (" << amount << ")\n";
    return true;
}

const std::vector<std::unique_ptr<Account>>& AccountsManager::getAccounts() const { return accounts_; }
const std::vector<JournalEntry>& AccountsManager::getJournal() const { return journal_; }

void AccountsManager::displayChartOfAccounts() const {
    std::cout << "\n  Chart of Accounts\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    for (const auto& account : accounts_) {
        std::cout << "  " << account->toString() << "\n";
    }
}

void AccountsManager::displayJournal() const {
    std::cout << "\n  General Journal\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    if (journal_.empty()) {
        std::cout << "  No journal entries.\n";
        return;
    }
    for (const auto& entry : journal_) {
        std::cout << "  #" << entry.id << " " << entry.date << " | " << entry.description << " | Dr "
                  << entry.debitAccountCode << " / Cr " << entry.creditAccountCode << " | "
                  << std::fixed << std::setprecision(2) << entry.amount << "\n";
    }
}

void AccountsManager::displayTrialBalance() const {
    std::cout << "\n  Trial Balance\n";
    std::cout << "  " << std::string(50, '-') << "\n";
    double totalDebits = 0.0;
    double totalCredits = 0.0;

    for (const auto& account : accounts_) {
        const double balance = account->getBalance();
        const AccountType type = account->getType();

        if (type == AccountType::Asset || type == AccountType::Expense) {
            if (balance >= 0) {
                totalDebits += balance;
            } else {
                totalCredits += -balance;
            }
        } else {
            if (balance >= 0) {
                totalCredits += balance;
            } else {
                totalDebits += -balance;
            }
        }

        std::cout << "  " << account->toString() << "\n";
    }

    std::cout << "  " << std::string(50, '-') << "\n";
    std::cout << "  Total Debits:  " << std::fixed << std::setprecision(2) << totalDebits << "\n";
    std::cout << "  Total Credits: " << totalCredits << "\n";
}

void AccountsManager::displayIncomeStatement() const {
    double revenue = 0.0;
    double expenses = 0.0;

    for (const auto& account : accounts_) {
        if (account->getType() == AccountType::Revenue) {
            revenue += account->getBalance();
        } else if (account->getType() == AccountType::Expense) {
            expenses += account->getBalance();
        }
    }

    std::cout << "\n  Income Statement (Summary)\n";
    std::cout << "  " << std::string(40, '-') << "\n";
    std::cout << "  Revenue:   " << std::fixed << std::setprecision(2) << revenue << "\n";
    std::cout << "  Expenses:  " << expenses << "\n";
    std::cout << "  Net Income:" << (revenue - expenses) << "\n";
}

void AccountsManager::initializeDefaultAccounts() {
    if (!accounts_.empty()) {
        return;
    }

    addAccount("1000", "Cash", AccountType::Asset, 50000.0);
    addAccount("1100", "Accounts Receivable", AccountType::Asset, 0.0);
    addAccount("1200", "Inventory", AccountType::Asset, 0.0);
    addAccount("2000", "Accounts Payable", AccountType::Liability, 0.0);
    addAccount("3000", "Owner's Equity", AccountType::Equity, 50000.0);
    addAccount("4000", "Sales Revenue", AccountType::Revenue, 0.0);
    addAccount("5000", "Cost of Goods Sold", AccountType::Expense, 0.0);
    addAccount("5100", "Salary Expense", AccountType::Expense, 0.0);
    addAccount("5200", "Rent Expense", AccountType::Expense, 0.0);
}

}  // namespace erp
