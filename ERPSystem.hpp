#pragma once

#include "AccountsManager.hpp"
#include "HRManager.hpp"
#include "InventoryManager.hpp"
#include "PayrollManager.hpp"
#include "SalesManager.hpp"

#include <string>

namespace erp {

class ERPSystem {
public:
    explicit ERPSystem(std::string companyName);

    const std::string& getCompanyName() const;

    HRManager& hr();
    InventoryManager& inventory();
    PayrollManager& payroll();
    AccountsManager& accounts();
    SalesManager& sales();

    void seedSampleData();
    void displayDashboard() const;

private:
    std::string companyName_;
    HRManager hr_;
    InventoryManager inventory_;
    AccountsManager accounts_;
    PayrollManager payroll_;
    SalesManager sales_;
};

}  // namespace erp
