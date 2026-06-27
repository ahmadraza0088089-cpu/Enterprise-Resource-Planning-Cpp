#include "ERPSystem.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace {

constexpr const char* kBanner = R"(
  +======================================================+
  |         ENTERPRISE RESOURCE PLANNING SYSTEM          |
  |              Console Application - C++               |
  +======================================================+
)";

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int value = 0;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "  Invalid input. Please enter a number.\n";
        clearInput();
    }
}

double readDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        double value = 0.0;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "  Invalid input. Please enter a number.\n";
        clearInput();
    }
}

void pause() { readLine("\nPress Enter to continue..."); }

void printMainMenu() {
    std::cout << "\n+-------------------------------------+\n"
              << "|           MAIN MENU                 |\n"
              << "+-------------------------------------+\n"
              << "|  1.  HR Module                      |\n"
              << "|  2.  Inventory Module               |\n"
              << "|  3.  Payroll Module                 |\n"
              << "|  4.  Accounts Module                |\n"
              << "|  5.  Sales Module                   |\n"
              << "|  6.  Company Dashboard              |\n"
              << "|  7.  Load Sample Data               |\n"
              << "|  0.  Exit                           |\n"
              << "+-------------------------------------+\n";
}

void printHRMenu() {
    std::cout << "\n  [HR Module]\n"
              << "  1. Add Employee\n"
              << "  2. Add Department\n"
              << "  3. View All Employees\n"
              << "  4. View Departments\n"
              << "  5. View Employees by Department\n"
              << "  6. Transfer Employee\n"
              << "  7. Deactivate Employee\n"
              << "  0. Back\n";
}

void printInventoryMenu() {
    std::cout << "\n  [Inventory Module]\n"
              << "  1. Add Product\n"
              << "  2. View Catalogue\n"
              << "  3. Stock In\n"
              << "  4. Stock Out\n"
              << "  5. Search Products\n"
              << "  6. Low Stock Report\n"
              << "  0. Back\n";
}

void printPayrollMenu() {
    std::cout << "\n  [Payroll Module]\n"
              << "  1. Process Single Employee\n"
              << "  2. Process All Employees\n"
              << "  3. View Payroll History\n"
              << "  4. Post Payroll to Accounts\n"
              << "  0. Back\n";
}

void printAccountsMenu() {
    std::cout << "\n  [Accounts Module]\n"
              << "  1. View Chart of Accounts\n"
              << "  2. Post Journal Entry\n"
              << "  3. View Journal\n"
              << "  4. Trial Balance\n"
              << "  5. Income Statement\n"
              << "  0. Back\n";
}

void printSalesMenu() {
    std::cout << "\n  [Sales Module]\n"
              << "  1. Add Customer\n"
              << "  2. View Customers\n"
              << "  3. Create Sales Order\n"
              << "  4. Add Item to Order\n"
              << "  5. Complete Order\n"
              << "  6. View All Orders\n"
              << "  0. Back\n";
}

void handleHR(erp::ERPSystem& system) {
    while (true) {
        printHRMenu();
        const int choice = readInt("  Choice: ");
        if (choice == 0) {
            return;
        }

        switch (choice) {
            case 1: {
                const std::string name = readLine("  Name: ");
                const std::string department = readLine("  Department: ");
                const std::string position = readLine("  Position: ");
                const double salary = readDouble("  Base Salary: ");
                const std::string hireDate = readLine("  Hire Date (YYYY-MM-DD): ");
                erp::Employee& employee =
                    system.hr().addEmployee(name, department, position, salary, hireDate);
                std::cout << "  Employee added with ID " << employee.getId() << ".\n";
                break;
            }
            case 2: {
                const std::string name = readLine("  Department Name: ");
                const int managerId = readInt("  Manager Employee ID (-1 if none): ");
                erp::Department& department = system.hr().addDepartment(name, managerId);
                std::cout << "  Department added with ID " << department.getId() << ".\n";
                break;
            }
            case 3:
                system.hr().displayEmployees();
                break;
            case 4:
                system.hr().displayDepartments();
                break;
            case 5: {
                const std::string department = readLine("  Department: ");
                system.hr().displayEmployeesByDepartment(department);
                break;
            }
            case 6: {
                const int id = readInt("  Employee ID: ");
                const std::string department = readLine("  New Department: ");
                system.hr().updateEmployeeDepartment(id, department);
                break;
            }
            case 7: {
                const int id = readInt("  Employee ID: ");
                system.hr().deactivateEmployee(id);
                break;
            }
            default:
                std::cout << "  Invalid choice.\n";
        }
        pause();
    }
}

void handleInventory(erp::ERPSystem& system) {
    while (true) {
        printInventoryMenu();
        const int choice = readInt("  Choice: ");
        if (choice == 0) {
            return;
        }

        switch (choice) {
            case 1: {
                const std::string sku = readLine("  SKU: ");
                const std::string name = readLine("  Product Name: ");
                const std::string category = readLine("  Category: ");
                const int quantity = readInt("  Initial Quantity: ");
                const double cost = readDouble("  Unit Cost: ");
                const double price = readDouble("  Unit Price: ");
                const int reorder = readInt("  Reorder Level: ");
                system.inventory().addProduct(sku, name, category, quantity, cost, price, reorder);
                std::cout << "  Product added.\n";
                break;
            }
            case 2:
                system.inventory().displayCatalogue();
                break;
            case 3: {
                const std::string sku = readLine("  SKU: ");
                const int qty = readInt("  Quantity to add: ");
                system.inventory().stockIn(sku, qty);
                break;
            }
            case 4: {
                const std::string sku = readLine("  SKU: ");
                const int qty = readInt("  Quantity to remove: ");
                system.inventory().stockOut(sku, qty);
                break;
            }
            case 5: {
                const std::string query = readLine("  Search: ");
                const auto results = system.inventory().searchProducts(query);
                std::cout << "\n  Search Results (" << results.size() << ")\n";
                for (const auto* product : results) {
                    std::cout << "  " << product->toString() << "\n";
                }
                break;
            }
            case 6:
                system.inventory().displayLowStock();
                break;
            default:
                std::cout << "  Invalid choice.\n";
        }
        pause();
    }
}

