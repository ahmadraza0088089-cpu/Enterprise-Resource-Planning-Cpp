#pragma once

#include <string>

namespace erp {

class Product {
public:
    Product(std::string sku, std::string name, std::string category, int quantity,
            double unitCost, double unitPrice, int reorderLevel = 10);

    const std::string& getSku() const;
    const std::string& getName() const;
    const std::string& getCategory() const;
    int getQuantity() const;
    double getUnitCost() const;
    double getUnitPrice() const;
    int getReorderLevel() const;

    void setName(const std::string& name);
    void setCategory(const std::string& category);
    void setUnitCost(double cost);
    void setUnitPrice(double price);
    void setReorderLevel(int level);

    bool addStock(int amount);
    bool removeStock(int amount);
    bool isLowStock() const;

    std::string toString() const;

private:
    std::string sku_;
    std::string name_;
    std::string category_;
    int quantity_;
    double unitCost_;
    double unitPrice_;
    int reorderLevel_;
};

}  // namespace erp
