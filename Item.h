#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
    std::string type;
    int value;
    int quantity;

public:
    Item(const std::string& name, const std::string& type, int value, int quantity);

    // Accesseurs
    std::string getName() const;
    std::string getType() const;
    int getValue() const;
    int getQuantity() const;

    // Modificateurs
    void setQuantity(int q);
    bool use(); // retourne true si l'item a pu etre utilise
};

#endif
