#include "ERPSystem.hpp"

#include <iomanip>
#include <iostream>

namespace erp {

ERPSystem::ERPSystem(std::string companyName)
    : companyName_(std::move(companyName)),
      payroll_(hr_),
      sales_(inventory_, accounts_) {
    accounts_.initializeDefaultAccounts();
}

const std::string& ERPSystem::getCompanyName() const { return companyName_; }

HRManager& ERPSystem::hr() { return hr_; }
InventoryManager& ERPSystem::inventory() { return inventory_; }
PayrollManager& ERPSystem::payroll() { return payroll_; }
AccountsManager& ERPSystem::accounts() { return accounts_; }
SalesManager& ERPSystem::sales() { return sales_; }

void ERPSystem::seedSampleData() {
    std::cout << "\n  Loading sample data...\n";

    hr_.addDepartment("Human Resources", -1);
    hr_.addDepartment("Sales", -1);
    hr_.addDepartment("Warehouse", -1);
    hr_.addDepartment("Finance", -1);

    Employee& alice = hr_.addEmployee("Alice Khan", "Human Resources", "HR Manager", 5500.0, "2022-03-15");
    Employee& bob = hr_.addEmployee("Bob Ahmed", "Sales", "Sales Executive", 4200.0, "2023-01-10");
    Employee& charlie = hr_.addEmployee("Charlie Ali", "Warehouse", "Inventory Clerk", 3800.0, "2023-06-01");
    Employee& diana = hr_.addEmployee("Diana Noor", "Finance", "Accountant", 4800.0, "2021-11-20");

    if (Department* hrDept = hr_.findDepartmentByName("Human Resources")) {
        hrDept->setManagerEmployeeId(alice.getId());
    }
    if (Department* salesDept = hr_.findDepartmentByName("Sales")) {
        salesDept->setManagerEmployeeId(bob.getId());
    }

    inventory_.addProduct("SKU-001", "Laptop Pro 15", "Electronics", 25, 800.0, 1200.0, 5);
    inventory_.addProduct("SKU-002", "Office Chair", "Furniture", 40, 120.0, 199.0, 10);
    inventory_.addProduct("SKU-003", "Wireless Mouse", "Electronics", 100, 15.0, 29.99, 20);
    inventory_.addProduct("SKU-004", "A4 Paper Ream", "Stationery", 8, 3.5, 6.99, 15);

    accounts_.postJournalEntry("2026-06-01", "Initial inventory purchase", "1200", "1000", 15000.0);

    sales_.addCustomer("Tech Solutions Ltd", "contact@techsolutions.com", "+92-300-1112233");
    sales_.addCustomer("Green Office Co", "orders@greenoffice.com", "+92-321-4455667");

    SalesOrder& order = sales_.createOrder(2001, "2026-06-10");
    sales_.addItemToOrder(order.getId(), "SKU-001", 2);
    sales_.addItemToOrder(order.getId(), "SKU-003", 5);
    sales_.completeOrder(order.getId());

    payroll_.processAll("2026-06", 0.10, 50.0);
    accounts_.postJournalEntry("2026-06-30", "June payroll", "5100", "1000",
                                 payroll_.totalPayrollForPeriod("2026-06"));

    std::cout << "  Sample data loaded successfully.\n";
}

void ERPSystem::displayDashboard() const {
    int activeEmployees = 0;
    for (const auto& employee : hr_.getEmployees()) {
        if (employee->isActive()) {
            ++activeEmployees;
        }
    }

    std::cout << "\n  Company Dashboard: " << companyName_ << "\n";
    std::cout << "  " << std::string(50, '=') << "\n";
    std::cout << "  Active Employees:    " << activeEmployees << "\n";
    std::cout << "  Products in Stock:   " << inventory_.getProducts().size() << "\n";
    std::cout << "  Inventory Value:     " << std::fixed << std::setprecision(2)
              << inventory_.totalInventoryValue() << "\n";
    std::cout << "  Customers:           " << sales_.getCustomers().size() << "\n";
    std::cout << "  Total Sales Revenue: " << sales_.totalRevenue() << "\n";
    std::cout << "  Payroll Records:     " << payroll_.getHistory().size() << "\n";
}

}  // namespace erp
