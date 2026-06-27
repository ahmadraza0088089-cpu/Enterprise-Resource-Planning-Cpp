#pragma once

#include "AccountsManager.hpp"
#include "Customer.hpp"
#include "InventoryManager.hpp"
#include "SalesOrder.hpp"

#include <memory>
#include <string>
#include <vector>

namespace erp {

class SalesManager {
public:
    SalesManager(InventoryManager& inventory, AccountsManager& accounts);

    Customer& addCustomer(std::string name, std::string email, std::string phone);

    Customer* findCustomer(int id);
    const Customer* findCustomer(int id) const;

    SalesOrder& createOrder(int customerId, const std::string& orderDate);
    bool addItemToOrder(int orderId, const std::string& sku, int quantity);
    bool completeOrder(int orderId, const std::string& paymentAccountCode = "1000");

    const std::vector<std::unique_ptr<Customer>>& getCustomers() const;
    const std::vector<std::unique_ptr<SalesOrder>>& getOrders() const;

    void displayCustomers() const;
    void displayOrders() const;
    double totalRevenue() const;

private:
    InventoryManager& inventory_;
    AccountsManager& accounts_;
    std::vector<std::unique_ptr<Customer>> customers_;
    std::vector<std::unique_ptr<SalesOrder>> orders_;
    int nextCustomerId_ = 2001;
    int nextOrderId_ = 3001;
};

}  // namespace erp
