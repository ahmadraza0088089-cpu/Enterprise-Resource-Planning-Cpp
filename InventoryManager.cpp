#include "InventoryManager.hpp"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

namespace erp {

namespace {

std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char character) { return static_cast<char>(std::tolower(character)); });
    return value;
}

bool containsIgnoreCase(const std::string& haystack, const std::string& needle) {
    return toLower(haystack).find(toLower(needle)) != std::string::npos;
}

}  // namespace

Product& InventoryManager::addProduct(std::string sku, std::string name, std::string category,
                                      int quantity, double unitCost, double unitPrice, int reorderLevel) {
    if (findProduct(sku) != nullptr) {
        std::cout << "  Warning: SKU " << sku << " already exists. Updating stock instead.\n";
        Product* existing = findProduct(sku);
        existing->addStock(quantity);
        return *existing;
    }

    products_.push_back(std::make_unique<Product>(std::move(sku), std::move(name), std::move(category),
                                                  quantity, unitCost, unitPrice, reorderLevel));
    return *products_.back();
}

Product* InventoryManager::findProduct(const std::string& sku) {
    for (auto& product : products_) {
        if (product->getSku() == sku) {
            return product.get();
        }
    }
    return nullptr;
}

const Product* InventoryManager::findProduct(const std::string& sku) const {
    for (const auto& product : products_) {
        if (product->getSku() == sku) {
            return product.get();
        }
    }
    return nullptr;
}

std::vector<const Product*> InventoryManager::searchProducts(const std::string& query) const {
    std::vector<const Product*> results;
    for (const auto& product : products_) {
        if (containsIgnoreCase(product->getSku(), query) || containsIgnoreCase(product->getName(), query) ||
            containsIgnoreCase(product->getCategory(), query)) {
            results.push_back(product.get());
        }
    }
    return results;
}

bool InventoryManager::stockIn(const std::string& sku, int quantity) {
    Product* product = findProduct(sku);
    if (product == nullptr) {
        std::cout << "  Error: Product not found.\n";
        return false;
    }
    if (!product->addStock(quantity)) {
        std::cout << "  Error: Invalid quantity.\n";
        return false;
    }
    std::cout << "  Stock in recorded. New quantity: " << product->getQuantity() << "\n";
    return true;
}

bool InventoryManager::stockOut(const std::string& sku, int quantity) {
    Product* product = findProduct(sku);
    if (product == nullptr) {
        std::cout << "  Error: Product not found.\n";
        return false;
    }
    if (!product->removeStock(quantity)) {
        std::cout << "  Error: Insufficient stock.\n";
        return false;
    }
    std::cout << "  Stock out recorded. Remaining: " << product->getQuantity() << "\n";
    return true;
}

const std::vector<std::unique_ptr<Product>>& InventoryManager::getProducts() const { return products_; }

void InventoryManager::displayCatalogue() const {
    std::cout << "\n  Inventory Catalogue (" << products_.size() << " items)\n";
    std::cout << "  " << std::string(70, '-') << "\n";
    if (products_.empty()) {
        std::cout << "  No products in inventory.\n";
        return;
    }
    for (const auto& product : products_) {
        std::cout << "  " << product->toString() << "\n";
    }
}

void InventoryManager::displayLowStock() const {
    std::cout << "\n  Low Stock Alerts\n";
    std::cout << "  " << std::string(50, '-') << "\n";
    bool found = false;
    for (const auto& product : products_) {
        if (product->isLowStock()) {
            std::cout << "  " << product->toString() << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "  All products are above reorder level.\n";
    }
}

double InventoryManager::totalInventoryValue() const {
    double total = 0.0;
    for (const auto& product : products_) {
        total += product->getQuantity() * product->getUnitCost();
    }
    return total;
}

}  // namespace erp
