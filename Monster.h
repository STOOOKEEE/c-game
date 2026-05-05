#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"
#include "ActAction.h"
#include <vector>
#include <string>

enum class MonsterCategory { NORMAL, MINIBOSS, BOSS };

class Monster : public Entity {
protected:
    MonsterCategory category;
    int mercy;
    int mercyGoal;
    std::vector<std::string> actIds;
    bool killed;
    bool spared;

public:
    Monster(const std::string& name, int hp, int atk, int def,
            MonsterCategory category, int mercyGoal, const std::vector<std::string>& actIds);
    virtual ~Monster() = default;

    // Accesseurs
    MonsterCategory getCategory() const;
    std::string getCategoryStr() const;
    int getMercy() const;
    int getMercyGoal() const;
    const std::vector<std::string>& getActIds() const;
    bool isKilled() const;
    bool isSpared() const;

    // Modificateurs
    void modifyMercy(int amount);
    void setKilled(bool k);
    void setSpared(bool s);

    // Polymorphisme : nombre d'actions ACT selon la categorie
    virtual int getMaxActs() const = 0;

    void displayStats() const override;

    // Cree une copie du monstre (pour combat)
    virtual Monster* clone() const = 0;
};

// Classes derivees
class NormalMonster : public Monster {
public:
    using Monster::Monster;
    int getMaxActs() const override;
    Monster* clone() const override;
};

class MiniBossMonster : public Monster {
public:
    using Monster::Monster;
    int getMaxActs() const override;
    Monster* clone() const override;
};

class BossMonster : public Monster {
public:
    using Monster::Monster;
    int getMaxActs() const override;
    Monster* clone() const override;
};

#endif
