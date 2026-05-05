#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
private:
    std::string name;
    int hp;
    int hpMax;
    int atk;
    int def;

public:
    Entity(const std::string& name, int hp, int atk, int def);
    virtual ~Entity() = default;

    // Accesseurs
    std::string getName() const;
    int getHp() const;
    int getHpMax() const;
    int getAtk() const;
    int getDef() const;
    bool isAlive() const;

    // Modificateurs
    void setHp(int hp);
    void takeDamage(int damage);
    void heal(int amount);

    // Methode virtuelle pure -> classe abstraite
    virtual void displayStats() const = 0;
};

#endif
