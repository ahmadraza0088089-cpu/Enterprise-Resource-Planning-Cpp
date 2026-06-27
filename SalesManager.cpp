#include "SalesManager.hpp"

#include <iomanip>
#include <iostream>

namespace erp {

SalesManager::SalesManager(InventoryManager& inventory, AccountsManager& accounts)
    : inventory_(inventory), accounts_(accounts) {}

Customer& SalesManager::addCustomer(std::string name, std::string email, std::string phone) {
    const int id = nextCustomerId_++;
    customers_.push_back(std::make_unique<Customer>(id, std::move(name), std::move(email), std::move(phone)));
    return *customers_.back();
}

Customer* SalesManager::findCustomer(int id) {
    for (auto& customer : customers_) {
        if (customer->getId() == id) {
            return customer.get();
        }
    }
    return nullptr;
}

const Customer* SalesManager::findCustomer(int id) const {
    for (const auto& customer : customers_) {
        if (customer->getId() == id) {
            return customer.get();
        }
    }
    return nullptr;
}

SalesOrder& SalesManager::createOrder(int customerId, const std::string& orderDate) {
    const Customer* customer = findCustomer(customerId);
    const std::string customerName = customer != nullptr ? customer->getName() : "Walk-in Customer";
    const int id = nextOrderId_++;
    orders_.push_back(std::make_unique<SalesOrder>(id, customerId, customerName, orderDate));
    return *orders_.back();
}

bool SalesManager::addItemToOrder(int orderId, const std::string& sku, int quantity) {
    SalesOrder* order = nullptr;
    for (auto& entry : orders_) {
        if (entry->getId() == orderId) {
            order = entry.get();
            break;
        }
    }

    if (order == nullptr) {
        std::cout << "  Error: Order not found.\n";
        return false;
    }

    if (order->getStatus() != OrderStatus::Pending) {
        std::cout << "  Error: Cannot modify a completed or cancelled order.\n";
        return false;
    }

    const Product* product = inventory_.findProduct(sku);
    if (product == nullptr) {
        std::cout << "  Error: Product not found.\n";
        return false;
    }

    if (product->getQuantity() < quantity) {
        std::cout << "  Error: Insufficient stock for " << product->getName() << ".\n";
        return false;
    }

    OrderLine line{sku, product->getName(), quantity, product->getUnitPrice()};
    order->addLine(line);
    std::cout << "  Added " << quantity << " x " << product->getName() << " to order #" << orderId << ".\n";
    return true;
}

bool SalesManager::completeOrder(int orderId, const std::string& paymentAccountCode) {
    SalesOrder* order = nullptr;
    for (auto& entry : orders_) {
        if (entry->getId() == orderId) {
            order = entry.get();
            break;
        }
    }

    if (order == nullptr) {
        std::cout << "  Error: Order not found.\n";
        return false;
    }

    if (order->getStatus() != OrderStatus::Pending) {
        std::cout << "  Error: Order is not pending.\n";
        return false;
    }

    if (order->getLines().empty()) {
        std::cout << "  Error: Order has no items.\n";
        return false;
    }

    for (const auto& line : order->getLines()) {
        if (!inventory_.stockOut(line.sku, line.quantity)) {
            std::cout << "  Error: Could not fulfill order due to stock issue.\n";
            return false;
        }
    }

    const double total = order->getTotal();
    double cogs = 0.0;
    for (const auto& line : order->getLines()) {
        const Product* product = inventory_.findProduct(line.sku);
        if (product != nullptr) {
            cogs += product->getUnitCost() * line.quantity;
        }
    }

    accounts_.postJournalEntry(order->getOrderDate(), "Sale Order #" + std::to_string(orderId), paymentAccountCode,
                               "4000", total);
    if (cogs > 0) {
        accounts_.postJournalEntry(order->getOrderDate(), "COGS Order #" + std::to_string(orderId), "5000", "1200",
                                   cogs);
    }

    order->setStatus(OrderStatus::Completed);
    std::cout << "  Order #" << orderId << " completed. Total: " << std::fixed << std::setprecision(2) << total
              << "\n";
    return true;
}

const std::vector<std::unique_ptr<Customer>>& SalesManager::getCustomers() const { return customers_; }
const std::vector<std::unique_ptr<SalesOrder>>& SalesManager::getOrders() const { return orders_; }

void SalesManager::displayCustomers() const {
    std::cout << "\n  Customers (" << customers_.size() << ")\n";
    std::cout << "  " << std::string(60, '-') << "\n";
    if (customers_.empty()) {
        std::cout << "  No customers on record.\n";
        return;
    }
    for (const auto& customer : customers_) {
        std::cout << "  " << customer->toString() << "\n";
    }
}

void SalesManager::displayOrders() const {
    std::cout << "\n  Sales Orders (" << orders_.size() << ")\n";
    std::cout << "  " << std::string(60, '-') << "\n";
    if (orders_.empty()) {
        std::cout << "  No sales orders.\n";
        return;
    }
    for (const auto& order : orders_) {
        std::cout << "  " << order->toString() << "\n";
    }
}

double SalesManager::totalRevenue() const {
    double total = 0.0;
    for (const auto& order : orders_) {
        if (order->getStatus() == OrderStatus::Completed) {
            total += order->getTotal();
        }
    }
    return total;
}

}  // namespace erp
