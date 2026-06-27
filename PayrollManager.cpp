#include "PayrollManager.hpp"

#include <iostream>

namespace erp {

PayrollManager::PayrollManager(const HRManager& hr) : hr_(hr) {}

PayrollRecord PayrollManager::processEmployee(int employeeId, const std::string& period, double taxRate,
                                              double otherDeductions) {
    const Employee* employee = hr_.findEmployee(employeeId);
    if (employee == nullptr || !employee->isActive()) {
        std::cout << "  Error: Active employee not found.\n";
        return PayrollRecord(employeeId, "Unknown", period, 0, 0, 0, 0);
    }

    const double gross = employee->getBaseSalary();
    const double tax = gross * taxRate;
    const double net = gross - tax - otherDeductions;

    PayrollRecord record(employeeId, employee->getName(), period, gross, tax, otherDeductions, net);
    history_.push_back(record);

    std::cout << "  Payroll processed: " << record.toString() << "\n";
    return record;
}

std::vector<PayrollRecord> PayrollManager::processAll(const std::string& period, double taxRate,
                                                      double otherDeductions) {
    std::vector<PayrollRecord> batch;
    std::cout << "\n  Processing payroll for " << period << "...\n";

    for (const auto& employee : hr_.getEmployees()) {
        if (!employee->isActive()) {
            continue;
        }
        batch.push_back(processEmployee(employee->getId(), period, taxRate, otherDeductions));
    }

    if (batch.empty()) {
        std::cout << "  No active employees to process.\n";
    }

    return batch;
}

const std::vector<PayrollRecord>& PayrollManager::getHistory() const { return history_; }

void PayrollManager::displayHistory() const {
    std::cout << "\n  Payroll History\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    if (history_.empty()) {
        std::cout << "  No payroll records.\n";
        return;
    }
    for (const auto& record : history_) {
        std::cout << "  " << record.toString() << "\n";
    }
}

double PayrollManager::totalPayrollForPeriod(const std::string& period) const {
    double total = 0.0;
    for (const auto& record : history_) {
        if (record.getPeriod() == period) {
            total += record.getNetPay();
        }
    }
    return total;
}

}  // namespace erp
