#pragma once

#include "HRManager.hpp"
#include "PayrollRecord.hpp"

#include <memory>
#include <string>
#include <vector>

namespace erp {

class PayrollManager {
public:
    explicit PayrollManager(const HRManager& hr);

    PayrollRecord processEmployee(int employeeId, const std::string& period,
                                  double taxRate = 0.10, double otherDeductions = 0.0);
    std::vector<PayrollRecord> processAll(const std::string& period,
                                          double taxRate = 0.10, double otherDeductions = 0.0);

    const std::vector<PayrollRecord>& getHistory() const;

    void displayHistory() const;
    double totalPayrollForPeriod(const std::string& period) const;

private:
    const HRManager& hr_;
    std::vector<PayrollRecord> history_;
};

}  // namespace erp
