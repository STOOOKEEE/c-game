#include "Entity.h"

Entity::Entity(const std::string& name, int hp, int atk, int def) {
    this->name = name;
    this->hp = hp;
    this->hpMax = hp;
    this->atk = atk;
    this->def = def;
}

std::string Entity::getName() const { return this->name; }
int Entity::getHp() const { return this->hp; }
int Entity::getHpMax() const { return this->hpMax; }
int Entity::getAtk() const { return this->atk; }
int Entity::getDef() const { return this->def; }
bool Entity::isAlive() const { return this->hp > 0; }

void Entity::setHp(int h) {
    this->hp = h;
    if (this->hp < 0) this->hp = 0;
    if (this->hp > this->hpMax) this->hp = this->hpMax;
}

void Entity::takeDamage(int damage) {
    this->hp -= damage;
    if (this->hp < 0) this->hp = 0;
}

void Entity::heal(int amount) {
    this->hp += amount;
    if (this->hp > this->hpMax) this->hp = this->hpMax;
}
