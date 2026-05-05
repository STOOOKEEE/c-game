#include "Player.h"
#include <iostream>

Player::Player(const std::string& name) : Entity(name, 100, 10, 5) {
    this->kills = 0;
    this->spares = 0;
    this->victories = 0;
}

int Player::getKills() const { return this->kills; }
int Player::getSpares() const { return this->spares; }
int Player::getVictories() const { return this->victories; }
std::vector<Item>& Player::getInventory() { return this->inventory; }

void Player::addKill() { this->kills++; }
void Player::addSpare() { this->spares++; }
void Player::addVictory() { this->victories++; }
void Player::addItem(const Item& item) { this->inventory.push_back(item); }

void Player::displayStats() const {
    std::cout << "=== " << this->getName() << " ===" << std::endl;
    std::cout << "HP: " << this->getHp() << "/" << this->getHpMax() << std::endl;
    std::cout << "Monsters killed: " << this->kills << std::endl;
    std::cout << "Monsters spared: " << this->spares << std::endl;
    std::cout << "Victories: " << this->victories << "/10" << std::endl;
}
