#include "Item.h"

Item::Item(const std::string& name, const std::string& type, int value, int quantity) {
    this->name = name;
    this->type = type;
    this->value = value;
    this->quantity = quantity;
}

std::string Item::getName() const { return this->name; }
std::string Item::getType() const { return this->type; }
int Item::getValue() const { return this->value; }
int Item::getQuantity() const { return this->quantity; }

void Item::setQuantity(int q) { this->quantity = q; }

bool Item::use() {
    if (this->quantity <= 0) return false;
    this->quantity--;
    return true;
}