void handlePayroll(erp::ERPSystem& system) {
    while (true) {
        printPayrollMenu();
        const int choice = readInt("  Choice: ");
        if (choice == 0) {
            return;
        }

        switch (choice) {
            case 1: {
                const int id = readInt("  Employee ID: ");
                const std::string period = readLine("  Period (YYYY-MM): ");
                const double taxRate = readDouble("  Tax Rate (e.g. 0.10): ");
                const double deductions = readDouble("  Other Deductions: ");
                system.payroll().processEmployee(id, period, taxRate, deductions);
                break;
            }
            case 2: {
                const std::string period = readLine("  Period (YYYY-MM): ");
                const double taxRate = readDouble("  Tax Rate (e.g. 0.10): ");
                const double deductions = readDouble("  Other Deductions: ");
                system.payroll().processAll(period, taxRate, deductions);
                break;
            }
            case 3:
                system.payroll().displayHistory();
                break;
            case 4: {
                const std::string period = readLine("  Period to post (YYYY-MM): ");
                const double total = system.payroll().totalPayrollForPeriod(period);
                if (total <= 0) {
                    std::cout << "  No payroll found for that period.\n";
                } else {
                    system.accounts().postJournalEntry(period + "-30", "Payroll " + period, "5100", "1000", total);
                }
                break;
            }
            default:
                std::cout << "  Invalid choice.\n";
        }
        pause();
    }
}

void handleAccounts(erp::ERPSystem& system) {
    while (true) {
        printAccountsMenu();
        const int choice = readInt("  Choice: ");
        if (choice == 0) {
            return;
        }

        switch (choice) {
            case 1:
                system.accounts().displayChartOfAccounts();
                break;
            case 2: {
                const std::string date = readLine("  Date (YYYY-MM-DD): ");
                const std::string description = readLine("  Description: ");
                const std::string debit = readLine("  Debit Account Code: ");
                const std::string credit = readLine("  Credit Account Code: ");
                const double amount = readDouble("  Amount: ");
                system.accounts().postJournalEntry(date, description, debit, credit, amount);
                break;
            }
            case 3:
                system.accounts().displayJournal();
                break;
            case 4:
                system.accounts().displayTrialBalance();
                break;
            case 5:
                system.accounts().displayIncomeStatement();
                break;
            default:
                std::cout << "  Invalid choice.\n";
        }
        pause();
    }
}

void handleSales(erp::ERPSystem& system) {
    while (true) {
        printSalesMenu();
        const int choice = readInt("  Choice: ");
        if (choice == 0) {
            return;
        }

        switch (choice) {
            case 1: {
                const std::string name = readLine("  Customer Name: ");
                const std::string email = readLine("  Email: ");
                const std::string phone = readLine("  Phone: ");
                erp::Customer& customer = system.sales().addCustomer(name, email, phone);
                std::cout << "  Customer added with ID " << customer.getId() << ".\n";
                break;
            }
            case 2:
                system.sales().displayCustomers();
                break;
            case 3: {
                const int customerId = readInt("  Customer ID: ");
                const std::string date = readLine("  Order Date (YYYY-MM-DD): ");
                erp::SalesOrder& order = system.sales().createOrder(customerId, date);
                std::cout << "  Order created with ID " << order.getId() << ".\n";
                break;
            }
            case 4: {
                const int orderId = readInt("  Order ID: ");
                const std::string sku = readLine("  Product SKU: ");
                const int qty = readInt("  Quantity: ");
                system.sales().addItemToOrder(orderId, sku, qty);
                break;
            }
            case 5: {
                const int orderId = readInt("  Order ID: ");
                system.sales().completeOrder(orderId);
                break;
            }
            case 6:
                system.sales().displayOrders();
                break;
            default:
                std::cout << "  Invalid choice.\n";
        }
        pause();
    }
}

}  // namespace

int main() {
    std::cout << kBanner;

    const std::string companyName = readLine("  Enter company name [Acme Corp]: ");
    erp::ERPSystem system(companyName.empty() ? "Acme Corp" : companyName);

    std::cout << "\n  Welcome to " << system.getCompanyName() << " ERP System.\n";

    while (true) {
        printMainMenu();
        const int choice = readInt("  Choice: ");

        switch (choice) {
            case 0:
                std::cout << "\n  Shutting down ERP system. Goodbye!\n";
                return 0;
            case 1:
                handleHR(system);
                break;
            case 2:
                handleInventory(system);
                break;
            case 3:
                handlePayroll(system);
                break;
            case 4:
                handleAccounts(system);
                break;
            case 5:
                handleSales(system);
                break;
            case 6:
                system.displayDashboard();
                pause();
                break;
            case 7:
                system.seedSampleData();
                pause();
                break;
            default:
                std::cout << "  Invalid choice.\n";
                pause();
        }
    }
}
