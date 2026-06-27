#pragma once

#include <string>
#include <vector>

namespace erp {

struct OrderLine {
    std::string sku;
    std::string productName;
    int quantity;
    double unitPrice;
    double lineTotal() const;
};

enum class OrderStatus { Pending, Completed, Cancelled };

class SalesOrder {
public:
    SalesOrder(int id, int customerId, std::string customerName, std::string orderDate);

    int getId() const;
    int getCustomerId() const;
    const std::string& getCustomerName() const;
    const std::string& getOrderDate() const;
    OrderStatus getStatus() const;
    const std::vector<OrderLine>& getLines() const;

    void addLine(OrderLine line);
    double getTotal() const;
    void setStatus(OrderStatus status);

    std::string toString() const;

private:
    int id_;
    int customerId_;
    std::string customerName_;
    std::string orderDate_;
    OrderStatus status_;
    std::vector<OrderLine> lines_;
};

}  // namespace erp
