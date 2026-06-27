#include "SalesOrder.hpp"

#include <iomanip>
#include <sstream>

namespace erp {

double OrderLine::lineTotal() const { return quantity * unitPrice; }

SalesOrder::SalesOrder(int id, int customerId, std::string customerName, std::string orderDate)
    : id_(id),
      customerId_(customerId),
      customerName_(std::move(customerName)),
      orderDate_(std::move(orderDate)),
      status_(OrderStatus::Pending) {}

int SalesOrder::getId() const { return id_; }
int SalesOrder::getCustomerId() const { return customerId_; }
const std::string& SalesOrder::getCustomerName() const { return customerName_; }
const std::string& SalesOrder::getOrderDate() const { return orderDate_; }
OrderStatus SalesOrder::getStatus() const { return status_; }
const std::vector<OrderLine>& SalesOrder::getLines() const { return lines_; }

void SalesOrder::addLine(OrderLine line) { lines_.push_back(std::move(line)); }

double SalesOrder::getTotal() const {
    double total = 0.0;
    for (const auto& line : lines_) {
        total += line.lineTotal();
    }
    return total;
}

void SalesOrder::setStatus(OrderStatus status) { status_ = status; }

namespace {

const char* statusLabel(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending:
            return "Pending";
        case OrderStatus::Completed:
            return "Completed";
        case OrderStatus::Cancelled:
            return "Cancelled";
    }
    return "Unknown";
}

}  // namespace

std::string SalesOrder::toString() const {
    std::ostringstream stream;
    stream << "Order #" << id_ << " | " << customerName_ << " | " << orderDate_ << " | "
           << statusLabel(status_) << " | Total: " << std::fixed << std::setprecision(2) << getTotal();
    for (const auto& line : lines_) {
        stream << "\n    - " << line.productName << " x" << line.quantity << " @ " << line.unitPrice;
    }
    return stream.str();
}

}  // namespace erp
