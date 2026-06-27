#pragma once

#include "Product.hpp"

#include <memory>
#include <string>
#include <vector>

namespace erp {

class InventoryManager {
public:
    Product& addProduct(std::string sku, std::string name, std::string category, int quantity,
                        double unitCost, double unitPrice, int reorderLevel = 10);

    Product* findProduct(const std::string& sku);
    const Product* findProduct(const std::string& sku) const;
    std::vector<const Product*> searchProducts(const std::string& query) const;

    bool stockIn(const std::string& sku, int quantity);
    bool stockOut(const std::string& sku, int quantity);

    const std::vector<std::unique_ptr<Product>>& getProducts() const;

    void displayCatalogue() const;
    void displayLowStock() const;
    double totalInventoryValue() const;

private:
    std::vector<std::unique_ptr<Product>> products_;
};

}  // namespace erp
