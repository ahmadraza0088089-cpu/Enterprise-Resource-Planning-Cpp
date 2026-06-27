#include "Product.hpp"

#include <iomanip>
#include <sstream>

namespace erp {

Product::Product(std::string sku, std::string name, std::string category, int quantity,
                 double unitCost, double unitPrice, int reorderLevel)
    : sku_(std::move(sku)),
      name_(std::move(name)),
      category_(std::move(category)),
      quantity_(quantity),
      unitCost_(unitCost),
      unitPrice_(unitPrice),
      reorderLevel_(reorderLevel) {}

const std::string& Product::getSku() const { return sku_; }
const std::string& Product::getName() const { return name_; }
const std::string& Product::getCategory() const { return category_; }
int Product::getQuantity() const { return quantity_; }
double Product::getUnitCost() const { return unitCost_; }
double Product::getUnitPrice() const { return unitPrice_; }
int Product::getReorderLevel() const { return reorderLevel_; }

void Product::setName(const std::string& name) { name_ = name; }
void Product::setCategory(const std::string& category) { category_ = category; }
void Product::setUnitCost(double cost) { unitCost_ = cost; }
void Product::setUnitPrice(double price) { unitPrice_ = price; }
void Product::setReorderLevel(int level) { reorderLevel_ = level; }

bool Product::addStock(int amount) {
    if (amount <= 0) {
        return false;
    }
    quantity_ += amount;
    return true;
}

bool Product::removeStock(int amount) {
    if (amount <= 0 || amount > quantity_) {
        return false;
    }
    quantity_ -= amount;
    return true;
}

bool Product::isLowStock() const { return quantity_ <= reorderLevel_; }

std::string Product::toString() const {
    std::ostringstream stream;
    stream << sku_ << " | " << name_ << " [" << category_ << "] | Qty: " << quantity_
           << " | Cost: " << std::fixed << std::setprecision(2) << unitCost_
           << " | Price: " << unitPrice_;
    if (isLowStock()) {
        stream << " [LOW STOCK]";
    }
    return stream.str();
}

}  // namespace erp
