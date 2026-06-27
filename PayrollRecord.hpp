#pragma once

#include <string>

namespace erp {

class PayrollRecord {
public:
    PayrollRecord(int employeeId, std::string employeeName, std::string period,
                  double grossPay, double tax, double deductions, double netPay);

    int getEmployeeId() const;
    const std::string& getEmployeeName() const;
    const std::string& getPeriod() const;
    double getGrossPay() const;
    double getTax() const;
    double getDeductions() const;
    double getNetPay() const;

    std::string toString() const;

private:
    int employeeId_;
    std::string employeeName_;
    std::string period_;
    double grossPay_;
    double tax_;
    double deductions_;
    double netPay_;
};

}  // namespace erp
