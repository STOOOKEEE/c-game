#include "Monster.h"
#include <iostream>

Monster::Monster(const std::string& name, int hp, int atk, int def,
                 MonsterCategory category, int mercyGoal, const std::vector<std::string>& actIds)
    : Entity(name, hp, atk, def) {
    this->category = category;
    this->mercy = 0;
    this->mercyGoal = mercyGoal;
    this->actIds = actIds;
    this->killed = false;
    this->spared = false;
}

MonsterCategory Monster::getCategory() const { return this->category; }

std::string Monster::getCategoryStr() const {
    switch (this->category) {
        case MonsterCategory::NORMAL:   return "NORMAL";
        case MonsterCategory::MINIBOSS: return "MINIBOSS";
        case MonsterCategory::BOSS:     return "BOSS";
    }
    return "UNKNOWN";
}

int Monster::getMercy() const { return this->mercy; }
int Monster::getMercyGoal() const { return this->mercyGoal; }
const std::vector<std::string>& Monster::getActIds() const { return this->actIds; }
bool Monster::isKilled() const { return this->killed; }
bool Monster::isSpared() const { return this->spared; }

void Monster::modifyMercy(int amount) {
    this->mercy += amount;
    if (this->mercy < 0) this->mercy = 0;
    if (this->mercy > this->mercyGoal) this->mercy = this->mercyGoal;
}

void Monster::setKilled(bool k) { this->killed = k; }
void Monster::setSpared(bool s) { this->spared = s; }

void Monster::displayStats() const {
    std::cout << "--- " << this->name << " [" << this->getCategoryStr() << "] ---" << std::endl;
    std::cout << "HP: " << this->hp << "/" << this->hpMax << std::endl;
    std::cout << "ATK: " << this->atk << " | DEF: " << this->def << std::endl;
    std::cout << "Mercy: " << this->mercy << "/" << this->mercyGoal << std::endl;
}

// NormalMonster
int NormalMonster::getMaxActs() const { return 2; }
Monster* NormalMonster::clone() const { return new NormalMonster(*this); }

// MiniBossMonster
int MiniBossMonster::getMaxActs() const { return 3; }
Monster* MiniBossMonster::clone() const { return new MiniBossMonster(*this); }

// BossMonster
int BossMonster::getMaxActs() const { return 4; }
Monster* BossMonster::clone() const { return new BossMonster(*this); }
