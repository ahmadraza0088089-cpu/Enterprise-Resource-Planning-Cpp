#include "PayrollRecord.hpp"

#include <iomanip>
#include <sstream>

namespace erp {

PayrollRecord::PayrollRecord(int employeeId, std::string employeeName, std::string period,
                           double grossPay, double tax, double deductions, double netPay)
    : employeeId_(employeeId),
      employeeName_(std::move(employeeName)),
      period_(std::move(period)),
      grossPay_(grossPay),
      tax_(tax),
      deductions_(deductions),
      netPay_(netPay) {}

int PayrollRecord::getEmployeeId() const { return employeeId_; }
const std::string& PayrollRecord::getEmployeeName() const { return employeeName_; }
const std::string& PayrollRecord::getPeriod() const { return period_; }
double PayrollRecord::getGrossPay() const { return grossPay_; }
double PayrollRecord::getTax() const { return tax_; }
double PayrollRecord::getDeductions() const { return deductions_; }
double PayrollRecord::getNetPay() const { return netPay_; }

std::string PayrollRecord::toString() const {
    std::ostringstream stream;
    stream << period_ << " | [" << employeeId_ << "] " << employeeName_
           << " | Gross: " << std::fixed << std::setprecision(2) << grossPay_
           << " | Tax: " << tax_ << " | Deductions: " << deductions_ << " | Net: " << netPay_;
    return stream.str();
}

}  // namespace erp
